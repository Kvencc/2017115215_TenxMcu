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
  for (uint16_t i = 0; i < msCount; i++) {
    for (uint16_t j = 0; j < 1000; j++) {
      /* code */
    }
  }
}
