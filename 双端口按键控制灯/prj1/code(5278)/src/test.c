/*-----------------------------------------------
  名称：TM52F5278实验板专用测试程序
  功能：例程首先，通过按键S1改变开关机状态，并通过IAP功能将每次的开关机状态记录在单片机内置的FLASH中。
  			其次，1  通过AD转换功能采集滑动变阻器的电压值，并利用该值通过PWM对电机进行调速控制。
				  2  将按键S3加一计数的值，掉电存储到AT24C02中，上电再将值读出来。
				  3  将按键S4加一计数的值，掉电存储到AT93C46中，同样上电再读出来。
				  4	 使用红外遥控上的三个按键取代小板上的三个按键实现同样的功能
			最后  分别通过数码管动态扫描和内置LED驱动两种方式（通过注释和打开test.h中的internal_led，
				  从这两种方式中进行切换），将AD值，按键S3，S4的值显示在对应的数码管上。
  编写：Peasant_zhang
  日期：2015 9.6
------------------------------------------------*/
#include <REGtenxTM52F5278.h>
#include <intrins.h>
#include <absacc.h>
#include "test.h"
#include "AT2402.h"
#include "AT93C46.h"
#include "led_driver.h"
#include "music.h"
#include "IrDA_receive.h"




u8 s1_cnt = 0; 			//定义中断计数用来按键扫描延时
u8 s3_cnt = 0;
u8 s4_cnt = 0;


static u16 cnt0 = 0;	//用来ad数据采集延时
static u16 cnt1 = 0; 	//用来数码管动态扫描延时计时
static u8 dat_templ;   	//ad转换暂存低2位变量
u8 dat_temph;		   	//用来暂存高8位AD转换值

bit s1_flag ; 			//开机标识，默认为开机状态
bit ad_flag = 0;  
bit display_flag;		//定义数码管显示标志位
u16 buzzer_cnt;			//定义蜂鸣器延时计数变量

bit beep_flg;
bit com0_flag;
bit com1_flag;
bit com2_flag;
bit com3_flag;
bit g_flag;				//4ms计时
u8 s3_count = 0;		//按键S3计数0~9
u8 s4_count = 0;		//按键S4计数0~9
u8 com = 0;				//用于动态扫描位码切换

u8 buffer[4] = {0,0,0,0};	//用于缓存4位数码管显示值，buffer[0],buffer[1]用于缓存AD值，
							//buffer[2]用于缓存24C02，buffer[3]用于缓存94c02中的值


//动态扫描共阳数码管编码
u8 code duan_ma[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
					 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};


u16 dat;					//测试存储单元正常工作临时变量

u8 switch_state;			//开关机状态变量

uchar IrDA_buf;			   //用于存储红外接收到的数据

u16 IrDA_cnt = 0 ;		   //用于对红外波段进行计数
u16 UART_cnt;			   //定时发送串口数据

