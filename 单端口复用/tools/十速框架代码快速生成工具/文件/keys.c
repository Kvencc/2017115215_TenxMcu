#define __keys_c
#include	"includeAll.h"

//-----------------------
void GetKeys(void){
	static uint8_t lastKeyValue = 0; 
	//scan key
		F_segsOff();
    F_comsOff();
#keyC1

    _nop_();
    _nop_();
    _nop_();
    _nop_();

#keyC2
#keyC3
    //
}