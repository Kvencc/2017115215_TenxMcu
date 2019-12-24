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
  P3MODH = 0x24;
  P3MODL = 0x84;
  P1MODH = 0x2a;
  P1MODL = 0xa2;
  
  // IO 状态初始化
  P3_4 = 1;
  P3_2 = 1;
  P1_7 = 1;
  P1_2 = 1;

  P1_5 = 1;
  F_ledOn();
  F_led2Off();
  
  // T2 初始化  7.3728Mhz/2 = 3686400Hz
  //  3686400Hz/3686.4 = 1000Hz = 1ms timer2 interrupt
  TH2 = (65536 - 3686) / 256;
  RCP2H = TH2;
  TL2 = (65536 - 3686) % 256;
  RCP2L = TL2;
  TR2 = 1;
  ET2 = 1;
  EA = 1;
}
//=============================================================================
void VarsInit() {}