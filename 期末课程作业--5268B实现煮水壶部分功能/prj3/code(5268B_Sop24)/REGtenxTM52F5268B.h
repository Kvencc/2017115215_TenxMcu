
/*
******************************************************************************************************
Name		:TM52M5268B_64B.h
Version		:V1.1
Author		:
Date		:2015.08.06
Modify      :2.PWM1RPD -> PWM1PRD
             1.TT0 -> IT0
******************************************************************************************************
*/
#ifndef __TM52F5268_H__
#define __TM52F5268_H__

sfr     P0      =0x80;
sbit    P0_3    = P0^3;
sbit    P0_2    = P0^2;			  
sbit    P0_1    = P0^1;
sbit    P0_0    = P0^0;


sfr     SP      =0x81;
sfr     DPL     =0x82;
sfr     DPH     =0x83;
sfr     PCON    =0x87;
	//--------------------------------------------------------------------------------------------
	#define 	SMOD	0x80		//�����ʱ���λ
	//--------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------
	#define 	GF1		0x08		//�û��������ʹ��
	#define 	GF0		0x04		//�û��������ʹ��
	//--------------------------------------------------------------------------------------------
	#define 	PD		0x02		//��λ��1,оƬ����PDģʽ
	//--------------------------------------------------------------------------------------------
	#define 	IDL		0x01		//��λ��1,оƬ����IDLģʽ

//---------------------------
sfr     TCON    =0x88;
sbit    TF1     =TCON^7;
sbit    TR1     =TCON^6;
sbit    TF0     =TCON^5;
sbit    TR0     =TCON^4;
sbit    IE1     =TCON^3;
sbit    IT1     =TCON^2;
sbit    IE0     =TCON^1;
sbit    IT0     =TCON^0;

sfr     TMOD    =0x89;
	//--------------------------------------------------------------------------------------------
	#define 	T1Mask		0xf0		//T1����ģʽѡ��Mask
	//--------------------------------------------------------------------------------------------
	#define 	GATE1		0x80		//��ʱ��1�������ؿ���λ
					 	 	//��GATE1=1ʱ,INT1����Ϊ�ߵ�ƽ,ͬʱTCON�е�TR1����λΪ1ʱ,��ʱ/������1�ſ�ʼ����
					 	 	//��GATE1=0ʱ,��ֻҪ��TR1����λ��Ϊ1����ʱ/������1�Ϳ�ʼ����
	#define 	CT1		0x40		//��ʱ/������1���ܵ�ѡ��λ
					 	 	//CT1=1Ϊ������,ͨ���ⲿ����T1�����������
					 	 	//CT1=0Ϊ��ʱ��,���ڲ�ϵͳʱ���ṩ��ʱ��������
	//--------------------------------------------------------------------------------------------
	#define 	T1M0		0x00		//T1Ϊ13λ��ʱ/������
	#define 	T1M1		0x10		//T1Ϊ16λ��ʱ/������
	#define 	T1M2		0x20		//T1Ϊ8λ�Զ����ؼ���/��ʱ�� 
	#define 	T1M3		0x30		//������
	//--------------------------------------------------------------------------------------------
	#define 	T0Mask		0x0f		//T0����ģʽѡ��Mask
	//--------------------------------------------------------------------------------------------
	#define 	GATE0		0x08		//��ʱ��0�������ؿ���λ
					 	 	//��GATE0=1ʱ,INT0����Ϊ�ߵ�ƽ,ͬʱTCON�е�TR0����λΪ1ʱ,��ʱ/������0�ſ�ʼ����
					 	 	//��GATE0=0ʱ,��ֻҪ��TR0����λ��Ϊ1����ʱ/������0�Ϳ�ʼ����
	#define 	CT0		0x04		//��ʱ/������0���ܵ�ѡ��λ
					 	 	//CT0=1Ϊ������,ͨ���ⲿ����T0�����������
					 	 	//CT0=0Ϊ��ʱ��,���ڲ�ϵͳʱ���ṩ��ʱ��������
	//--------------------------------------------------------------------------------------------
	#define 	T0M0		0x00		//T0Ϊ13λ��ʱ/������ 
	#define 	T0M1		0x01		//T0Ϊ16λ��ʱ/������ 
	#define 	T0M2		0x02		//T0Ϊ8λ�Զ����ؼ���/��ʱ��
	#define 	T0M3		0x03		//��������T0,T0��Ϊ����������8λ��ʱ��/������TH0��TL0,�ڴ�ģʽ��T1ֹͣ����
