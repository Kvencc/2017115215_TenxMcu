#ifndef  __tempAd_h
    #define __tempAd_h
//Hal
	//ad0
	#tempAdH1
//Const
    #define D_shortValue 3000
    #define D_offValue   100
    #define D_padInvalidTime1  2  //s
	#define D_padInvalidTime2  3  //s
	#define D_padValidTime 10  //min
    #define D_tempChangeTime 30 //s
//Var
	#ifdef __tempAd_c
		bit bAdShort;			//��·
		bit bAdOff,bLastAdOff;				//��·
		bit bKettleValid;	//�к�״̬
    bit bHighTemp;		//�е�״̬
		uint8_t padInvalidTimer1, padInvalidTimer2;
		uint8_t padValidTimer;
		uint8_t curTemp , lastTemp, highTemp;
    uint8_t tempChangeTimer;
	#else
		extern bit  bAdShort ;
		extern bit  bAdOff ,bLastAdOff;
		extern bit  bKettleValid ;
    extern bit bHighTemp ;
		extern uint8_t	padInvalidTimer1,padInvalidTimer2 ;
		extern uint8_t padValidTimer	;
		extern uint8_t curTemp , lastTemp, highTemp ;
    extern uint8_t tempChangeTimer ;
	#endif
//Function
    void    AdInit(void) ;
    void    GetTemp(void)  ;
#endif
