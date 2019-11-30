#define __keys_c
#include "includeAll.h"
//=============================================================================
void GetKeys() {
  static uint8_t tempKeyValue = D_keyNull;

  DelayMs(5);
  if (P_key1 == 0) {
    tempKeyValue = D_keyValue1;
  } else {
    keyValue = tempKeyValue;
    tempKeyValue = D_keyNull;
  }
}