sfr     TL0     =0x8a;
sfr     TL1     =0x8b;
sfr     TH0     =0x8c;
sfr     TH1     =0x8d;
//---------------------------
sfr     P1      =0x90;
sbit    P1_7    = P1^7;
sbit    P1_6    = P1^6;
sbit    P1_5    = P1^5;
sbit    P1_4    = P1^4;
sbit    P1_3    = P1^3;
sbit    P1_2    = P1^2;			  
sbit    P1_1    = P1^1;
sbit    P1_0    = P1^0;
/*
******************************************************************************************************
*/
sfr		P0OE		= 0x91;				//P0 CMOS Push-Pull Output Enable (1=Enable)

/*
******************************************************************************************************
*/
sfr		P2MOD		= 0x93;				//P2  
	//--------------------------------------------------------------------------------------------
	//P2MOD1:P2MOD Bit[3:2],P2.1 Pin Mode Control
	#define		P21MOD_Mask		~0xc0
	#define		P21MOD_0		0x00
	#define		P21MOD_1		0x40
	#define		P21MOD_2		0x80
	#define		P21MOD_3		0xC0
	//--------------------------------------------------------------------------------------------
	//P2MOD0:P2MOD Bit[1:0],P2.0 Pin Mode Control
	#define		P20MOD_Mask		~0x03
	#define		P20MOD_0		0x00
	#define		P20MOD_1		0x01
	#define		P20MOD_2		0x02
	#define		P20MOD_3		0x03
/*
******************************************************************************************************
*/
sfr     OPTION  =0x94;
	//--------------------------------------------------------------------------------------------
	#define 	UART1W		0x80		//One wire UART, both TXD/RXD use P3.1 pin
	//--------------------------------------------------------------------------------------------
	#define 	MODE3 		0x40		//mode 3v
	//--------------------------------------------------------------------------------------------
	#define 	WDTPSC_0	0x30		//Watch Dog Timer Prescale 3=Fastest
	#define 	WDTPSC_1	0x20		//Watch Dog Timer Prescale
	#define 	WDTPSC_2	0x10		//Watch Dog Timer Prescale
	#define 	WDTPSC_3	0x00		//Watch Dog Timer Prescale
	//--------------------------------------------------------------------------------------------
	#define 	AdcClk_32	0x00		//ADC Clock Rate:SysClk/32
	#define 	AdcClk_16	0x04		//ADC Clock Rate:SysClk/16
	#define 	AdcClk_8	0x08		//ADC Clock Rate:SysClk/8
	#define 	AdcClk_4	0x0C		//ADC Clock Rate:SysClk/4
	//--------------------------------------------------------------------------------------------
	#define 	TM3Psc_32768	0x00		
	#define 	AdcClk_16384	0x01		
	#define 	AdcClk_8192	0x02		
	#define 	AdcClk_128	0x03
sfr     INTFLG  =0x95;
	//--------------------------------------------------------------------------------------------
	#define		LVD		0x80		//Low Voltage Detect Flag
	//--------------------------------------------------------------------------------------------
	#define		TKIF	0x20		//Touch Key �жϱ�־��HW clear while TKSOC set
	//--------------------------------------------------------------------------------------------
	#define		ADIF	0x10		//ADC �жϱ�־��HW clear while ADSOC set
	//--------------------------------------------------------------------------------------------
	#define		IE2		0x04		//INT2 �жϱ�־��1=�ⲿ�ж�2�ж�
	//--------------------------------------------------------------------------------------------
	#define 	P1IF	0x02		//P1�˿��жϱ�־��1=P1�˿��ж�
	//--------------------------------------------------------------------------------------------
	#define 	TF3		0x01		//TM3�жϱ�־,1=TM3�ж�
sfr     P1WKUP  =0x96;
/*
******************************************************************************************************
*/
sfr		SWCMD		= 0x97;

