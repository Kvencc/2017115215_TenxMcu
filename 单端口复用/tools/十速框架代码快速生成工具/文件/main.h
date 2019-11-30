
#ifndef __main_h
#define __main_h

//Hal---------------

//Const---------------
#define D_40ms 10        //basetime= 4ms
#define D_300ms	80	   //
#define D_500ms  125    //
#define D_800ms 200
#define D_1s   250      //
#define D_1min   60       //base= 1s
#define D_30min 30
#define D_1h   60   //min
#define D_2h   120   //min
#define D_4h   240  //min
#define D_8h 480  //min
#define D_9h	570
#define D_24h	1440
#define D_initTime 2 //s
#define D_clWfTime 5  //normal : 5 min  test : 2
#define D_hcWfTime 5    //normal : 5 min  test : 2
#define D_idleTime 60 //sec
#define D_setFlashTime	6 //sec
#define D_relayOffTime 6 //sec
#define D_maxSelIndex 6
//hw


#define D_temp  3
#define D_powerOnTimer 10 //min
#ifdef  MAIN_C
//var------------------
	bit bPowerOn ;
	bit bPowerOff;
  bit b500ms   ;
	bit b40ms   ;

	bit bWater100 ;
	bit bMicroHeat ;
	bit bMicroHeat2 ;
	bit bHeat ;

	bit bWfSetted ;

    bit b4ms ;

    uint8_t  timer125us, timer40ms, timer300ms,timer500ms,timer800ms, timer1s, timer1min, timer1h ;
    uint8_t  initTimer, idleTimer, setFlashTimer, setFirstWorkTimer ;
		uint16_t hwTimer, setHwTime, setWftime, wfTimer, orderTimer,setWftime2 ;
    uint8_t setHwTemp ;
    uint8_t selIndex ;
    uint8_t relayOffTimer ;
    uint8_t onTime, offTime, onOffTimer,powerOnTimer ;
		

#else

    extern bit b500ms ;
    extern bit b4ms ;
    extern uint8_t  timer125us, timer40ms, timer300ms, timer500ms, timer1s, timer1min, timer1h ;
    extern uint8_t  adjustTimer,wfTimer ;
	extern uint16_t hwTimer ;
    extern uint8_t setHwTemp ;
    extern uint8_t keyValue ;


#endif
//function------------------------

    void InitVar() ;
    void PowerOff(void);
    void DisplayDispatcher(void) ;
    void TimerProcess() ;
    void UserTaskSetting() ;
    void TasksProcess() ;
	void ChangeToFastClk(void);
	void StarShow();
	void init_IOMOD();
	void init_Timer();
#endif
