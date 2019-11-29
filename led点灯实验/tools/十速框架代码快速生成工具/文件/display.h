
#ifndef __display_h
#define __display_h
#displayH1
//HAL------------------------------
#define F_setA() SMG_A =1
#define F_setB() SMG_B =1
#define F_setC() SMG_C =1
#define F_setD() SMG_D =1
#define F_setE() SMG_E =1
#define F_setF() SMG_F =1
#define F_setG() SMG_G =1
#define F_setP() SMG_P =1
//Com0 == Led comm
#define F_ledCom1On() LEDCOM1= 0
#define F_ledCom2On() LEDCOM2= 0
#define F_ledCom3On() LEDCOM3= 0
#define F_ledCom4On() LEDCOM4= 0
#define F_szCom1On() SMGCOM1 = 0
#define F_szCom2On() SMGCOM2 = 0
#define F_szCom3On() SMGCOM3 = 0
#define F_szCom4On() SMGCOM4 = 0
//Const---------------------------
//
#define D_setASeg   0x01
#define D_clrASeg   0xfe
#define D_setBSeg   0x02
#define D_clrBSeg   0xfd
#define D_setCSeg   0x04
#define D_clrCSeg   0xfb
#define D_setDSeg   0x08
#define D_clrDSeg   0xf7
#define D_setESeg   0x10
#define D_clrESeg   0xef
#define D_setFSeg   0x20
#define D_clrFSeg   0xdf
#define D_setGSeg   0x40
#define D_clrGSeg   0xbf
#define D_setPSeg	0x80
#define D_clrPSeg	0x7f

//led
#displayH2
#input1
//Var------------------------------

#ifdef __dispaly_c
    uint8_t displayBuffer[D_DisplayBufferSize] ;
	uint8_t displayBuffer2[D_DisplayBufferSize+1],displayStatus=0;
#else
    extern uint8_t displayBuffer[D_DisplayBufferSize] ;
	extern uint8_t displayBuffer2[D_DisplayBufferSize+1],displayStatus;
#endif
//Function----------------------------
void DisplayScan(void) ;//
void DisplayNumber(uint16_t number) ;
void DisplayTime(uint16_t time);
void DisplayTemp(uint16_t number);//onlay fangzhuang
//
#endif
