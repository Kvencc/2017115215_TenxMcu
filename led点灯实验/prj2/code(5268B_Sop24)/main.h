
#ifndef __main_h
#define __main_h



//Hal---------------
#define F_csOn()   P0_1 = 1; bMotorOn = 1
#define F_csOff()  P0_1 = 0; bMotorOn = 0
#define F_ssOn()   P1_7 = 1; bSsRelayOn = 1
#define F_ssOff()  P1_7 = 0; bSsRelayOn = 0
//#define F_xdOn()	P2_1 = 1; bXdRelayOn =1
//#define F_xdOff()	P2_1 = 0; bXdRelayOn =0
//Const---------------------------------------
#define D_40ms  20         //basetime  4ms
#define D_500ms  125
#define D_1s   250       //basetime  4ms
#define D_1m   60       //
#define D_1h   60

#define D_assWfTime    15 //min
#define D_idleTime  60   //0.5s*60 = 30s
#define D_tempChangeTime  30 //25s
#define D_tempAdjustTime 3 //5s
#define D_csTimeAdjustTime 2 //2s
#define D_defaultHwTemp 60 //度
#define D_hwTime 15
#define D_hw100Time 15
#define D_highStep  2
#define D_hwStep    7

#define D_assCsTime 32  //28s
#define D_hcsTime 24   //20s
#define D_xdTime  8   //8min
#define D_boilCount 3

#define D_relayOffTime 5
#define D_wfOnTime  3
#define D_wfOffTime 2
//keyValue
//#define D_keyHxd   1
//#define D_keyHw   2
#define D_keyHcsOn   11
#define D_keyHcsOff   1
#define D_keyHss   2
#define D_keyAss   3
#define D_keyPower 4
#define D_longPressCount  50

#define D_hwTableSize 7


#ifdef  MAIN_C
//var------------------
bit b4ms;
bit bPowerOn;
bit bSsRelayOn;
bit bXdRelayOn;
bit bMotorOn;
bit bHcsOn;
bit bAssToHcsOn;
bit bAssOn;
bit bHssOn;
bit bHxdOn;
bit bHwOn;
bit b500ms;
bit b40ms;
bit bAuto;
bit bHighTemp;
bit bLedFlash;
bit bIdle;
bit bResetStepMotor;
bit bAdTest;
bit bTempAdjust;
bit bWater100;
bit bMicroHeat;
bit bSsDelay;
bit bWfSetted;
bit bSelfTest;
bit bCsAdjust;
bit bCsing;

uint8_t tick, timer40ms, timer500ms, timer1s, timer1m, timer1h;
uint8_t csTimer, csTimerBack, xdTimer, wfTimer, hssTimer;
uint8_t tempChangeTimer;
uint8_t tempAdjustTimer;
uint8_t settedTemp, highTemp;
uint8_t keyValue;
uint8_t idleTimer;
uint16_t powerDelayCounter;
uint8_t hwTimer, hwIndex;
uint8_t selfTestTimer;
uint8_t relayOffTimer, wfOnOffTimer;
code const uint8_t hwTempTable[D_hwTableSize] = { 100, 45, 60, 70, 80, 90, 95 };

#else
extern bit b4ms;
extern bit bPowerOn;
extern bit bSsRelayOn;
extern bit bXdRelayOn;
extern bit bMotorOn;
extern bit bHcsOn;
extern bit bAssOn;

extern bit bHwOn;
extern bit b500ms;
extern bit b40ms;
extern bit bAuto;
extern bit bHigh;
extern bit bLedFlash;

extern uint8_t tick, timer40ms, timer500ms, timer1s, timer1m, timer1h;
extern uint8_t csTimer, xdTimer, wfTimer, hssTimer;
extern uint8_t tempChangeTimer;
extern uint8_t tempAdjustTimer;
extern uint8_t settedTemp, highTemp;
extern uint8_t keyValue;
extern uint8_t highTemp;
extern uint8_t boilCounter;
extern uint8_t hwTimer;


#endif
//Macro Actions

//Functions------------------------
void GetKey(void);
void DisplayDispatcher(void);
void PowerOff(void);
void InitVar();
void SsOff();



#endif
