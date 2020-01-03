#define __init_c
#include "includeAll.h"
//=============================================================================
void SysInit() {
  F_clearWDT();
  //时钟初始化
  CLKCON = 0x03; // Clock div 1  7.3728Mhz


  STPPCK = 0;
  STPFCK = 0;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SELFCK = 1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  // IO 模式初始化
  //按键3_4 p3modh 1~0
  //3_2 p3modl 5-4
  //1_7 p1modh 7~6
  //1_2 p1modl 5~4
  //按键初始化

   
	

  // PINMOD = 0x00;
  //按键初始化

  P3MODH = 0x2a;
  P1MODL = 0xaa;
  P1MODH = 0xaa;
  P3MODL = 0xa4;

  //led灯初始化 p1_0 p1modl 1~0    p1_2 p1modl 5~4  p1_4 p1modh 1~0
//蜂鸣器 p1_5 p1modh 2~3
// P_smgcon1 P1_1  p1modl 3~2
// P_smgcon2 P1_6  p1modh 5~4

// P_smga P1_4     p1modh 1~0
// P_smgb P3_4     p3modh 1~0
// P_smgc P3_5     p3modh 3_2
// P_smgd P1_7     p1modh 7~6
// P_smge P3_6     p3modh 5~4
// P_smgf P1_2     p1modl 5~4
// P_smgg P3_2     p3modl 5~4
// P_smgdg P1_3    p1modl 7~6
  
  // IO 状态初始化
  P3_4 = 1;
  P3_2 = 1;
  P1_7 = 1;
  //P1_2 = 1;

  
  F_ledOn();
  F_led2Off();
  F_led1On();
   
  
  // T2 初始化  7.3728Mhz/2 = 3686400Hz
  //  3686400Hz/3686.4 = 1000Hz = 1ms timer2 interrupt
  //922
  TH2 = (65536 - 3686) / 256;
  RCP2H = TH2;
  TL2 = (65536 - 3686) % 256;
  RCP2L = TL2;
  TR2 = 1;
  ET2 = 1;

  TH0 = (65536 - 3686) / 256;

  TL0 = (65536 - 3686) % 256;

  TR0 = 0;
  ET0 = 1;
  EA = 1;
}
//=============================================================================
void VarsInit() {}