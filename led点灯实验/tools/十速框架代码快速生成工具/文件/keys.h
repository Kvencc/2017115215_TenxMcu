#ifndef	_keys_h
#define	_keys_h	
//Hal----------------
#keyH1  
	
		
                        
//Const--------------
	#define D_keyDebounce  2
	#define D_longPress	60
	#define D_longPressHalf 50
	

	
	#define D_key1 1
	#define D_key2 2
	#define D_key3 3
	#define D_key4 4
	#define D_key5 5
	#define D_key6 6
	#define D_key7 7
	#define D_key8 8
	#define D_key9 9
	#define D_key10 10
	#define D_key11 11
	#define D_key12 12
	#define D_keyNull 0
	
//Var----------------
	#ifdef  __keys_c
        bit bKey ,bKeyPowerOff;
        uint8_t keyValue, keyDebounce,powerOffTime ;	
	#else
        extern bit bKey,bKeyPowerOff ;
        extern uint8_t keyValue, keyDebounce,powerOffTime ; 
	#endif

//Action Macro-------
		

//Function-----------

    void GetKeys(void) ;
#endif
