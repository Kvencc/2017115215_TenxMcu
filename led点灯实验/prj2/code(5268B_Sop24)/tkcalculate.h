//============================================================================================
//Function : void TkCalculate(unsigned char uctkcount);
//used to calculate the TOUCH KEY data,the result is save in TkOutputArray
//input : uctkcount = ALL USED TOUCH KEY CHANNEL COUNT
//used RAM : 
//	TkRowDataArray[(TKCOUNT+1) * 2)bytes]: used to save TOUCH KEY RAW data
//	TkBaselineArray[(TKCOUNT+1) * 2)bytes]: used to save TOUCH KEY BASELINE data
//	RawDataInvalidFlag[1bit]: if this bit is 1 means NOISE is detected,all TOUCH KEY output will be clear
//	TkCalcArray[(TKCOUNT * 5)bytes]: used to calculate the TOUCH KEY data to check if the KEY is pressed or not
//	TkArrayIndex[1 byte]: used to switch the calculate buffer
//	TkOutputArray[(TKCOUNT * 2)bytes]: used to save calculate result,the result will be saved in the first half of this array
//	ALL ARRAY's INDEX is same to the TkChannelTable's TOUCH KEY INDEX
//============================================================================================
void TkCalculate(unsigned char uctkcount);