//---------------------------
sfr     SCON    =0x98;
	//--------------------------------------------------------------------------------------------
	sbit 		SM0 		= SCON^7;	//���пڹ�����ʽ����λ
	sbit 		SM1 		= SCON^6;	//[SM0:SM1]=
					 	 	//00 ��ʽ0��������������Ƶ������:����Ƶ��/12
					 	 	//01 ��ʽ1���������ɶ�ʱ��T1��T2������ʺ�SMOD����:2SMOD*(T1�����)/32
					 	 	//10 ��ʽ2��������������Ƶ�ʺ�SMOD����:2SMOD*����Ƶ��/64
					 	 	//11 ��ʽ3���������ɶ�ʱ��T1��T2������ʺ�SMOD����:2SMOD*(T1�����)/32
	//--------------------------------------------------------------------------------------------
	sbit 		SM2 		= SCON^5;	//���ͨ�ſ���λ*/
							//���ͨ���ǹ����ڷ�ʽ2�ͷ�ʽ3��SM2λ��Ҫ���ڷ�ʽ2�ͷ�ʽ3����״̬
					 	 	//�����пڹ����ڷ�ʽ2��3:
					 	 	//��SM2=1ʱ,ֻ�е����յ���9λ����(RB8)Ϊ1ʱ,�Űѽ��յ���ǰ8λ��������SBUF,����λRI�����ж�����,����Ὣ���յ������ݷ���
					 	 	//��SM2=0ʱ,�Ͳ��ܵ�9λ������0����1,������������SBUF,�������ж�����,�����ڷ�ʽ0ʱ��SM2����Ϊ0
	//--------------------------------------------------------------------------------------------
	sbit 		REN 		= SCON^4;	//��������λ:
					 	 	//REN���ڿ������ݽ��յ������ͽ�ֹ,REN=1ʱ,��������,REN=0ʱ,��ֹ����
	//--------------------------------------------------------------------------------------------
	sbit 		TB8 		= SCON^3;	//�������ݵ�8λ
	sbit 		RB8 		= SCON^2;	//�������ݵ�8λ
	//--------------------------------------------------------------------------------------------
	sbit 		TI 		= SCON^1;	//�����жϱ�־λ��
					 	 	//��ʽ0ʱ,�������8λ���ݺ�,��Ӳ����λ
					 	 	//������ʽ��,��Ӳ����λ,TI=1��ʾ֡���ͽ���,TI������������
	//--------------------------------------------------------------------------------------------
	sbit 		RI 		= SCON^0;	//�����жϱ�־λ��
					 	 	//��ʽ0ʱ,�������8λ���ݺ�,��Ӳ����λ
					 	 	//������ʽ��,��Ӳ����λ,RI=1��ʾ֡�������
	
sfr     SBUF    =0x99;
sfr     PWM0PRD =0x9a;
sfr     PWM0DH  =0x9b;
sfr     PWM1PRD =0x9c;
sfr     PWM1DH  =0x9d;

//---------------------------
sfr     P2      =0xa0;
sbit    P2_1    = P2^1;
sbit    P2_0    = P2^0;

sfr     PWMCON  =0xa1;
	//--------------------------------------------------------------------------------------------
	#define		PWM1CKS_16M	0xC0		//PWM1 clock =FRC Double frequence
	#define		PWM1CKS_Div1	0x80            //PWM1 clock =SysClk/1
	#define		PWM1CKS_Div2	0x40            //PWM1 clock =SysClk/2
	#define		PWM1CKS_Div4	0x00            //PWM1 clock =SysClk/4
	//--------------------------------------------------------------------------------------------
	// PWM1DL  (bit5~bit4) 
	//--------------------------------------------------------------------------------------------                                              //
	#define		PWM0CKS_16M		0x0C		//PWM0 clock =FRC Double frequence
	#define		PWM0CKS_Div1	0x08            //PWM0 clock =SysClk/1
	#define		PWM0CKS_Div2	0x04            //PWM0 clock =SysClk/2
	#define		PWM0CKS_Div4	0x00            //PWM0 clock =SysClk/4
sfr     P1MODL  =0xa2;
	//--------------------------------------------------------------------------------------------
	//P1MOD3:P1MODL Bit[7:6],P1.3 Pin Mode Control
	#define		P13MOD_Mask		~0xc0
	#define		P13MOD_0		0x00
	#define		P13MOD_1		0x40
	#define		P13MOD_2		0x80
	#define		P13MOD_3		0xC0
	//--------------------------------------------------------------------------------------------
	//P1MOD2:P1MODL Bit[5:4],P1.2 Pin Mode Control
	#define		P12MOD_Mask		~0x30
	#define		P12MOD_0		0x00
	#define		P12MOD_1		0x10
	#define		P12MOD_2		0x20
	#define		P12MOD_3		0x30
	//--------------------------------------------------------------------------------------------
	//P1MOD1:P1MODL Bit[3:2],P1.1 Pin Mode Control
	#define		P11MOD_Mask		~0x0C
	#define		P11MOD_0		0x00
	#define		P11MOD_1		0x04
	#define		P11MOD_2		0x08
	#define		P11MOD_3		0x0C
	//--------------------------------------------------------------------------------------------
	//P1MOD0:P1MODL Bit[1:0],P1.0 Pin Mode Control
	#define		P10MOD_Mask		~0x03
	#define		P10MOD_0		0x00
	#define		P10MOD_1		0x01
	#define		P10MOD_2		0x02
	#define		P10MOD_3		0x03
