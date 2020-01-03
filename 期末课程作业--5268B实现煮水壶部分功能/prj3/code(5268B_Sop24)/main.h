#ifndef __main_h
#define __main_h
// Hal: exp: #define P_led P10 -----------------

// Const: exp: #define D_data 1 ----------------
// base 1ms
#define D_5ms 5
#define D_1000ms 1000
// Globle Var -----------------------------------------
#ifdef __main_c
bit bLedFlash ;
uint16_t index = 0;
uint16_t time1 = 10;
uint8_t i;
 uint8_t gewei = 0;
 uint8_t ten = 0;
#else
extern bit bLedFlash;
#endif
static uint16_t ledflg = 0;

// Action Macro: exp: #define F_getData() ------

// Function ------------------------------------
void TimeProcess();
void TaskSetting();
void TaskProcess();
void DisplayProcess();
#endif