#define __keys_c
#include "includeAll.h"
//=============================================================================
void GetKeys() {
  static uint8_t tempKeyValue1 = D_keyNull;
  static uint8_t tempKeyValue2 = D_keyNull;
  static uint8_t tempKeyValue3 = D_keyNull;
  static uint8_t tempKeyValue4 = D_keyNull;

  //按键口 P17 设为上拉输入
  
  

  

  // P1MODL = 0x02;
  // P1_2 = 1;
  if ( P_key2== 0 ) {
    tempKeyValue2 = D_keyValue1;
  } else {
    keyValue2 = tempKeyValue2;
    tempKeyValue2 = D_keyNull;
  }
  if ( P_key3 == 0 ) {
    tempKeyValue3 = D_keyValue1;
  } else {
    keyValue3 = tempKeyValue3;
    tempKeyValue3 = D_keyNull;
  }
  if ( P_key1 == 0 ) {
    tempKeyValue1 = D_keyValue1;
  } else {
    keyValue1 = tempKeyValue1;
    tempKeyValue1 = D_keyNull;
  }
  // if ( P_key4 == 0 ) {
    
  //   tempKeyValue4 = D_keyValue1;
  // } else {
    
  //   keyValue4 = tempKeyValue4;
  //   tempKeyValue4 = D_keyNull;
  // }

  
  // P1MODL = 0xaa;

  //按键口P10，恢复为输出
  
}