sfr     P1MODH  =0xa3;
	//--------------------------------------------------------------------------------------------
	//P1MOD7:P1MODH Bit[7:6],P1.7 Pin Mode Control
	#define		P17MOD_Mask		~0xc0
	#define		P17MOD_0		0x00
	#define		P17MOD_1		0x40
	#define		P17MOD_2		0x80
	#define		P17MOD_3		0xc0
	//--------------------------------------------------------------------------------------------
	//P1MOD6:P1MODH Bit[5:4],P1.6 Pin Mode Control
	#define		P16MOD_Mask		~0x30
	#define		P16MOD_0		0x00
	#define		P16MOD_1		0x10
	#define		P16MOD_2		0x20
	#define		P16MOD_3		0x30
	//--------------------------------------------------------------------------------------------
	//P1MOD5:P1MODH Bit[3:2],P1.5 Pin Mode Control
	#define		P15MOD_Mask		~0x0c
	#define		P15MOD_0		0x00
	#define		P15MOD_1		0x04
	#define		P15MOD_2		0x08
	#define		P15MOD_3		0x0c
	//--------------------------------------------------------------------------------------------
	//P1MOD4:P1MODH Bit[1:0],P1.4 Pin Mode Control
	#define		P14MOD_Mask		~0x03
	#define		P14MOD_0		0x00
	#define		P14MOD_1		0x01
	#define		P14MOD_2		0x02
	#define		P14MOD_3		0x03
sfr     P3MODL  =0xa4;
	//--------------------------------------------------------------------------------------------
	//P3MOD3:P3MODL Bit[7:6],P3.3 Pin Mode Control
	#define		P33MOD_Mask		~0xc0
	#define		P33MOD_0		0x00
	#define		P33MOD_1		0x40
	#define		P33MOD_2		0x80
	#define		P33MOD_3		0xc0
	//--------------------------------------------------------------------------------------------
	//P3MOD2:P3MODL Bit[5:4],P3.2 Pin Mode Control
	#define		P32MOD_Mask		~0x30
	#define		P32MOD_0		0x00
	#define		P32MOD_1		0x10
	#define		P32MOD_2		0x20
	#define		P32MOD_3		0x30
	//--------------------------------------------------------------------------------------------
	//P3MOD1:P3MODL Bit[3:2],P3.1 Pin Mode Control
	#define		P31MOD_Mask		~0x0c
	#define		P31MOD_0		0x00
	#define		P31MOD_1		0x04
	#define		P31MOD_2		0x08
	#define		P31MOD_3		0x0c
	//--------------------------------------------------------------------------------------------
	//P3MOD0:P3MODL Bit[1:0],P3.0 Pin Mode Control
	#define		P30MOD_Mask		~0x03
	#define		P30MOD_0		0x00
	#define		P30MOD_1		0x01
	#define		P30MOD_2		0x02
	#define		P30MOD_3		0x03
sfr     P3MODH  =0xa5;	
	//--------------------------------------------------------------------------------------------
	//T0OE:P3MODH Bit[7],"Timer0 overflow divided by 64"signal output to P3.4 pin
	#define		T0OE    		0x80
	//--------------------------------------------------------------------------------------------
	//P3MOD6:P3MODH Bit[5:4],P3.6 Pin Mode Control
	#define		P36MOD_Mask		~0x30
	#define		P36MOD_0		0x00
	#define		P36MOD_1		0x10
	#define		P36MOD_2		0x20
	#define		P36MOD_3		0x30
	//--------------------------------------------------------------------------------------------
	//P3MOD5:P3MODH Bit[3:2],P3.5 Pin Mode Control
	#define		P35MOD_Mask		~0x0c
	#define		P35MOD_0		0x00
	#define		P35MOD_1		0x04
	#define		P35MOD_2		0x08
	#define		P35MOD_3		0x0c
	//--------------------------------------------------------------------------------------------
	//P3MOD4:P3MODH Bit[1:0],P3.4 Pin Mode Control
	#define		P34MOD_Mask		~0x03
	#define		P34MOD_0		0x00
	#define		P34MOD_1		0x01
	#define		P34MOD_2		0x02
	#define		P34MOD_3		0x03
sfr     PINMOD  =0xa6;
	#define		PWM1AOE		0x80//Set to enable PWM1A and signal output to P1.3 pin
	#define		PWM0AOE		0x20//Set to enable PWM0A and signal output to P1.2 pin
	#define		TCOE		  0x08//Set to output "Instruction Cycle Clock " signal to P1.4 pin
	#define		T2OE		  0x04//Set to output "Timer2 overflow divided by 2" signal to P1.0 pin
