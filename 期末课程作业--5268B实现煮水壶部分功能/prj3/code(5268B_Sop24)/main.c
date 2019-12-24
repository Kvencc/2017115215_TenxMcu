#define __main_c
#include "includeAll.h"
//=============================================================================
void main() {
  
  SysInit();
  VarsInit();
  //使能看门狗
  F_turnOnWDT();

  while (1) {
    //喂狗
    F_clearWDT();
    //业务代码
    TimeProcess();
    TaskSetting();
    TaskProcess();
    DisplayProcess();
  }
}
//=============================================================================
void TimeProcess() {
  static uint8_t timer5ms = 0;
  static uint16_t second = 0;

  if (b1ms) {
    // 1ms 执行一次
    b1ms = 0;
    timer5ms++;
    second++;
  }
  if (timer5ms >= D_5ms) {
    // 5ms 执行一次
    timer5ms = 0;
    GetKeys();
  }
  if (second >= D_1000ms) {
    // 1s 执行一次
    second = 0;
    //CLRWDT = 1; To:清除看门狗定时器
  }
  

}
//=============================================================================
void TaskProcess() {}
//=============================================================================
void TaskSetting() {
  if (D_keyValue1 == keyValue1) {
    ledflg = ~ledflg;
  }
  keyValue1 = D_keyNull;


  if (D_keyValue1 == keyValue2) {
    ledflg = ~ledflg;
  }
  keyValue2 = D_keyNull;


  if (D_keyValue1 == keyValue3) {
    ledflg = ~ledflg;
  }
  keyValue3 = D_keyNull;
  

  if (D_keyValue1 == keyValue4) {
    ledflg = ~ledflg;
  }
  keyValue4 = D_keyNull;
}
//=============================================================================
void DisplayProcess() {
  static uint16_t secon = 0;
 
  // F_ledOn();
  if (ledflg) {
    
    F_led1Off();
    if (secon <= 10) {
    // 1s 执行一次
    
    F_buzz();
    secon++;
    }
    secon = 0;
    
  }
    
  else {
    if (secon <= 10) {
    // 1s 执行一次
    
    F_buzz();
    secon++;
    }
    F_led1On();
    secon = 0;
  }
}