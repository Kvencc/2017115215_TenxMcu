
#define __dispaly_c

#include    "includeAll.h"

#input4code const uint8_t displayFonts[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
#input5code const uint8_t displayFonts[10] ={0x3F,0x30,0x5B,0x79,0x74,0x6D,0x6F ,0x38,0x7F,0x7D};
//------------------
void DisplayScan(void)
{
	static uint8_t dspIndex = 0x0;
	unsigned char displayTemp,displayStatusTemp;
	dspIndex++;
	if (dspIndex >= D_DisplayBufferSize) {
		dspIndex = 0;
	}
	F_segsOff();
	F_comsOff();
	#displayC1
	displayStatusTemp=displayStatus;
	displayStatusTemp>>=dspIndex;
	if((displayStatusTemp & 0x01)==0)
	{
		displayBuffer2[dspIndex]=displayBuffer[dspIndex];
	}
	if (b500ms)
	{
		displayTemp=displayBuffer[dspIndex];
	}
	else
	{
		displayTemp=displayBuffer2[dspIndex];
	}
	if (displayTemp & 0x01) {
		//A
		F_setA();
	}
	if (displayTemp & 0x02) {
		//B
		F_setB();
	}
	if (displayTemp & 0x04) {
		//C
		F_setC();
	}
	if (displayTemp & 0x08) {
		//D
		F_setD();
	}
	if (displayTemp & 0x10) {
		//E
		F_setE();
	}
	if (displayTemp & 0x20) {
		//F
		F_setF();
	}
	if (displayTemp & 0x40) {
		//G
		F_setG();
	}
	if (displayTemp & 0x80) {
		//P
		F_setP();
	}
	switch (dspIndex) {
		#displayC2
	}//end switch

}
//------------------
void DisplayNumber(uint16_t number)
{
	uint16_t i;
	bit flag;
	flag=1;
	i = number / 1000;
	if (i == 0) {
		displayBuffer[4] = D_fontBlank;
	}else {
		flag=0;
		displayBuffer[4] = displayFonts[i];
	}
	
	number = number % 1000;
	i = number / 100;
	if (i == 0 && flag) {
		displayBuffer[3] = D_fontBlank;
	}else {
		displayBuffer[3] = displayFonts[i];
		flag=0;
	}
	
	number = number % 100;
	i=number/10;
	if (i == 0 && flag) {
		displayBuffer[2] = D_fontBlank;
	}else {
		displayBuffer[2] = displayFonts[i];
		flag=0;
	}
	number = number % 10;
	displayBuffer[1] = displayFonts[number];
	return;
}
//------------------
void DisplayTemp(uint16_t number)
{
	uint16_t i;
	bit flag;
	flag=1;
	i = number / 100;
	if (i == 0) {
		displayBuffer[4] = D_fontBlank;
	}else {
		displayBuffer[4] = displayFonts[i];
		flag=0;
	}
	
	number = number % 100;
	i = number / 10;
	if (i == 0 && flag) {
		displayBuffer[3] = D_fontBlank;
	}else {
		displayBuffer[3] = displayFonts[i];
	}
	
	number = number % 10;
	displayBuffer[2] = displayFonts[number];
	
	displayBuffer[1] = D_fontDu;//.c
	return;
}
//----------------------
void DisplayTime(uint16_t time)
{
	uint16_t k;
//time-- 88：88
	k=time / 600;
	if (k == 0) {
		displayBuffer[4] = D_fontBlank;
	}else {
		displayBuffer[4] = displayFonts[k];
	}
	time=time % 600;
	
	k = time/ 60;
	displayBuffer[3] = displayFonts[k] ;
	time = time % 60;
	
	k= time/ 10;
	displayBuffer[2] = displayFonts[k]| 0x80;
	
	k= time % 10;
	displayBuffer[1] = displayFonts[k];
}