//---------------------------	
sfr     IE      =0xa8;
	//--------------------------------------------------------------------------------------------
	sbit 		EA 			= IE^7;		//EA=0ʱ,�����жϽ�ֹ;EA=1ʱ,���жϵĲ����ɸ��������λ����
	sbit 		ET2 		= IE^5;		//��ʱ��2�жϳ���
	sbit 		ES 			= IE^4;		//���п��жϳ���(ES=1����,ES=0��ֹ)
	sbit 		ET1 		= IE^3;		//��ʱ��1�жϳ���
	sbit 		EX1 		= IE^2;		//���ж�INT1�жϳ���
	sbit 		ET0 		= IE^1;		//��ʱ��0�жϳ���
	sbit 		EX0 		= IE^0;		//�ⲿ�ж�INT0���ж�����
	
sfr     INTE1   =0xa9;		
    //-------------------------------------------------------------------------------------------------------
	//IAPдʹ��-->INTE1=(INTE1&~IAPWE_Mask)|IAPWE_En;(����д��Ҫ)
	//IAPд��ֹ-->INTE1=(INTE1&~IAPWE_Mask)|IAPWE_Dis;
	
	#define 	IAPWE_Mask	0xE0
	#define 	IAPWE_En	0xA0
	#define 	IAPWE_Dis	0x00
	//--------------------------------------------------------------------------------------------
	#define		SPIE		0x10		//SPI �ж�����
	//--------------------------------------------------------------------------------------------
	#define		ADTKIE  0x08		//ADC/Touch Key  �ж�����
	//--------------------------------------------------------------------------------------------
	#define		EX2			0x04		//INT2 �ж�������Stop Mode ���ѹ�������
	//--------------------------------------------------------------------------------------------
	#define	  P1IE		0x02		//P1�˿��ж�����
	//--------------------------------------------------------------------------------------------
	#define		TM3IE		0x01		//TM3�ж�����		
sfr     ADTKDT  =0xaa;		
	//--------------------------------------------------------------------------------------------
	//ADCDL:ADTKDT Bit[7:4],ADC Data LSB 3~0
	#define		TKEOC		0x08		//Touch Key End of Conversion
	#define		TKOVF		0x04		//Touch Key Counter Overflow
	//--------------------------------------------------------------------------------------------
	//TKDH:ADTKDT Bit[1:0],Touch Key Data MSB 9~8
sfr     ADCDH   =0xab;
sfr     TKDL    =0xac;
sfr     TKCON   =0xad;
	//--------------------------------------------------------------------------------------------
	//TKPD:TKCON Bit[7],Touch Key Power Down
	#define		TKPD		0x80		//0: Touch Key Running ;1: Touch Key Power Down
	//--------------------------------------------------------------------------------------------
	//TKTMR:TKCON Bit[2:0],Touch Key Conversion Time
	#define		TKTMR_Mask		 ~0x07		//TKTMR_Mask
	#define		TKTMR_short    0x00		  //shortest
//...
	#define		TKTMR_long     0x07		  //longest
sfr     CHSEL   =0xae;
	//--------------------------------------------------------------------------------------------
	//ADCHS:CHSEL Bit[7:4],ADC Channel Select
                 //0000: AD0 (P3.3)
                 //0001: AD1 (P3.2)
                 //0010: AD2 (P3.1)
                 //0011: AD3 (P3.0)
                 //0100: AD4 (P1.0)
                 //0101: AD5 (P1.1)
                 //0110: AD6 (P1.2)
                 //0111: AD7 (P1.3)
                 //1000: AD8 (P1.4)
                 //1001: AD9 (P1.5)
                 //1010: VSS
                 //1011: VBG (Internal Reference Voltage)
                 //11xx: Reserved	
	//--------------------------------------------------------------------------------------------
	//TKCHS:TKCON Bit[3:0],Touch Key Channel Select
                 //0000: TK0 (P1.0)
                 //0001: TK1 (P1.1)
                 //0010: TK2 (P1.2)
                 //0011: TK3 (P1.3)
                 //0100: TK4 (P3.3)
                 //0101: TK5 (P3.2)
                 //0110: TK6 (P3.1)
                 //0111: TK7 (P3.0)
                 //1000: TK8 (P1.4)
                 //1001: TK9 (P1.6)
                 //1010: TK10 (P1.7)
                 //1011: TK11 (P3.6)
                 //1100: TK12 (P3.5)
                 //1101: TK13 (P3.4)
                 //11xx: Reserved
/*
******************************************************************************************************
*/
sfr		TKCON2		= 0xAF;
	//ATKDT:TKCON2 Bit[7:4],Auto Touch Key Scan Result
	//--------------------------------------------------------------------------------------------
	//TKAUTO:TKCON2 Bit[3],Touch Key Auto Scan Mode Enable
	#define		TKAUTO		0x08		//0: Touch Key Running ;1: Touch Key Power Down
	//--------------------------------------------------------------------------------------------
	//TKSCNRT:TKCON2 Bit[2],Touch Key Auto Scan Rate ,0=125mS,1=62mS
	#define		TKSCNRT		0x04		//0=125mS,1=62mS
	//--------------------------------------------------------------------------------------------
	//TKSCNUM:TKCON2 Bit[1:0],Touch Key Auto Scan Number
	#define		TKSCNUM1	0x00		//1 channel
	#define		TKSCNUM4	0x03		//4 channel

