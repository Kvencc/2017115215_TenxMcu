//=============================================================================
//Name		:tkjudgement.c
//Purpose	:touchkey judgement
//=============================================================================
#define     TKJUDGEMENT_C

#include    "includeAll.h"


//=============================================================================
// Function:	void TkJudgement(void)
// Purpose:	judge touch key status
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
void TkJudgement(unsigned char uctkcount)
{
	unsigned char tktemp, thtemp_min, thtemp;
	unsigned char* ptemp, *otemp;

	otemp = (unsigned char*)&TkOutputArray[0];
	for (tktemp = 0; tktemp < uctkcount; tktemp++) {
		ptemp = (unsigned char*)&TkOutputArray[tktemp];
		if (TkOutputArray[tktemp] < 0) {
			*(otemp + tktemp) = 0x00;
		}else {
			if (TkOutputArray[tktemp] > 0xff) {
				*(otemp + tktemp) = 0xff;
			}else {
				*(otemp + tktemp) = *(ptemp + 1);
			}
		}
		thtemp = TkThresholdTable[tktemp];
		thtemp_min = TkThresholdTable_MIN[tktemp];
		if (TkStatus & TkStatusBitTable[tktemp]) {
			if (thtemp_min > *(otemp + tktemp))
				TkStatus &= ~(TkStatusBitTable[tktemp]);
		}else {
			if (thtemp <= *(otemp + tktemp))
				TkStatus |= TkStatusBitTable[tktemp];
		}
	}
}
//=============================================================================
// Function:	void InitialIoport(void)
// Purpose:	initial io port
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
//MODE0:00 Pseudo Open Drain(P3.0~P3.2) or Open Drain(others pin) with internal pull up
//MODE1:01 Pseudo Open Drain(P3.0~P3.2) or Open Drain(others pin) without internal pull up
//MODE2:10 CMOS output
//MODE3:11 Analog input for ADC or Touch Key,digital input buffer is disabled
void InitialIoport(void)
{
	P0OE = IOSetting[0];
	P1MODL = IOSetting[1];
	P1MODH = IOSetting[2];
	P2MOD = IOSetting[3];
	P3MODL = IOSetting[4];
	P3MODH = IOSetting[5];
	//relay off
	P_zero = 1;
	F_csOff();
	F_ssOff();

	#ifdef TKOUTPUT
	P0 = P0Temp = PowerOnIOStatus[0];
	P1 = P1Temp = PowerOnIOStatus[1];
	P2 = P2Temp = PowerOnIOStatus[2];
	P3 = P3Temp = PowerOnIOStatus[3];
	#endif
}
//=============================================================================
// Function:	void ChangeToFastClk(void)
// Purpose:	change system clock form slow to fast,do not change system clock from slow to slow or fast to fast
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
void ChangeToFastClk(void)
{
	CLKCON = 0x02;  //Clock div 2
	STPPCK = 0;
	STPFCK = 0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SELFCK = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
//=============================================================================
// Function:	void ChangeToSlowClk(void)
// Purpose:	change system clock form fast to slow,do not change system clock from slow to slow or fast to fast
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
//void ChangeToSlowClk(void)
//{
//	CLKCON = 0x01;	//Clock div 4
//	SELFCK = 0;	//change to slow clock
//	STPFCK = 1;	//stop fast clock
//	STPPCK = 1;	//stop uart/t0/t1/t2/adc in idle mode
//}
//=============================================================================
// Function:	int TkConversion(unsigned char TkCh)
// Purpose:	touch key convert
// Input:	touch key channel
// OutPut:	none
// Author:
//=============================================================================
int TkConversion(unsigned char TkCh)
{
	int tkdata = 0;
	if (TkCh == 0xff) return 0; //TK channel error
	TKCON = TKTMR;      //TKTMR
	CHSEL = 0xf0 + TkCh;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TKSOC = 1;                  //start touch key conversion
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while ((ADTKDT & 0x08) == 0) ; //wait touch key end of conversion
	TKSOC = 0;
	tkdata = (ADTKDT & 0x03);
	tkdata <<= 8;
	tkdata |= TKDL;
	if (ADTKDT & 0x04) {         //bit2:overflow,bit0~1:TKDH
		tkdata = 0x3ff;         //overflow
	}
	return tkdata;
}
//=============================================================================
// Function:	unsigned char TkChannelSelection(unsigned char TkIndex)
// Purpose:	touch key channel setting
// Input:	touch key channel index
// OutPut:	touch key channel
// Author:
//=============================================================================
unsigned char TkChannelSelection(unsigned char TkIndex)
{
	switch (TkIndex) {
		case 0:     //channel 0,P1.0
			P1MODL |= 0x03;
			return 0x00;
		case 1:     //channel 1,P1.1
			P1MODL |= 0x0c;
			return 0x01;
		case 2:     //channel 2,P1.2
			P1MODL |= 0x30;
			return 0x02;
		case 3:     //channel 3,P1.3
			P1MODL |= 0xc0;
			return 0x03;
		case 4:     //channel 4,P3.3
			P3MODL |= 0xc0;
			return 0x04;
		case 5:     //channel 5,P3.2
			P3MODL |= 0x30;
			P1MODH |= 0x0c;
			return 0x05;
		case 6:     //channel 6,P3.1
			P3MODL |= 0x0c;
			return 0x06;
		case 7:     //channel 7,P3.0
			P3MODL |= 0x03;
			return 0x07;
		case 8:     //channel 8,P1.4
			P1MODH |= 0x03;
			return 0x08;
		case 9:     //channel 9,P1.6
			P1MODH |= 0x30;
			return 0x09;
		case 10:    //channel 10,P1.7
			P1MODH |= 0xc0;
			return 0x0a;
		case 11:    //channel 11,P3.6
			P3MODH |= 0x30;
			return 0x0b;
		case 12:    //channel 12,P3.5
			P3MODH |= 0x0c;
			return 0x0c;
		case 13:    //channel 13,P3.4
			P3MODH |= 0x03;
			return 0x0d;
		default:    //get touch key channel error
			return 0xff;
	}
}
//=============================================================================
// Function:	void TkChannelReset(unsigned char TkIndex)
// Purpose:	touch key channel setting
// Input:	touch key channel index
// OutPut:	touch key channel
// Author:
//=============================================================================
void TkChannelReset(unsigned char TkIndex)
{
	switch (TkIndex) {
		case 0:     //channel 0,P1.0
			P1MODL &= 0xfc;
			return;
		case 1:     //channel 1,P1.1
			P1MODL &= 0xf3;
			return;
		case 2:     //channel 2,P1.2
			P1MODL &= 0xcf;
			return;
		case 3:     //channel 3,P1.3
			P1MODL &= 0x3f;
			return;
		case 4:     //channel 4,P3.3
			P3MODL &= 0x3f;
			return;
		case 5:     //channel 5,P3.2
			P3MODL &= 0xcf;
			return;
		case 6:     //channel 6,P3.1
			P3MODL &= 0xf3;
			return;
		case 7:     //channel 7,P3.0
			P3MODL &= 0xfc;
			return;
		case 8:     //channel 8,P1.4
			P1MODH &= 0xfc;
			return;
		case 9:     //channel 9,P1.6
			P1MODH &= 0xcf;
			return;
		case 10:    //channel 10,P1.7
			P1MODH &= 0x3f;
			return;
		case 11:    //channel 11,P3.6
			P3MODH &= 0xcf;
			return;
		case 12:    //channel 12,P3.5
			P3MODH &= 0xf3;
			return;
		case 13:    //channel 13,P3.4
			P3MODH &= 0xfc;
			return;
		default:    //get touch key channel error
			return;
	}
}
//=============================================================================
// Function:	void GetBaseline(unsigned char uctkcount)
// Purpose:	get touch key baseline
// Input:	touch key channel count
// OutPut:	none
// Author:
//=============================================================================
#ifdef PlugInGetBaseline
void GetBaseline(unsigned char uctkcount)
{
	unsigned char tktemp;
	for (tktemp = 0; tktemp < uctkcount; tktemp++) {
		gBTkCh = TkChannelSelection(TkChannelTable[tktemp]);
		TkBaselineArray[tktemp] = TkConversion(gBTkCh);
		TkChannelReset(gBTkCh);
	}
	if (UseReferenceTK) TkBaselineArray[uctkcount] = TkConversion(15);  //TK reference channel
}
#endif
//=============================================================================
// Function:	void CheckNoise(void)
// Purpose:	check noise
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
void CheckNoise(unsigned char uctkcount)
{
	int TkNoiseTemp;
	TkNoiseTemp = abs(TkBaselineArray[uctkcount] - TkRawDataArray[uctkcount]);
	if (TkNoiseTemp < 2) {
		AntiNoiseTimer = 0;     //�ο��Ų���Ϊ����1ʱ���ż�ʱ��0
	}else {
		if ((AntiNoiseTimer < gbAntiNoiseTimer) && (TkNoiseTemp > 5)) {  //������140ms�ڲο��Ų�����������5���ж�Ϊ����
			AntiNoiseTimer = 0;
			RawDataInvalidFlag = 1;
			AntiNoiseDebounceTimer = 0;
		}
	}
	TkNoise = TkNoiseTemp;
	if (TkNoiseTemp > 255) TkNoise = 255;
}
//=============================================================================
// Function:	void TkStatusOutput(void)
// Purpose:	output tkstatus to io
// Input:	none
// OutPut:	none
// Author:
//=============================================================================
#ifdef TKOUTPUT
void TkStatusOutput(unsigned char uctkcount)
{
	unsigned char i;
	int ucStatusTemp;
	for (i = 0; i < uctkcount; i++) {
		ucStatusTemp = TkStatus & TkStatusBitTable[i];
		if (ucStatusTemp) {
			ucStatusTemp = 1;
			if (TkDebounceTimer[i] < TkDebounceTimerTable[i]) TkDebounceTimer[i]++;
		}else {
			TkDebounceTimer[i] = 0;
		}
		if (TkDebounceTimer[i] < TkDebounceTimerTable[i]) ucStatusTemp = 0;
		if (TKOutputSetting[0] == 0) {
			if (ucStatusTemp ^ TKOutputSetting[1]) {
				switch (TkChannelOutTable[i] & 0xf0) {
					case 0x00:
						P0Temp &= ~(1 << (TkChannelOutTable[i] & 0x0f));
						P0 = P0Temp;
						break;
					case 0x10:
						P1Temp &= ~(1 << (TkChannelOutTable[i] & 0x0f));
						P1 = P1Temp;
						break;
					case 0x20:
						P2Temp &= ~(1 << (TkChannelOutTable[i] & 0x0f));
						P2 = P2Temp;
						break;
					case 0x30:
						P3Temp &= ~(1 << (TkChannelOutTable[i] & 0x0f));
						P3 = P3Temp;
						break;
					default:
						break;
				}
			}else {
				switch (TkChannelOutTable[i] & 0xf0) {
					case 0x00:
						P0Temp |= (1 << (TkChannelOutTable[i] & 0x0f));
						P0 = P0Temp;
						break;
					case 0x10:
						P1Temp |= (1 << (TkChannelOutTable[i] & 0x0f));
						P1 = P1Temp;
						break;
					case 0x20:
						P2Temp |= (1 << (TkChannelOutTable[i] & 0x0f));
						P2 = P2Temp;
						break;
					case 0x30:
						P3Temp |= (1 << (TkChannelOutTable[i] & 0x0f));
						P3 = P3Temp;
						break;
					default:
						break;
				}
			}
		}else {
			if ((ucStatusTemp) && ((TkPressedFlag & (1 << i)) == 0)) {
				switch (TkChannelOutTable[i] & 0xf0) {
					case 0x00:
						P0Temp ^= (1 << (TkChannelOutTable[i] & 0x0f));
						P0 = P0Temp;
						break;
					case 0x10:
						P1Temp ^= (1 << (TkChannelOutTable[i] & 0x0f));
						P1 = P1Temp;
						break;
					case 0x20:
						P2Temp ^= (1 << (TkChannelOutTable[i] & 0x0f));
						P2 = P2Temp;
						break;
					case 0x30:
						P3Temp ^= (1 << (TkChannelOutTable[i] & 0x0f));
						P3 = P3Temp;
						break;
					default:
						break;
				}
				TkPressedFlag |= (1 << i);
			}else {
				if (ucStatusTemp == 0) TkPressedFlag &= ~(1 << i);
			}
		}
	}
}
#endif
//=============================================================================
// Function:   Initialize registers
// -- set flag
// -- clear RAM
// -- get baseline
//=============================================================================
void InitialRegister(void)
{
	unsigned char i, j;

	gBTimer0RollOver = 0;
	TkArrayIndex = 0;
	TkStatus = 0;
	RawDataInvalidFlag = 0;
//	UseReferenceTK = 1;		//д1ʹ���ڲ��ο��ż���������д0���òο��ţ�����������
	UseReferenceTK = 0;
	for (i = 0; i < TKCOUNT; i++) {
		for (j = 0; j < 5; j++)
			TkCalcArray[i][j] = 0;
		TkBaselineArray[i] = 0;
	}
	if (UseReferenceTK) TkBaselineArray[TKCOUNT] = 0;

	#ifndef POWERSAVE
	TMOD = 0x11;        //16bit timer0&timer1
	TH0 = (65536 - 5772) / 256; //4ms timer0 interrupt
	TL0 = (65536 - 5772) % 256;
	TH1 = (65536 - 28860) / 256;        //20ms timer1 interrupt
	TL1 = (65536 - 28860) % 256;

	TH2 = (65536 - 250) / 256;   //0.125ms timer2 interrupt
	RCP2H = TH2;
	TL2 = (65536 - 250) % 256;
	RCP2L = TL2;

	ET0 = 1;            //timer0 interrupt enabl
	TR0 = 1;            //timer0 running
	ET1 = 1;
	TR1 = 1;

	ET2 = 1;            //timer2 interrupt enable
	TR2 = 1;            //timer2 running

	gbAntiNoiseTimer = 35;  //35*T0 interrupt timer 4ms = 140ms�������޸���T0��ʱʱ����Ҫ�޸Ĵ�ֵ
	i = 15;
	#else
	OPTION = 0x43;      //mode3v,the chip can be only operated in VCC<3.6V condition and LDO is turned off to save current,timer3 Interrupt rate is 128 Slow clock cycle
	CLRTM3 = 1;
	gbAntiNoiseTimer = 7;   //7*T0 interrupt timer 20ms = 140ms�������޸���T2��ʱʱ����Ҫ�޸Ĵ�ֵ
	i = 1;
	#endif

	P1MODH |= 0x0c;         //CLD
	#ifdef PlugInGetBaseline
	GetBaseline(TKCOUNT);               //get baseline
	while (gBTimer0RollOver < i) CLRWDT = 1;
	GetBaseline(TKCOUNT);               //get baseline
	gBTimer0RollOver = 0;
	AllTkBaselineSetFlag = 1;
	#else
	TkBaselineSetNum = 0;
	AllTkBaselineSetFlag = 0;
	TkBaselineSetFlag = 0;
	#endif
}

//=============================================================================
// Function:   Touchkey Sacn
// -- get all touch channel raw data
// -- Calculate
// -- Get results
// -- Outputs the results on the IO pin
// -- Outputs the results on the IIC
// -- Update base line
//=============================================================================
void TKScan(void)
{
	unsigned char tktemp;

	for (tktemp = 0; tktemp < TKCOUNT; tktemp++) {
		gBTkCh = TkChannelSelection(TkChannelTable[tktemp]);
		TkRawDataArray[tktemp] = TkConversion(gBTkCh);
		TkChannelReset(gBTkCh);
	}
	if (UseReferenceTK) TkRawDataArray[TKCOUNT] = TkConversion(15); //TK reference channel
	if (AllTkBaselineSetFlag) {
		if (UseReferenceTK) CheckNoise(TKCOUNT);
		TkCalculate(TKCOUNT);
		TkJudgement(TKCOUNT);
		#ifdef TKOUTPUT
		TkStatusOutput(TKCOUNT);
		#endif
	}

	#ifdef IIC_COMM
	IIC_RW();
	#endif

	if (AllTkBaselineSetFlag)
		UpdateBaseline(TKCOUNT, UpdateUpperLimit, UpdateLowerLimit, UpdateBaselineTimer); //���������͸���ʱ����global.h�ж���
	else
		UpdateBaseline(TKCOUNT, UpdateUpperLimit, UpdateUpperLimit, GetBaselineTimer); //���������͸���ʱ����global.h�ж���
}
//=============================================================================
// Function:   idle mode, sleep 20ms
//=============================================================================
#ifdef POWERSAVE
void PRO_SLEEP20MS(void)
{
	TKCON = 0x80;       //TOUCH KEY POWER DOWN
	CLKCON = 0x01;      //Clock div 4,24KHz/4
	SELFCK = 0;     //change to slow clock
	STPFCK = 1;     //stop fast clock
	STPPCK = 1;     //stop uart/t0/t1/t2/adc in idle mode
	INTE1 = 0x01;       //enable timer3 interrupt
	PCON |= IDL;        //enter idle mode
	INTE1 = 0x00;       //disable timer3 interrupt
	CLRTM3 = 1;
	STPFCK = 0;     //enable fast clock
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	CLKCON = 0x02;      //Clock div 2,7.3728MHz/2
	SELFCK = 1;     //change to fast clock
}

#endif
