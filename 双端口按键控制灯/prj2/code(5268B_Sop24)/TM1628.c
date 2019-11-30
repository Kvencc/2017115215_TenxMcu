#define __tm1628_c
#include "includeAll.h"

//only write a byte data to TM1628 
void WriteByteTo1628(uint8_t byte)
{
    uint8_t i ;
	
	P_1628_STB = 0 ;
    _nop_();
	_nop_();
	for(i=0 ; i<8 ; i++){
		P_1628_CLK = 0 ;		
		if(byte & 0x01){
			P_1628_DIO = 1;
		}
		else{
			P_1628_DIO = 0;
			
		}
      _nop_();
	    _nop_();
			_nop_();
	    _nop_();
			_nop_();
	    _nop_();
		P_1628_CLK = 1 ;
        _nop_();
				_nop_();
		byte >>= 1;
	} 
}
//
void Init1628()
{
    P_1628_STB = 1;
	P_1628_CLK = 1;
	P_1628_DIO = 1;
	//display mode 
	WriteByteTo1628(D_mode7_10SEG) ;
    P_1628_STB = 1;
	//write data to display Ram, address auto add 1 
	WriteByteTo1628(D_burstWrite) ;
    P_1628_STB = 1;
   	WriteByteTo1628(D_light10);
    P_1628_STB = 1; 
}
//
void Dislay1628()
{
	uint8_t i ;
	uint8_t byte ;
	
    //
    Init1628() ;
	//start address 0x00
	WriteByteTo1628(D_adress00) ;
	for(i=0; i<7; i++){
		byte = tm1628Buffer[i] ;
		WriteByteTo1628(byte) ;
		byte = (tm1628Buffer[i] >> 8) ;
		WriteByteTo1628(byte) ;
	}
    P_1628_STB = 1;
}