//主函数
void main ()
{
	u8 i;
	sys_clk_init();		   //系统时钟初始化
#ifdef internal_led
	led_controler();	   //初始化为内部LED驱动
#endif
	gpio_init();		   //设置好相对应的IO管脚

	timer1_init();
//  uart_init();		   //串口占用定时器1为波特率发生器
  	adc_init();			   //初始化AD
   	pwm_init();			   //初始化PWM
   	timer0_init();		   //初始化定时器0
	timer2_init();
	s1_flag = IAP_Read(switch_addr); 		//取出开关机之前的状态记忆值
//	if(s1_flag != 1 && s1_flag != 0) {		//当IAP中存储的值既不是1也不是0时，初始化为0，关机状态
//		s1_flag = 0;
//	}


//	led_disp();	 		//led显示
//	lcd_seg_disp();
//	Segment8_4(); 		//测试数码管能不能正常显示

	dat = IAP_Read(switch_addr);		//测试IAP能否正常读写
	IAP_Write(switch_addr, 0x03);
	dat = IAP_Read(switch_addr);

//	dat = c2404_read();		 //测试IIC正常读写
//	c2404_write(0x0b);
//	Timer0_delay(20);
//	dat = c2404_read();

//	dat = Read(0x10);		//测试SPI正常读写	
//	Write(0x10, 0x03);
//	Timer0_delay(20);
//	dat = Read(0x10);

//	IrDA_re();				//测试红外信号的接收
//	IrDA_process();


//	PINMOD |= TCOE; 				//通过P1.4输出2分频后的系统时钟	
//	sing_the_song();
//	BUZZER = 0;
//	dat_temph = IAP_Read(ad_addr); 	//开机读出保存的值

	s3_count = c2404_read();	    //从2404中读出按键S3计数到的最新值
	s4_count = Read(0x10);			//从93c46中读取按键S4计数到的最新值	  括号中的0x10为93c46中的一个地址
#ifdef sing
	sing_the_song();
#endif

	
	for(;;) {
			IrDA_receive();

			while(g_flag){
				g_flag = 0;
				key_scan(); 				//按键扫描
				IrDA_process();				//红外接收
				count_range();				//计数范围

				if(s1_flag) {				 //开启AD转换，并将转换得到的高8位送到PWM的高8为
					ad_to_pwm_and_segdisply();
					PWM1DH  =  dat_temph; 		//通过AD转换调节PWM1输出量
				}

			    if(s1_flag) {
					PINMOD |= PWM1BOE;			//打开PWM输出功能
				 } else {
				 	//PINMOD = 0;				//测试发现关闭pwm后，P2.3输出默认为高电平
					PWM1DH  = 0x00;				//通过向PWM1DH中写0，使输出拉低
				}


				if (s1_flag) 				    //记忆按键值
					EEPROM_record();
						
				if (s1_flag) {
				#ifndef internal_led
					display_flag = 1;	
				#else
					display_flag = 0;
					led_disp();				//LED驱动显示
				#endif
				} else {
				#ifndef internal_led
					display_flag = 1; 
				#else
					display_flag = 0;
					for (i = 0; i < 8; i++) 	//对LCD_RAM初始化为全正，熄灭LED
						XBYTE[0xf000+i] = 0xff;
				#endif
				}

				if (s1_flag) {
					if(IAP_Read(switch_addr) != switch_on)
						IAP_Write(switch_addr, switch_on);  //使用IAP记录开机状态
		
	 			} else {
					if(IAP_Read(switch_addr != switch_off))
	 	 				IAP_Write(switch_addr, switch_off); //使用IAP记录关机状态
	 			} 

	 		}
			
				
	   }
}

//系统时钟初始化
void sys_clk_init()
{
	
//	CLKPSC_H = 0;
//	CLKPSC_L = 0;
	_nop_();			 //在内部晶振FRC = 7.3728MHZ且不分频的情况下一个nop为0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLKCON = CLKPSC_Div2; //对时钟进行二分频
	_nop_();			 //在内部晶振FRC = 7.3728MHZ且不分频的情况下一个nop为0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	FCKTYPE	= 0;  	//内部快时钟	7.3728Mhz	0.135us		   0为内部快钟
 	STPFCK = 0;  	//停止快时钟
	_nop_();			//在内部晶振FRC = 7.3728MHZ且不分频的情况下一个nop为0.875us
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SELFCK	= 1;  	//选择快时钟(默认为内部FRC)	0为慢时钟
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
//	PINMOD |= TCOE; //通过P1.4输出2分频后的系统时钟	
}