//---------------------------
sfr     P3      =0xb0;
sbit    P3_7    = P3^7;
sbit    P3_6    = P3^6;
sbit    P3_5    = P3^5;
sbit    P3_4    = P3^4;
sbit    P3_3    = P3^3;
sbit    P3_2    = P3^2;			  
sbit    P3_1    = P3^1;
sbit    P3_0    = P3^0;

//---------------------------
sfr     IP      =0xb8;
	//--------------------------------------------------------------------------------------------
	sbit		PT2			  = IP^5;		//��ʱ2�ж����ȼ���λ
	sbit 		PS			  = IP^4;		//���п��ж����ȼ���λ
	sbit 		PT1	    	= IP^3;		//��ʱ1�ж����ȼ���λ
	sbit 		PX1	    	= IP^2;		//���ж�INT1�ж����ȼ���λ
	sbit 		PT0	    	= IP^1;		//��ʱ0�ж����ȼ���λ
	sbit 		PX0	    	= IP^0;		//���ж�INT0�ж����ȼ���λ

sfr     IPH     =0xb9;
	//--------------------------------------------------------------------------------------------	
	#define	  	PT2H		0x20 		//Timer2�ж����ȼ���λ����
	#define	  	PSH		  0x10 		//�����ж����ȼ���λ����
	#define	  	PT1H		0x08 		//Timer1�ж����ȼ���λ����
	#define	  	PX1H		0x04 		//XINT1�ж����ȼ���λ���� 
	#define	  	PT0H		0x02 		//Timer0�ж����ȼ���λ����
	#define		  PX0H		0x01 		//XINT0�ж����ȼ���λ����
sfr     IP1     =0xba;
	//--------------------------------------------------------------------------------------------
	#define		  PSPI		0x10		//SPI�ж����ȼ���λ
	#define	  	PADTKI  0x08		//ADC/Touch Key�ж����ȵ�λ����
	#define	  	PX2		  0x04		//XINT2�ж����ȵ�λ����
	#define	  	PP1		  0x02		//Port1�ж����ȵ�λ����
	#define		  PT3		  0x01		//Timer3�ж����ȵ�λ����
sfr     IP1H    =0xbb;
	//--------------------------------------------------------------------------------------------
	#define		  PSPIH 	0x10		//SPI�ж����ȼ���λ
	#define 	  PADTKIH	0x08;		//ADC/Touch Key �ж����ȼ���λ
	#define		  PX2H		0x04		//XIN T2�ж����ȼ���λ
	#define 	  PP1H		0x02;		//P1�ж����ȼ���λ
	#define 	  PT3H    0x01;		//��ʱ3�ж����ȼ���λ

/*
******************************************************************************************************
*/
sfr   SPCON     = 0xBC;
	#define		SPCON_Mask	~0xFF		//
	#define		SPEN    0x80		//SPI Enable.0: SPI Enable;1: SPI Disable
	#define		MSTR    0x40 	  //Master Mode Enable.0: Slave Mode;1: Master Mode
	#define		CPOL    0x20	  //SPI Clock Polarity.0: SCK is low in idle state;1: SCK is high in idle state
	#define		CPHA    0x10		//SPI Clock Phase.0: Data sampled on first edge of SCK period;1: Data sampled on second edge of SCK period
	#define		SSDIS   0x08		//Pin Disable.0: Enable   pin;1: Disable   pin
	#define		LSBF    0x04 	  //LSB First.0: MSB first;1: LSB first
	//--------------------------------------------------------------------------------------------
	//SPCR:SPCON Bit[1:0], SPI Clock Rate.
	#define		SPCR_2  0x00	  //FSYSCLK/2
	#define		SPCR_4  0x01	  //FSYSCLK/4
	#define		SPCR_8  0x02	  //FSYSCLK/8
	#define		SPCR_16 0x03	  //FSYSCLK/16
