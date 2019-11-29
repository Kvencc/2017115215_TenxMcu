//#indlude <reg51.h>

#include "delay.h"


void delayms_sh(u8 ms)	
{						
	unsigned char i;
	while(ms--)
	{
		for(i = 0; i < 1840; i++);
	}
}

void delayms_lo(u16 ms)	
{						
	unsigned char i;

	while(ms--)
	{
		for(i = 0; i < 1840; i++);
	}
}