//GPIO初始化
void gpio_init()
{

	//设置P3.3 P3.2 P2.5分别为为S1,S3,S4按键输入， P3口默认为高阻态
	P3MODL = 0x00;	//P3.3口默认为输入状态
	P3_3 = 1;		//输入模式下开启内部上拉
	P3_2 = 1;		//0时为输入，1时为内部上拉
	P2_5 = 1;		//输入模式开启内部上拉
	
#ifndef internal_led
	//设置相应IO口为数码管动态扫描输出口
	P0OE = 0xff;	//使能P0口输出
	P3MODH = P34MOD_2 | P35MOD_2 | P36MOD_2; 	//设置P3.4,P3.5,P3.6为输出
	P1MODH = 0x80;	 //设置 P1.7为CMOS输出
#else
	P3MODH = P34MOD_3 | P35MOD_3 | P36MOD_3; //设置为seg——lcd输出
   	P1MODH = P17MOD_3 ; 
   	P0OE = 0xff;
#endif


	//将P1.0设置为AD口
	P1MODL = 0x03;
	
	
	//设置P2.3为PWM口
	P2MOD |= P2OE3;	 //引脚输出为推挽输出方式

	//设置P1.4，P1.5分别为AT2402的scl和sda接口
	P1MODH |= P15MOD_0 | P14MOD_2; 	  //P1.5为开漏输出，且允许输入。P1.4为CMOS输出

	//设置P2.2为推挽输出, 对应CS
	P2MOD |= P2OE2;	 //引脚输出为推挽输出方式
	P1MODL |= P13MOD_0 | P12MOD_2 | P11MOD_2;

	//设置P1.6为有源（振荡源）蜂鸣器输出口
	P1MODH |= P16MOD_2;
	BUZZER = 0;			//开始蜂鸣器为关闭状态
	//设置P2.4为无源蜂鸣器输出口
	P2MOD |= P2OE4;	 //引脚输出为推挽输出方式
	P2_4 = 0;

	//设置P2_0为红外输入口
	P2MOD |= P20MOD_0;
	P2_0 = 1;				//开启内部上拉

}


//测试数码管是否能正常工作
void Segment8_4()
{
	P0OE = 0xff;	//使能P0口输出
	P3MODH |= P34MOD_2 | P35MOD_2 | P36MOD_2; 	//设置P3.4,P3.5,P3.6为输出
	P1MODH |= 0x80;	 //设置 P1.7为CMOS输出

	P0_0 = 0;  	//COM口
	P0_1 = 0;
	P0_2 = 0;
	P0_3 = 0;	//COM口
		 
	P0_4 = 0;	//段码输入口
	P0_5 = 0;
	P0_6 = 0;
	P0_7 = 0;
	P3_4 = 0;
	P3_5 = 0;
	P3_6 = 0;
	P1_7 = 0;	//段码入口
}
	

// 串口初始化
void uart_init(void)

{

//采用T1计时,- 必须采用Timer1自动重装模,T1中断要关闭
//实际的波特率  9615

	 SM0=0;
	 SM1=1;	             // SM1\SM0=01   UART mode=1 ;8位数据传送   //第9位是 奇偶校验位
 	 SM2=0;		   	     //Mode 1, 3     波特率采用 9600 = (SMOD+1) x Fsysclk / (32 x 2 x (256-TH1)) --- 若使用Timer1 自动重载模式
 	 PCON=0x80;          //SMOD=1
				   
	 TL1=244;		   	 //假如我用4MHZ晶体通过计算 256-TH1应等于13.2, 那么TH1=256-13.2=242.8 约等243 
 	 TH1=244;			 //因为我是用两个电路板通信所以波特率B不必精确到9600, 只要两个电路板一起使用相同的晶体 TH1也相同即可准确通信
 	 TMOD=0x20;         //T1采用8位重装模式

		 				//实际的波特率  9615= (1+1) x 4000 000 / (32 x 2 x (256-243)) 

		 				//9615/9600=1.0016
	 TI=0;			    //先清发送中断 标志
	 RI=0;				//先清接收中断 标志
  	 T2CON=0;
	 TR1=1;	            //TIMER1 运行
//	 REN=1;		        //UART接收收据使能
// 	 IPH=0x10;    //UART中断设为高优先级
// 	 EA=1;              //全局中断打开
//	 ES=1;
}


