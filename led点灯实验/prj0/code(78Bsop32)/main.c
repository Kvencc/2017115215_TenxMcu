#define __main_c
#include "includeAll.h"
//=============================================================================
void main() {
  SysInit();
  VarsInit();
  while (1) {
    F_turnOnWDT();
    // user coding
    F_ledOff();
    delayMs(500);
    F_ledOn();
    delayMs(500);
  }
}
//=============================================================================
void delayMs(uint16_t msCount) {
  uint16_t i, j;
  for (i = 0; i < msCount; i++) {
    for (j = 0; j < 1000; j++) {
      /* code */
    }
  }
}
