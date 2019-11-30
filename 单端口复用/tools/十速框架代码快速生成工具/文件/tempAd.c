
#define __tempAd_c

#include    "includeAll.h"

//#define D_pullUp10K    1
//#define D_pullDown10K   1

//10k Pull-down VCC, 12bits Ad sample
//0c--99c
#define D_tableSize 101
//pullup 10k
/*
   code const uint16_t adTable[D_tableSize]={
   3974,3968,3962,3955,3949,3942,3935,3927,3919,3911,3901,3892,3882,
   3873,3863,3853,3842,3831,3820,3808,3795,3782,3768,3753,3738,3723,
   3707,3692,3677,3663,3650,3633,3616,3599,3580,3560,3539,3517,3495,
   3471,3448,3424,3400,3376,3353,3332,3306,3281,3255,3229,3202,3176,
   3149,3122,3094,3066,3037,3007,2977,2945,2912,2881,2849,2817,2784,
   2751,2718,2684,2650,2616,2582,2548,2514,2480,2447,2413,2381,2349,
   2317,2285,2253,2221,2189,2157,2124,2091,2058,2024,1990,1955,1919,
   1885,1853,1821,1790,1759,1728,1698,1668,1638,
   };
 */
//pulldown 10k
code const uint16_t adTable[D_tableSize] = {
 127,
 133, 139, 146, 153, 160, 168, 176, 184, 193, 201,
 210, 220, 229, 239, 250, 261, 272, 283, 295, 307,
 319, 332, 346, 359, 373, 388, 403, 418, 433, 449,
 466, 483, 500, 518, 536, 554, 573, 592, 612, 632,
 653, 674, 695, 717, 739, 761, 784, 807, 831, 855,
 879, 904, 929, 954, 980,1006,1032,1059,1085,1112,
1140,1167,1195,1223,1251,1280,1308,1337,1366,1395,
1424,1453,1483,1512,1542,1571,1601,1631,1660,1690,
1720,1749,1779,1808,1838,1867,1896,1926,1955,1984,
2013,2041,2070,2098,2126,2154,2182,2210,2237,2264,



};

// return 0: short or off
// return 1--100c
void GetTemp(void)
{
//	static uint16_t adFilterResult = 3650;
	static uint16_t adFilterResult = 672;
	uint16_t adCurResult;
	uint8_t head, middle, end;
	//ad0
	#tempAdC1
	CHSEL = D_adChannel;  //AD0
	OPTION = 0x04; //ADC Clock Rate 10: SYSCLK/16
	CLRWDT = 1;
	ADSOC = 1;
	_nop_();
	_nop_();
	while (ADSOC) {
	}
	adCurResult = ADCDH;
	adCurResult <<= 4;
	head = ADTKDT;
	head >>= 4;
	adCurResult += head;
	if (adCurResult >= D_shortValue) {
		bAdShort = 1;
		bAdOff = 0;
		bKettleValid = 0;
		padInvalidTimer1 = D_padInvalidTime1;
		padInvalidTimer2 = D_padInvalidTime2;
		return;
	}else {
		bAdShort = 0;
		if (adCurResult <= D_offValue) {
			bAdOff = 1;
			bKettleValid = 0;
			padInvalidTimer1 = D_padInvalidTime1;
			padInvalidTimer2 = D_padInvalidTime2;
			return;
		}else {
			bAdOff = 0;
			bKettleValid = 1;
			//filter
			adFilterResult = (adFilterResult * 3 + adCurResult) / 4;
			head = 0;
			end = D_tableSize - 1;
			middle = (head + end) / 2;
			while (head != end) {
				if (adFilterResult > adTable[middle]) {
					head = middle + 1;
					middle = (head + end) / 2;
				}else {
					if (adFilterResult < adTable[middle]) {
						end = middle;
						middle = (head + end) / 2;
					}else {
						break;
					} //end if
				}// end if
			}//end while
			curTemp = middle;
			if (curTemp >= 100) {
				curTemp = 100;
			}
		}
	}
}
