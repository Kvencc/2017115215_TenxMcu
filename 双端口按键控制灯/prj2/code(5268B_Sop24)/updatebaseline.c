//=============================================================================
//Name		:updatebaseline.c
//Purpose	:update touch key baseline
//=============================================================================
#define		UPDATEBASELINE_C
#include	"global.h"
//=============================================================================
// Function:	void UpdateBaseline(void)
// Purpose:		update touch key baseline
// Input:		none
// OutPut:		none
// Author:
// 如果无按键(TKSTATUS为0)且无干扰(RawDataInvalidFlag为0)则检测更新，否则所有更新计时全部清0然后跳出
// 1,如果TkRawDataArray值与对应的TkBaselineArray的值不一致到步骤2，否则无需更新直接跳出
// 2,开始取当前TkRawDataArray值作为一个基准点UpdateBasepointArray，并开始更新计时UpdateCounter，
//   如果后续在更新时间UpdateCounter达到的情况下所有的TkRawDataArray值都满足在基准点UpdateBasepointArray的上下限范围内则更新最后一个TkRawDataArray作为新的TkBaselineArray,
//   否则重复步骤2
//=============================================================================
void UpdateBaseline(unsigned char uctkcount,unsigned char ucupperlimit,unsigned char ucunderlimit,unsigned int ucupdatetimer)
{
	unsigned char tktemp;
	int i;
	if(UseReferenceTK) uctkcount = uctkcount + 1;
	if(TkStatus || RawDataInvalidFlag)
	{
		for(tktemp = 0;tktemp < uctkcount;tktemp++)
		{
			UpdateCounter[tktemp] = 0;
		}
		return;
	}
	for(tktemp = 0;tktemp < uctkcount;tktemp++)
	{
		if(TkBaselineArray[tktemp] != TkRawDataArray[tktemp])
		{
			if(UpdateCounter[tktemp] < 0x80)
			{
				UpdateCounter[tktemp] = 0x81;
				UpdateBasepointArray[tktemp] = TkRawDataArray[tktemp];
				continue;
			}
			UpdateCounter[tktemp]++;
            i = TkRawDataArray[tktemp] - UpdateBasepointArray[tktemp]; 
			if((i > ucupperlimit)||(i < -ucunderlimit))
			{
				UpdateCounter[tktemp] = 0;
			}
		}
	}
	for(tktemp = 0;tktemp < uctkcount;tktemp++)
	{
		if(UpdateCounter[tktemp] >= ucupdatetimer)
		{
			UpdateCounter[tktemp] = 0;	
			TkBaselineArray[tktemp] = TkRawDataArray[tktemp];
			if(!AllTkBaselineSetFlag)
			{
				if((TkBaselineSetFlag & (1 << tktemp)) == 0)
				{
					TkBaselineSetFlag |= (1 << tktemp);
					TkBaselineSetNum++;
					if(TkBaselineSetNum >= uctkcount){
                        AllTkBaselineSetFlag = 1;
                    } 
                    
				}
			}
		}
	}
}