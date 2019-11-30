
#ifndef	__SETTING_H__
#define	__SETTING_H__
#ifdef TKJUDGEMENT_C

const unsigned char code TkChannelTable[] =
{
7,
6,
1,
0,
255,
255,
255,
255,
255,
255,
255,
255,
255,
255,
255,
255,
};
const unsigned char code TkChannelOutTable[] =
{
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,
0xFF,

};
const unsigned char code TkThresholdTable[] =
{
	40,
	40,
	40,
    40,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
	30,
};
const unsigned char code TkThresholdTable_MIN[] =
{
	32,
	32,
    32,
    32,
	26,
	26,
	25,
	25,
	25,
	25,
	25,
	25,
	25,
	25,
	25,
	25,
};
const int code TkStatusBitTable[] =
{
	0x0001,
	0x0002,
	0x0004,
	0x0008,
	0x0010,
	0x0020,
	0x0040,
	0x0080,
	0x0100,
	0x0200,
	0x0400,
	0x0800,
	0x1000,
	0x2000,
	0x4000,
	0x8000,
};
const unsigned char code IOSetting[] = // **********************
{
	0xff,	//Register P0OE setting
	0x00,	//Register P1MODL setting
	0xae,	//Register P1MODH setting
	0x0a,	//Register P2MOD setting
	0xf0,	//Register P3MODL setting
	0x2a,	//Register P3MODH setting
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
};
const unsigned char code TKOutputSetting[] =
{
	0x00,	//output IO mode,0:Normal 1:Toggle
	0x00,	//IO default status,0:High 1:Low
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
};
const unsigned char code PowerOnIOStatus[] =
{
 0xFF, //P0
 0xFF, //P1
 0xFF, //P2
 0xFF, //P3
 0xFF, //P4
 0xFF, //P5
 0xFF, //P6
 0xFF, //P7
};
const unsigned char code TkDebounceTimerTable[] =
{
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
	10,
};
#else
    extern const unsigned char code TkThresholdTable_MIN[];
    extern const unsigned char code TkThresholdTable[];
    extern const int code TkStatusBitTable[];
    extern const unsigned char code IOSetting[];
    extern const unsigned char code TkChannelTable[];
    extern const unsigned char code TkChannelOutTable[];
    extern const unsigned char code TKOutputSetting[];
    extern const unsigned char code TkDebounceTimerTable[];
    extern const unsigned char code PowerOnIOStatus[];
#endif

#endif
