#define __buzz_c

#include "includeAll.h"

void BuzzCount(uint8_t count)
{	
    buzzCounter = count ; 
}

void Buzz(){
    buzzLastTimer = D_buzzLastTime ;
}

