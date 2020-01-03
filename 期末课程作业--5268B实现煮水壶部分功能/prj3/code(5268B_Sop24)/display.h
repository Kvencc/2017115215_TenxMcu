#ifndef __display_h
#define __display_h
// Hal: exp: #define P_led P10 -----------------
#define P_led P1_0
#define P_led2 P1_2
#define P_led1 P1_4

#define P_smgcon1 P1_1
#define P_smgcon2 P1_6
#define P_smga P1_4
#define P_smgb P3_4
#define P_smgc P3_5
#define P_smgd P1_7
#define P_smge P3_6
#define P_smgf P1_2
#define P_smgg P3_2
#define P_smgdg P1_3
// Const: exp: #define D_data 1 ----------------
#define D_ledOn 1  //高电位亮
#define D_ledOff 0 //低点位灭
// Globle Var -----------------------------------------
#ifdef __display_c
uint16_t tempKeyValue5 = 0;
uint16_t tempKeyValue4 = 0 ;
// 显示段码值01234567
#else

#endif

// Action Macro: exp: #define F_getData() ------
#define F_led1On() P_led1 = D_ledOn
#define F_led1Off() P_led1 = D_ledOff
#define F_ledOn() P_led = D_ledOff
#define F_ledOff() P_led = D_ledOn
#define F_led2On() P_led2 = D_ledOn
#define F_led2Off() P_led2 = D_ledOff
#define F_ledNeg() P_led = ~P_led

// Function ------------------------------------
void smg_control(int num,int smg);
#endif