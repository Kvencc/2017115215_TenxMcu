#include <REGtenxTM52F5278.h>
#include "IrDA_receive.h"
#include "intrins.h"

uchar sj[4];		//放置解码数据


bit biaoz;


void IrDA_receive() 
{
	 uchar i;
	 uchar j;
	 bit startflag;
	 u16 re_dat[2];

	if(!in) {						    //下降沿（电平）有效
		_nop_();			 	
		_nop_();
		_nop_();
		_nop_();						//nop延时进行抖动处理,防止误触发
		_nop_();			 
		_nop_();
		_nop_();						
		if(!in) {						//约9.2ms的低电平
			TR2 = 1;
			while(!in){
				if(IrDA_cnt > 300)		//定时器2计数20us->600 40us-> 
					break;
			}
			TR2 = 0;
			re_dat[0] = IrDA_cnt;
			
		 }

		 if(in&& (re_dat[0] > 150)){	//约4.6ms的高电平	20us->400 40us->
				TR2 = 1;
				IrDA_cnt = 0;
				while(in) {
					if(IrDA_cnt > 150)	//20us->300 40us->
						break;
				}
				TR2 = 0;

				re_dat[1] = IrDA_cnt;
		}
		
		IrDA_cnt = 0;
		//20us->400 600 200 300 40us->
		if(re_dat[0] > 150 && re_dat[0] < 300 	 //帧头的电平时间在此区间内认为是有效帧头
			&& re_dat[1] > 90 && re_dat[1] < 150)	
			startflag = 1;
		re_dat[0] = 0;
		re_dat[1] = 0;
	}
		

	if(startflag) {					  //帧头有效接收数据 格式为 2字节ID码， 1字节数据， 1字节数据的反	
		startflag = 0;				  //码的格式参考ircode文档
		IrDA_cnt = 0;
		re_dat[0] = 0;
		re_dat[1] = 0;
		for(i = 0; i < 4; i++) {
			for(j = 0; j < 8; j++) {
				sj[i] >>= 1;
				if(!in) {
					_nop_();
					_nop_();
					_nop_();
					_nop_();
					_nop_();				
					_nop_();
					TR2 = 1;
					while(!in) {						
						if(IrDA_cnt > 20)	 //20us->35 40us->
							break;
					}
					TR2 = 0;
					re_dat[0] = IrDA_cnt;				//34 3d 3e
			  }
			  if(in && (re_dat[0] > 6  && re_dat[0] < 20)) {  //20us->20 40 40us->
					IrDA_cnt = 0;
					
					TR2 = 1;
					while(in) {
						if(IrDA_cnt > 55)	//20us->110 40us->
						break;
					}
					TR2 = 0;

					re_dat[1] = IrDA_cnt;	 			
					IrDA_cnt = 0;

					re_dat[0] = re_dat[0] + re_dat[1];
				}

 					if(re_dat[0] > 40 && re_dat[0] < 75)	//此时为1 	 20us->90 150 40us->
						sj[i] |= 0x80;
					if(re_dat[0] > 16 && re_dat[0] < 40)	//此时为0   20us->40 80 40us-> 
						sj[i] &= 0x7f;
					re_dat[0] = 0;
			}

		}
	   	  if(i>=4)						   	//4字节数据收完，biaoz置位
		  	 biaoz=1;

	  }
	  
 }
  
  