//发送一个字节
void SendByte(unsigned char dat)
{
 	SBUF = dat;
 	while(!TI);
      TI = 0;
}

//发送int型数据	   
void SendWord(unsigned int dat)
{
   u8 a, b;

   a =  dat;
   SendByte(a);			 //先发送低位字节
   b = dat >> 8;
   SendByte(b);			 //再发送高位字节

} 

//发送一个字符串
void SendStr(const unsigned char *s)
{
 	while(*s!='\0')// \0 表示字符串结束标志，
                //通过检测是否字符串末尾
  	{
  		SendByte(*s);
  		s++;
  	}
}
   
//ADC初始化
void adc_init()
{
	OPTION |= ADCKS_sys_16;   //ADC时钟为系统时钟的16分频
	CHSEL = 0x40;		     //通道选择为4通道，引脚为P1.0
	
}

//PWM初始化
void pwm_init()
{
 	PWMCON |= PWM0CKS_4;    //PWM0 clock =FRC Double frequence
	PWM1PRD = 0x80;			//周期为 256
	PWM1DH  = 0x40;
//	PWM0DL  = 0x00;
	PINMOD |= PWM1BOE ;	    
}



//外部中断0初始化
void int0_init()
{
 	IT0=1;				//负跳变触发
 	EX0=1;				//开外部中断0
 	EA=1;				//开总中断
}


//定时器0初始化   
//定时器输入时钟的基准频率为系统时钟的1/2  
//此处使用内部快钟并经过2分频后得到的计数单位时间为 0.5425us
void timer0_init()	  	
{
	TMOD |= 0x01;	   //设置为8

	TH0 = 0xe3;		   //定时4ms
	TL0 = 0x33;
	TR0 = 1;
	ET0 = 1;
	EA = 1;		
}

//定时器1初始化  定时约5.5个微秒

//void timer1_init()	  	
//{
//	TMOD |= 0x10;	   //定时器1设置为16位计数
//
//	TH1 = 0xff;		   
//	TL1 = 0xf6;
////	TR1 = 1;
//	ET1 = 1;		   
//	PT1 = 1;		   //设置定时器1为高优先级中断
//	EA = 1;		
//}


//定时器2初始化  定时约20个微秒
void timer2_init()
{
	TL2 = 0xb6;			 //20个us时计数值为0xffdb	  40us->ffb6
	TH2 = 0xff;
    RCP2H = 0xff;				
  	RCP2L = 0xb6;
	IPH |= 0x20;		//设置PT2H为1	 定时器中断具有最高优先级
	IP  |= 0x20;		//设置PT2为1
  	ET2=1;                     //打开定时器中断
  	EA=1;                      //打开总中断
//	TR2=1;                     //打开定时器开关
}


//外部中断0中断服务程序
//void int0_isr() interrupt 0 using 0
//{
//  
////	cnt++;
////
////	if(cnt > 1)
////		cnt = 0;
//
//}

//定时中断0服务程序 系统2分频时 定时4ms
void timer0_isr() interrupt 1 
{
	TH0 += 0xe3;		  
	TL0 += 0x33;

	g_flag = 1;
	//对应的按键按下开始计数延时
	if(key_flag0 == 1){
		key_flag0 = 0;
		s3_cnt++;
	}

	if(key_flag2 == 1) {
		key_flag2 = 0;
		s4_cnt++;
	}

	if(key_flag4 == 1) {
		key_flag4 = 0;
		s1_cnt++;
	}

	cnt0++;
	buzzer_cnt++; 
	
	source_beep();

	if(display_flag && s1_flag == 1) 
		segment_scan();	 		//数码管动态扫描
	 if(display_flag && s1_flag == 0)
	 	seg_send_weidata(0xff);		//关闭数码管显示

//   UART_cnt++;				//串口发送定时计数
}

