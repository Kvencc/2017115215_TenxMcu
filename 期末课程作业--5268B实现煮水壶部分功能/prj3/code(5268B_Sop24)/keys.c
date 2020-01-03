#define __keys_c
#include "includeAll.h"
//=============================================================================
void GetKeys() {
  static uint8_t tempKeyValue1 = D_keyNull;
  static uint8_t tempKeyValue2 = D_keyNull;
  static uint8_t tempKeyValue3 = D_keyNull;
  static uint8_t tempKeyValue4 = D_keyNull;


    temp1 = P1_2;
    temp2 = P1_7;
    temp3 = P3_2;
    temp4 = P3_4;

    P1MODH = 0x2a;
    P3MODH = 0x28;
    P1MODL = 0x8a;
    P3MODL = 0x84;

    P1_2 = 1;
    P1_7 = 1;
    P3_2 = 1;
    P3_4 = 1;

    F_ledOff();
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


  if ( P_key4 == 0 ) { 
     
    tempKeyValue4 = D_keyValue1;
  } else { 
    keyValue4 = tempKeyValue4;
    tempKeyValue4 = D_keyNull;
  }
  F_ledOn();
  P3MODH = 0x2a;
  P1MODL = 0xaa;
  P1MODH = 0xaa;
  P3MODL = 0xa4;
  
    P1_2 = temp1;
    P1_7 = temp2;
    P3_2 = temp3;
    P3_4 = temp4;

}