/*
******************************************************************************************************
*/
sfr   SPSTA     = 0xBD;
	#define		SPSTA_Mask	~0xFC		//
	#define		SPIF    0x80		//SPI Interrupt Flag,This bit is set by H/W at the end of a data transfer,Cleared by H/W when interrupt is vectored into
	#define		WCOL    0x40 	  //Write Collision Interrupt Flag,This bit is set by H/W if write data to SPDAT when SPBSY is set.Write 0 to this bit or rewrite data to SPDAT when SPBYS is cleared will clear this flag.
	#define		MODF    0x20	  //Mode Fault Interrupt Flag,This bit is set by H/W when SSDIS is cleared and NSS pin is pulled low in Master mode.Write 0 to this bit will clear this flag.When this bit is set, the SPEN and MSTR in SPCON will be cleared by hardware
	#define		RCVOVF  0x10		//Receive Buffer Overrun Flag,This bit is set by H/W at the end of a data transfer and RCVBF is set.Write 0 to this bit or read SPDAT register will clear this flag.
	#define		RCVBF   0x08		//Receive Buffer Full Flag,This bit is set by H/W at the end of a data transfer.Write 0 to this bit or read SPDAT register will clear this flag.
	#define		SPBSY   0x04 	  //SPI Busy Flag (Read Only),This bit is set by H/W when a SPI transfer is progress.
/*
******************************************************************************************************
*/
sfr   SPDAT     = 0xBE;         //SPI Transmit and Receive Data
/*
******************************************************************************************************
*/
sfr   ATKCMP10H = 0xC2;         //
	//--------------------------------------------------------------------------------------------
	//ATKCMP1:ATKCMP10H Bit[6:4], Auto Touch Key Scan Channel 1 Compare Data bit 10~8.
	//--------------------------------------------------------------------------------------------
	//ATKCMP0:ATKCMP10H Bit[2:0], Auto Touch Key Scan Channel 0 Compare Data bit 10~8.
/*
******************************************************************************************************
*/
sfr   ATKCMP32H = 0xC3;         //
	//--------------------------------------------------------------------------------------------
	//ATKCMP3:ATKCMP32H Bit[6:4], Auto Touch Key Scan Channel 3 Compare Data bit 10~8.
	//--------------------------------------------------------------------------------------------
	//ATKCMP2:ATKCMP32H Bit[2:0], Auto Touch Key Scan Channel 2 Compare Data bit 10~8.
/*
******************************************************************************************************
*/
sfr   ATKCMP0   = 0xC4;         //Auto Touch Key Scan Channel 0 Compare Data bit 7~0.
/*
******************************************************************************************************
*/
sfr   ATKCMP1   = 0xC5;         //Auto Touch Key Scan Channel 1 Compare Data bit 7~0.
/*
******************************************************************************************************
*/
sfr   ATKCMP2   = 0xC6;         //Auto Touch Key Scan Channel 2 Compare Data bit 7~0.
/*
******************************************************************************************************
*/
sfr   ATKCMP3   = 0xC7;         //Auto Touch Key Scan Channel 3 Compare Data bit 7~0.
//---------------------------
sfr     T2CON   =0xc8;
	//--------------------------------------------------------------------------------------------
	sbit 		TF2  	  =	T2CON^7 ;	//TM2����жϱ�־��TF2�������û������塰0������TM2��Ϊ���ڲ����ʷ�����ʱ��TF2���ᱻ�á�1����
	sbit 		EXF2    =	T2CON^6	;	//��ʱ��TM2�ⲿ�жϱ�־��EXEN2Ϊ1ʱ����T2EX��P1.1������������ʱ��1�жϱ�־EXF2��EXF2�������û������塰0����
	sbit  	RCLK    =	T2CON^5	;	//���нӿڵķ���ʱ��ѡ���־��TCLK=1ʱ��T2�����ڲ����ʷ�������ʽ��
	sbit  	TCLK 	  =	T2CON^4	;	//���нӿڵĽ���ʱ��ѡ���־λ��RCLK��1ʱ��T2�����ڲ����ʷ�������ʽ��
	sbit  	EXEN2   =	T2CON^3	;	//TM2���ⲿ�жϳ�����־��
	sbit 		TR2     =	T2CON^2	;	//TM2����/��ʱ����λ��TR2Ϊ1ʱ����������Ϊ0ʱ��ֹ����
	sbit 		CT2     =	T2CON^1	;	//�ⲿ������/��ʱ��ѡ��λ��C/T2=1ʱ��T2Ϊ�ⲿ�¼���������������������T2��P1.0����C/T2=0ʱ��T2Ϊ��ʱ�����������ʮ����Ƶ�ź���Ϊ�����źš�
	sbit    CPRL2   =	T2CON^0	;	//��׽�ͳ����Զ���װ�뷽ʽѡ��λ��Ϊ1ʱ�����ڲ�׽��ʽ��Ϊ0ʱTM2�����ڳ����Զ���װ�뷽ʽ����TCLK��RCLKΪ1ʱ��CP/RL2�����ԣ�T2���ǹ����ڳ����Զ���װ�뷽ʽ��

sfr     RCP2L   =0xca;
sfr     RCP2H   =0xcb;
sfr     TL2     =0xcc;
sfr     TH2     =0xcd;