//定时中断1服务程序 
//void timer1_isr() interrupt 3 
//{
//   	IrDA_cnt++;
//  	TH1 = 0xff;		   
//	TL1 = 0xf6;
////   	BUZZER = ~BUZZER;
//}


//定时中断2服务程序 
void timer2_isr() interrupt 5 
{
   TF2 = 0;					//添加额外的指令会占用时间
   IrDA_cnt++;
   
// BUZZER = ~BUZZER;
}

//按键扫描
void key_scan()
{
  //检测按键S3
	if (P3_2 == 0) {
		   key_flag0 = 1;	  			//按键按下开始延时计数标志置1
			if (s3_cnt >= 8) {			//延时30ms后，清零计数变量
				s3_cnt = 0;
				if (key_flag1 == 0) {  	//较难理解，作用长按无效或不用检测按键松开，效率高
					key_flag1 = 1;
					s3_count++;
					key_flag6 = 1;		//作为2402写的标志位
					beep_flg = 1;
				}		
			}
	} else {
		key_flag0 = 0;
		key_flag1 = 0;
		s3_cnt = 0;
	}

	//检测按键S4
	if (P2_5 == 0) {
		   key_flag2 = 1;
			if (s4_cnt >= 8) {
				s4_cnt = 0;
				if (key_flag3 == 0) {
					key_flag3 = 1;
					s4_count++;		  
					key_flag7 = 1;		 //作为93c46写的标志位
					beep_flg = 1;
				}		
			}
	} else {
		key_flag2 = 0;
		key_flag3 = 0;
		s4_cnt = 0;
	}

	//检测按键S1
	if (P3_3 == 0) {
		   key_flag4 = 1;
			if (s1_cnt >= 8) {
				s1_cnt = 0;
				if (key_flag5 == 0) {
					key_flag5 = 1;
					s1_flag = ~s1_flag;
					beep_flg = 1;
				}		
			}
	} else {
		key_flag4 = 0;
		key_flag5 = 0;
		s1_cnt = 0;
	}

	
	
}

//红外信号对开关机、计数器的处理
void IrDA_process()
{
	if (biaoz == 1) {
		biaoz = 0;
		IrDA_buf = sj[2];
	}

	switch(IrDA_buf) {

	case 0x11:				//开关机码
		IrDA_buf = 0;
		s1_flag = ~s1_flag;
		beep_flg = 1;
		break;
	case 0x22:			    //对应按键s4
		IrDA_buf = 0;
		key_flag6 = 1;		 //作为2402写的标志位
		s4_count++;		  
		key_flag7 = 1;		 //作为93c46写的标志位
		beep_flg = 1;
		break;
	case 0x33:			   //对应按键s3

		IrDA_buf = 0;
		s3_count++;
		key_flag6 = 1;
		key_flag7 = 1;

		beep_flg = 1;
		break;
	default: break;
	}
}

//-----------------------------------------------------------
//通过K1按键控制开关机状态，并使用IAP记录开关机状态下的状态量
//-----------------------------------------------------------

//IAP记录开关机状态
void  switch_rec(void)
{
  	if (s1_flag == 1) {
		IAP_Write(switch_addr, switch_on);  //使用IAP记录开机状态
		
	 } else if(s1_flag == 2) {
	 	 IAP_Write(switch_addr, switch_off); //使用IAP记录关机状态
	 } 
}

//开机状态
void switch_onn()
{

	dat_temph = IAP_Read(ad_addr); 	//开机读出保存的值
	s3_count = c2404_read();	    //从2404中读出按键S3计数到的最新值
	s4_count = Read(0x10);			//从93c46中读取按键S4计数到的最新值	  括号中的0x10为93c46中的一个地址
#ifdef sing
	sing_the_song();
#endif
	while(s1_flag == 1) {			//'=='为逻辑判断符
		PINMOD |= PWM1BOE;			//打开PWM输出功能 
		ad_to_pwm_and_segdisply();
		count_range();
		IrDA_receive();				//进行红外信号的接收
			
					
#ifndef internal_led
		display_flag = 1;	
#else
		display_flag = 0;
		led_disp();				//LED驱动显示
#endif

	}

}

