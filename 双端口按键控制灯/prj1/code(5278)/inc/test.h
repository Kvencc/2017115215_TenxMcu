#ifndef _TEST_H_
#define _TEST_H_

//uint uchar宏定义
#define u8 		unsigned char
#define u16	 	unsigned int
#define uchar 	unsigned char
#define uint 	unsigned int


#define switch_addr 0x1f00		 //开关机状态存储地址
#define ad_addr		0x1f01		 //AD值存储地址

#define switch_on	0x01		 //开机
#define switch_off	0x00		 //关机
/*------------------------------------------------
 *	  		功能选择
/*------------------------------------------------ */
//#define	internal_led				//注释掉该项为数码管动态扫描方式显示，不注释为内部led驱动显示
									//注意使用内部LED驱动的情况下红外接收是正常的，动态扫描还不好
//#define 	sing					//去掉注释开机通过无源蜂鸣器先唱歌，再点亮数码管
/*-------------------------------------------------*/
#define BUZZER P1_6

u8 bdata	key_flag;  				//按键标识位

//--------------------------------------------------------------------------------------------
sbit 		key_flag7		= key_flag^7;
sbit 		key_flag6		= key_flag^6;	
sbit 		key_flag5		= key_flag^5;	
sbit 		key_flag4		= key_flag^4;	
sbit 		key_flag3		= key_flag^3;	
sbit 		key_flag2		= key_flag^2;	
sbit 		key_flag1		= key_flag^1;	
sbit 		key_flag0		= key_flag^0;		



//系统时钟初始化
void sys_clk_init(void);

//GPIO初始化
void gpio_init(void);

//ADC初始化
void adc_init(void);

//PWM初始化
void pwm_init(void);

//中断0初始化
void int0_init(void);

//定时器0初始化
void timer0_init(void);

//定时器1初始化  定时约5.5个微秒
void timer1_init(void);	  	


//定时器2初始化
void timer2_init(void);


//按键扫描
void key_scan(void);

//AD采集，并显示
void ad_conver(void);

//AD显示
void ad_display(void);

//串口初始化
void uart_init(void);

//发送一个字节
void SendByte(unsigned char dat);

//发送int型数据
void SendWord(unsigned int dat);

//发送一个字符串
void SendStr(unsigned char *s);

//IAP操作
u8 IAP_Read(u16 addr);
void IAP_Write(u16 addr, u8 dat);

//LED初始化
void led_controler(void);

//LED显示
void led_disp(void);


//lcd初始化

void lcd_controler(void);

//LCD数码管显示
void lcd_seg_disp(void);

//SPI初始化
void spi_init(void);


//数码管测试函数
void Segment8_4(void);

//数码管动态扫描
void segment_scan(void);

//数码管动态扫描之送段码数据
void seg_send_duandata(u8 buffer);

//数码管动态扫描之送位码数据
void seg_send_weidata(u8 buffer);


////数码管动态扫描之定时器0延时
//void Timer0_delay(u16 ms);


//AD值作为PWM占空比输入变量，并显示在数码管上
void ad_to_pwm_and_segdisply(void);

//按键值变化时，将值记忆到EEPROM中
void EEPROM_record(void); 

//开机状态
void switch_onn(void);		//注意：函数名不能与宏定义名重复

//关机状态
void switch_offf(void);

//IAP记录开关机状态
void  switch_rec(void);

//按键S3,S4值得范围为0~9
void count_range(void);

//有源蜂鸣器
void source_beep(void);

//红外信号对开关机、计数器的处理
void IrDA_process(void);



#endif