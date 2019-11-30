
#ifndef __display_h
#define __display_h

//HAL------------------------------
//Ref 1628


//Const---------------------------

#define D_setHcsLed   0x01
#define D_clrHcsLed   0xfe

#define D_setCsTimeLed  0x02
#define D_clrCsTimeLed  0xfd

#define D_setAssLed   0x04
#define D_clrAssLed   0xfb

#define D_setPowerLed   0x20
#define D_clrPowerLed   0xdf
//sz
#define D_setTempFont   0x01
#define D_clrTempFont   0xfe

#define D_setPowerFont  0x10
#define D_clrPowerFont  0xef

#define D_setAssFont    0x08
#define D_clrAssFont    0xf7

#define D_setCsFont     0x04
#define D_clrCsFont     0xfb

#define D_setXdFont     0x02
#define D_clrXdFont     0xfd



#define D_FontBar   0x40
#define D_FontBlank 0x00
#define D_FontO     0x3F
#define D_FontN     0x37
#define D_Font0     0x3F
#define D_Font1     0x06
#define D_Font2     0x5B
#define D_FontE     0x79
#define D_Font8     0x7F

#define D_DisplayBufferSize 6
//Var------------------------------
	#ifdef __dispaly_c
//displayBuffer[0-1]: Led indicators
//displayBuffer[2-5]: SZ1-SZ4
uint8_t displayBuffer[D_DisplayBufferSize];
//A    B      C     D     E     F     G     DG
//seg8 seg7  seg6 seg5  seg4  seg2  seg1  seg3
code const uint16_t segMapTable[8] = { D_seg8, D_seg7, D_seg6, D_seg5, \
									   D_seg4, D_seg2, D_seg1, D_seg3 };
//com0--com5: grid* table
//grid6  grid1 grid3 grid4 grid5 grid2
code const uint8_t comMapTable[D_DisplayBufferSize] = { D_grid6, D_grid1, D_grid3, D_grid4, D_grid5, D_grid2 };
	#else
extern uint8_t displayBuffer[D_DisplayBufferSize];
extern code const uint16_t segMapTable[];
extern code const uint8_t comMapTable[];
	#endif
//Function----------------------------
void DisplayScan(void); //
void DisplayNumber(uint8_t number);
void DisplayXdNumber();
//
#define F_displayWaterLow()  displayBuffer[5] = D_FontBlank;  displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontE;  displayBuffer[2] = D_Font1
#define F_displayAdShort()   displayBuffer[5] = D_FontBlank;  displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontE;  displayBuffer[2] = D_Font2
#define F_displayAdOff()     displayBuffer[5] = D_FontBlank;  displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontE;  displayBuffer[2] = D_Font0
#define F_displayTempLogo()    displayBuffer[5] |= D_setTempFont
#define F_displayPowerOff()   displayBuffer[5] |= D_setPowerFont; displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontBlank; displayBuffer[2] = D_FontBlank; \
	displayBuffer[1] = D_FontBlank; displayBuffer[0] = D_FontBlank
#define F_displayPowerOn()  displayBuffer[5] = D_FontBlank; displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontO; displayBuffer[2] = D_FontN;
#define F_displayAll()    displayBuffer[5] = D_Font8; displayBuffer[4] = D_Font8; \
	displayBuffer[3] = D_Font8; displayBuffer[2] = D_Font8; \
	displayBuffer[1] = D_Font8; displayBuffer[0] = D_Font8
#define F_displayClrAll()    displayBuffer[5] = D_FontBlank; displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontBlank; displayBuffer[2] = D_FontBlank;  \
	displayBuffer[1] = D_FontBlank; displayBuffer[0] = D_FontBlank;
#define F_displayClrSz()   displayBuffer[4] = D_FontBlank; \
	displayBuffer[3] = D_FontBlank; displayBuffer[2] = D_FontBlank;

#define F_powerLedOn()      displayBuffer[1] |= D_setPowerLed
#define F_powerLedOff()     displayBuffer[1] &= D_clrPowerLed
#define F_assLedOn()        displayBuffer[1] |= D_setAssLed
#define F_assLedOff()       displayBuffer[1] &= D_clrAssLed
#define F_hcsLedOn()        displayBuffer[1] |= D_setHcsLed
#define F_hcsLedOff()       displayBuffer[1] &= D_clrHcsLed
#define F_csTimeLedOn()     displayBuffer[1] |= D_setCsTimeLed
#define F_csTimeLedOff()    displayBuffer[1] &= D_clrCsTimeLed

#define F_powerIconOn()     displayBuffer[5] |= D_setPowerFont
#define F_powerIconOff()    displayBuffer[5] &= D_clrPowerFont
#define F_csIconOn()        displayBuffer[5] |= D_setCsFont
#define F_csIconOff()       displayBuffer[5] &= D_clrCsFont
#define F_assIconOn()       displayBuffer[5] |= D_setAssFont
#define F_assIconOff()      displayBuffer[5] &= D_clrAssFont

#endif