//关机状态
void switch_offf()
{
	u8 i;

	IAP_Write(ad_addr, dat_temph);		//关机保存AD转换的值

	while (s1_flag == 2) {
		IrDA_receive();					//进行红外信号的接收
										//关机状态下进行红外信号的接收
//		key_scan();
#ifndef internal_led
		display_flag = 1; 
//		seg_send_weidata(0xff);		//关闭数码管显示
#else
		display_flag = 0;
		for (i = 0; i < 8; i++) 	//对LCD_RAM初始化为全正
			XBYTE[0xf000+i] = 0xff;
#endif
//		PINMOD = 0;						//测试发现关闭pwm后，P2.3输出默认为高电平
		PWM1DH  = 0x00;					//通过向PWM1DH中写0，使输出拉低
	}
	

}


//按键S3值得范围为0~9，按键S4之的范围为0~F
void count_range()
{

 	if (s3_count >= 10)
		s3_count = 0;
	if (s4_count >= 16)
		s4_count = 0;
	
	buffer[2] = s3_count;			 //将加计数值存储到相应的缓冲单元
	buffer[3] = s4_count;
}

//按键值变化时，将值记忆到EEPROM中
void EEPROM_record() 
{
	if(key_flag6 == 1) {			//按键值每变化一次向24c02记录一次
		key_flag6 = 0;
		c2404_write(buffer[2]);
		source_beep();

	}	

    if(key_flag7 == 1) {			//按键值每变化一次向93c46记录一次
		key_flag7 = 0;
		Write(0x10, buffer[3]);		   //0x10为存储地址
		source_beep();
	}	

}


//AD采集
void ad_conver()
{

  	if (cnt0 >= 250) {			//1s采样一次AD转换值
		cnt0 = 0;
		ADSOC = 1;			   //启动AD转换
		while (ADSOC == 1);    //ADSOC = AD start of conversion
		
		dat_temph = ADCDH;	   //取出高8位

	}
	
}


//IAP读数据功能,使用IAP功能keil必须设置为small存储模式
u8 IAP_Read(u16 addr)
{
	u8  dat_temp;

	SWCMD = 0x65;   	//使能IAP_ALL区的写功能
//	INTE1 = 0xa0;		//5274b/78b要加
	dat_temp = XBYTE[addr];
    SWCMD = 0x00;   	//写任意值关闭写功能
	return dat_temp;
}

//IAP写数据到rom
void IAP_Write(u16 addr, u8 dat)
{
   	SWCMD = 0x65;   	//使能IAP_ALL区的写功能
//	INTE1 = 0xa0;		//5274b/78b要加
	XBYTE[addr] = dat;
//	Timer0_delay(5);	//写入数据大约需500us,此处延时5ms
  	SWCMD = 0x00;   	//写任意值关闭写功能
}


//LED初始化
void led_controler()
{
	u8 i;

	//lcd默认时钟为src
	LCDCON2 |= LCDPSC_32;  //lcd进行32分频
	LCDCON2 |= SELLED;     //选择led模式
	LCDPIN |= LCDPIN_0;    //P3.4~P3.6,P1.7 mode;0: I/O mode;1: LCD/LED SEG4~7
	LCDCON |= LCDON;	  //开启lcd功能	

	for (i = 0; i < 8; i++) 	//对LCD_RAM初始化为全正
		XBYTE[0xf000+i] = 0xff;

}

//led数码管显示
void led_disp()
{
	com0_disp(buffer[3]);	  //显示按键S4加1计数的值
	com1_disp(buffer[2]);	  //显示按键S3加1计数的值
	com2_disp(buffer[1]);	  //显示AD转换值的高4位
	com3_disp(buffer[0]);	  //显示AD转换值的低4位
}