sfr     PSW     =0xd0;
	//--------------------------------------------------------------------------------------------
	sbit 		CY 		= PSW^7;	//��λ��־,�н����λ,CY��1;�޽����λ,CY��0
	sbit 		AC 		= PSW^6;	//���λ��־
	sbit 		F0 		= PSW^5;	//�û��������ʹ��
	sbit 		RS1 	= PSW^4;	//�����Ĵ�����ѡ��[RS1:RS0]
	sbit 		RS0 	= PSW^3;	//00--0��,01--1��,10--2��,11--3��
	sbit 		OV 		= PSW^2;	//����������������,�����,OV=1;�����,OV��0
  sbit    F1    = PSW^1;
	sbit 		P 		= PSW^0;	//������ʾALU�������ж�������λ1�ĸ�������ż��,

//---------------------------
sfr     CLKCON  =0xd8;
	//--------------------------------------------------------------------------------------------
	sbit		SCKTYPE		=CLKCON^7;		//Slow Clock Type. 0=SRC, 1=SXT
	sbit		FCKTYPE		=CLKCON^6;		//Fast Clock Type. 0=FRC, 1=FXT
	sbit		STPPCK		=CLKCON^4;		//Stop UART/Timer0/Timer1/Timer2/ADC Clock in Idle mode
	sbit		STPFCK		=CLKCON^3;		//Stop Fast Clock
	sbit		SELFCK      =CLKCON^2;		//Select Fast Clock	
	//--------------------------------------------------------------------------------------------
	#define		CLKPSC_div16 0x00
	#define		CLKPSC_div4	 0x01
	#define		CLKPSC_div2	 0x02
	#define		CLKPSC_div1	 0x03

sfr     ACC     =0xe0;
sfr     B       =0xf0;
sfr     CFGWL   =0xf7;
	//--------------------------------------------------------------------------------------------
	#define 	WDTEMask	0xC0		//
	#define 	WDTE11		0xC0		//WDT����ʹ��
	#define 	WDTE10		0x80		//WDTʹ��,����IDLE/PDOWNģʽ�½�ֹ
	#define 	WDTE0X		0x00		//WDT���ǽ�ֹ
	
	
 	#define 	IRCMask		0x0F		//

//---------------------------
sfr     AUX1    =0xf8;
	//--------------------------------------------------------------------------------------------
    sbit 		CLRWDT		= AUX1^7;
    sbit 		CLRTM3		= AUX1^6;//����TM3Ҳ������TM3
    sbit 		TKSOC		  = AUX1^5;//��������ʼ������ʱ�Զ�����
    sbit 		ADSOC		  = AUX1^4;//ADC��ʼ������ʱӲ���Զ�����
    sbit 		CLRPWM0		= AUX1^3;
    sbit 		DPSEL		  = AUX1^0;//0��ѡ��DPTR;1��ѡ��DPTR1
/*
******************************************************************************************************
*/	
sfr 	ICECON 		= 0xF9;
	#define 	HWBRK		          0x80		//H/W Break
	#define 	RETROREQ          0x40		//Retro-OPCode Request,HW set at SWBRK,clear at NMI return
	#define 	TXRDY		          0x20		//Transmitt Ready
	#define 	CMDRDY	          0x10		//Ready for Command
	#define 	XFIRCK	          0x08		//Swich to FIRC 4MHZ
	#define 	WRFAIL	          0x01		//EEPROM Write Fail
/*
******************************************************************************************************
*/	
sfr 	RETROCODE	= 0xFA;//ICE Mode Retro-OPCode
/*
******************************************************************************************************
*/	
sfr 	ICERCD 		= 0xFB;//ICE Mode Receive Data
/*
******************************************************************************************************
*/	
sfr 	ICECMDL		= 0xFC;//ICE Mode Command Low Byte
/*
******************************************************************************************************
*/	
sfr 	ICECMDH		= 0xFD;//ICE Mode Command High Byte
/*
******************************************************************************************************
*/	
sfr 	ICETXD 		= 0xFE;//ICE Mode Transmit Data
/*
******************************************************************************************************
*/	
sfr 	INDSFR 		= 0xFF;//SFR direct Adr replaced by ICECMDL in NMI"mov dir,a"&"mov a,dir"
/*
******************************************************************************************************
*/
#define	 All_Interrupt_Enable()		do{EA = 1;}while(0)		//ȫ���ж�ʹ��
#define	 All_Interrupt_Disable()	do{EA = 0;}while(0)		//ȫ���жϹر�
/*
******************************************************************************************************
*/
#define	 PowerDown()			do{PCON = PCON | PD;}while(0)	//�������ģʽ
#define	 PowerIdel()			do{PCON = PCON | IDL;}while(0)	//����IDELģʽ
#endif
