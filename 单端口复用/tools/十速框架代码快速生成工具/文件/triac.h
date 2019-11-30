#ifndef __triac_h
#define __triac_h

//Hal------------------
#triacH1
//Const-----------------
#define D_triacHoldTime   4 //base 0.25ms
#define D_fireType_0_16		0x0000
#define D_fireType_1_16		0x0001
#define D_fireType_2_16		0x0003
#define D_fireType_3_16		0x0013
#define D_fireType_4_16		0x0033
#define D_fireType_5_16		0x0037
#define D_fireType_6_16		0x0333
#define D_fireType_8_16 	0x00ff
#define D_fireType_16_16	0xffff




//Var-----------------
	#ifdef __triac_c
		bit bLastZero ;
		bit bZero ;
		bit bDelay ;
		bit bWattSetted ;
		bit	bAlarm ;
		bit bRelayOn ;
		uint16_t wfFireType,fireType,wfFireType2 ;
		uint8_t triacTimer ,delayTimer ;

	#else
		extern bit bLastZero ;
		extern bit bZero ;
		extern bit bDelay ;
		extern bit bWattSetted ;
		extern bit	bAlarm ;
		extern bit bRelayOn ;
		extern uint16_t wfFireType,fireType, wfFireType2;
		extern uint8_t triacTimer ,delayTimer ;
		extern uint8_t zeroCounter ;
	#endif
//Function-------------------
void InitTriac() ;


#endif
