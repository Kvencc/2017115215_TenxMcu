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
    TR0 = 1;
    index++;
      if(index == 100)
      {
        index = 0;
      }
    
  }
  keyValue1 = D_keyNull;


  if (D_keyValue1 == keyValue2) {
    ledflg = ~ledflg;
    TR0 = 1;
    index++;
      if(index == 100)
      {
        index = 0;
      }
  }
  keyValue2 = D_keyNull;
   

  if (D_keyValue1 == keyValue3) {
    ledflg = ~ledflg;
    TR0 = 1;
    index++;
      if(index == 100)
      {
        index = 0;
      }
  }
  keyValue3 = D_keyNull;
  

  if (D_keyValue1 == keyValue4) {
    ledflg = ~ledflg;
    TR0 = 1;
    index--;
      if(index < 0)
      {
        index = 1;
      }
          
  }
 keyValue4 = D_keyNull;
}

//if (D_keyValue1 == keyValue4) {
  // F_buzzOn;     //推挽输出状态控制蜂鸣器
  //}else {
   //F_buzzOff;
  //}

//=============================================================================
void DisplayProcess() {

 
  if (ledflg) {
    
    F_led1Off();
    F_led2On();
    gewei = index % 10;
    ten = (index-gewei)/10;
    smg_control(gewei,2);
    smg_control(ten,1);


  }  
  else {
     F_led1On();
    F_led2Off();
    gewei = index%10;
    ten = (index-gewei)/10;
    smg_control(gewei,2);
    smg_control(ten,1);
  }
    

}
