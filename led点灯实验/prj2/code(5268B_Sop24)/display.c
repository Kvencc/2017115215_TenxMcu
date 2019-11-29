
#define __dispaly_c

#include    "includeAll.h"

//�����루��ת��
//code const uint8_t displayFonts[10] = {0x3F,0x30,0x5B,0x79,0x74,0x6D,0x6F,0x38,0x7F,0x7D};
//
//��������
code const uint8_t displayFonts[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//------------------
void DisplayScan(void)
{
	uint8_t dspIndex, i;
	uint8_t byte, mask;
	uint16_t dspWord;

	for (dspIndex = 0; dspIndex < D_DisplayBufferSize; dspIndex++) {
		byte = displayBuffer[dspIndex];
		dspWord = 0;
		mask = 0x01;
		for (i = 0; i < 8; i++) {
			if (byte & mask) {
				dspWord |= segMapTable[i];
			}
			mask <<= 1;
		}
		tm1628Buffer[comMapTable[dspIndex]] = dspWord;
	}
	//
	Dislay1628();
}
//------------------
void DisplayNumber(uint8_t number)
{
	uint8_t i;

	i = number / 100;
	if (i == 0) {
		displayBuffer[4] = D_FontBlank;
	}else {
		displayBuffer[4] = displayFonts[i];
	}
	number = number % 100;
	i = number / 10;
	displayBuffer[3] = displayFonts[i];
	number = number % 10;
	displayBuffer[2] = displayFonts[number];

	return;
}
//=============================================================================
void DisplayXdNumber()
{
	displayBuffer[4] = displayFonts[8];
	displayBuffer[3] = displayFonts[0];
	displayBuffer[2] = displayFonts[0];
}
