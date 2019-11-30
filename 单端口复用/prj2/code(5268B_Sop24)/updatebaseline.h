//============================================================================================
//Function : void UpdateBaseline(unsigned char uctkcount);
//used to update the BASELINE to adapt the environment
//input : 	uctkcount = 通道数量
//			ucupperlimit = 更新baseline的上限	ucunderlimit = 更新baseline的下限，即正负浮动值
//			ucupdatetimer = 更新时间 
//used RAM : 
//	TkRowDataArray[(TKCOUNT+1) * 2)bytes]: used to save TOUCH KEY RAW data
//	TkBaselineArray[(TKCOUNT+1) * 2)bytes]: used to save TOUCH KEY BASELINE data
//	RawDataInvalidFlag[1bit]: if this bit is 1 means NOISE is detected,all TOUCH KEY output will be clear
//	UpdateBasepointArray[(TKCOUNT+1) * 2)bytes]: get a basepoint data,use this data as a START point 
//	UpdateCounter[(TKCOUNT+1)bytes]: update timer,if bigger than a const value then update the BASELINE
//	TkStatus[2 bytes]: the TOUCH KEY status ,bit0~bit15 indicate TK(TkChannelTable[0])~TK(TkChannelTable[TKCOUNT)])
//						if 1 means the TOUCH KEY has been pressed
//	ALL ARRAY's INDEX is same to the TkChannelTable's TOUCH KEY INDEX
//============================================================================================
void UpdateBaseline(unsigned char uctkcount,unsigned char ucupperlimit,unsigned char ucunderlimit,unsigned int ucupdatetimer);
							   