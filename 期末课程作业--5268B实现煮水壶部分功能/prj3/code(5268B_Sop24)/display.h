#ifndef __display_h
#define __display_h
// Hal: exp: #define P_led P10 -----------------
#define P_led P1_0
#define P_led1 P1_2
#define P_led2 P1_4
#define P_smg P1_4
// Const: exp: #define D_data 1 ----------------
#define D_ledOn 1  //高电位亮
#define D_ledOff 0 //低点位灭
// Globle Var -----------------------------------------
#ifdef __display_c
unsigned char code dofly_DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
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
#define F_smg()
// Function ------------------------------------

#endif