//lcd 配置
void lcd_controler()
{
	//lcd默认时钟为src，为独立的时钟源，可与系统时钟共存
	LCDCON2 |= LCDPSC_32;  //lcd进行32分频
//	LCDCON2 |= SELLED;     //选择led模式
	LCDPIN |= LCDPIN_0 | LCDPIN_1;    //P3.4~P3.6,P1.7 mode;0: I/O mode;1: LCD/LED SEG4~7
	LCDCON |= LCDON;	  //开启lcd功能	

}



//lcd 数码管显示
void lcd_seg_disp()
{
	u8 i;

   	lcd_controler();

   	for (i = 0; i < 8; i++) 	 //对LCD_RAM清零
		XBYTE[0xf000+i] = 0x00;

	XBYTE[0xf000] = 0x60;		//显示1
	XBYTE[0xf001] = 0x7d;	   //显示0

}



//AD值作为PWM占空比输入变量，并显示在数码管上
void ad_to_pwm_and_segdisply()
{
	ad_conver();				//AD转换
	buffer[1] = dat_temph/16;	//将AD的值通过数码管以十六进制的形式显示出来00~FF
	buffer[0] = dat_temph%16;
}

//--------------------------------
//使用数码管动态扫描显示数据
//--------------------------------

//数码管动态扫描
void segment_scan()
{

	 switch (com)
	 {
	 	case 0: 
			 seg_send_weidata(0x0f);		 //消隐处理
			 seg_send_duandata(duan_ma[buffer[0]]);	//送段码
			 seg_send_weidata(0x0e);		//送位码
			 com = 1;
			break;
		case 1: 
			 seg_send_weidata(0x0f);		//消隐
			 seg_send_duandata(duan_ma[buffer[1]]);	//送段码
			 seg_send_weidata(0x0d);		//送位码
			 com = 2;
			break;
		case 2: 
			 seg_send_weidata(0x0f);		//消隐
			 seg_send_duandata(duan_ma[buffer[2]]);	//送段码
			 seg_send_weidata(0x0b);		//送位码
			 com = 3;
			 break;
		case 3: 
			 seg_send_weidata(0x0f);		//消隐处理
			 seg_send_duandata(duan_ma[buffer[3]]);	//送段码
			 seg_send_weidata(0x07);		//送位码
			 com = 0;
			 break;
		default:
			break;
	}


}

//数码管动态扫描之送段码数据
void seg_send_duandata(u8 buffer)
{
//  P0 = (P0&0x0f)|_crol_(buffer&0x0f,4);  		//对应P0.4~P0.7

//	P3 = (P3&0x8f)|(buffer & 0x70);			  	//对应P3.4~P3.6	  该条语句与按键K1输入相冲突
//	P1 = (P1&0x7f)|(buffer & 0x80);				//对应P1.7
    P0_4 = buffer & 0x01;						//使用位操作符解决取值问题，高效，简单
	P0_5 = buffer & 0x02;
	P0_6 = buffer & 0x04;
	P0_7 = buffer & 0x08;
	P3_4 = buffer & 0x10;
	P3_5 = buffer & 0x20;
	P3_6 = buffer & 0x40;
	P1_7 = buffer & 0x80;
}

//数码管动态扫描之送位码数据
void seg_send_weidata(u8 buffer)
{
//   	P0 = (P0&0xf0)|buffer;
	P0_0 = buffer & 0x01;						//使用位操作符解决取值问题，高效，简单
	P0_1 = buffer & 0x02;
	P0_2 = buffer & 0x04;
	P0_3 = buffer & 0x08;
}
	


//有源蜂鸣器
void source_beep(void)
{
	if(beep_flg) 
		BUZZER = 1;
	if(buzzer_cnt >= 80) {
		BUZZER = 0;
		buzzer_cnt = 0;
		beep_flg = 0;
	}	

}










