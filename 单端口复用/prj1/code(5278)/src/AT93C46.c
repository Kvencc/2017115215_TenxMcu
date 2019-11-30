//-------------------
//该芯片使用的是模拟SPI协议，数据通信
#include <intrins.h>
#include "AT93C46.h"

// Write enable must precede all programming modes.
void Ewen(void) 
{
	unsigned char temp,InData;

	cs=0;	
	sk=0;
	cs=1;
	InData=0x98;					// 100 11XXXX
	for(temp=9;temp!=0;temp--) {	// 9
		di=InData&0x80;
		sk=1;	
		sk=0;
		InData<<=1;
	}
	cs=0;
}

// disables all programming instructions.
void Ewds(void) 
{
	unsigned char temp,InData;
	cs=0;
	sk=0;
	cs=1;
	InData=0x80;	// 10000XXXX
	for(temp=9;temp!=0;temp--) {	// 9
		di=InData&0x80;
		sk=1;	
		sk=0;
		InData<<=1;
	}
	cs=0;
}

// Reads data stored in memory, at specified address.
unsigned int Read(unsigned char address) 
{
	unsigned char temp;
	unsigned int result;

	Ewen();
	sk=0;	
	di=1;							// 110 A5-A0
	cs=0;	
	cs=1;
	sk=1;	
	sk=0;							// 1
	address=address&0x3f|0x80;
	for(temp=8;temp!=0;temp--) {	// 8
		di=address&0x80;
		sk=1;	sk=0;
		address<<=1;
	}
	do=1;
	for(temp=16;temp!=0;temp--) {	// 16
		sk=1;
		result=(result<<1)|do;
		sk=0;
	}
	cs=0;
	Ewds();
	return(result);
}

// Writes memory location An - A0.
void Write(unsigned char address,unsigned int InData) 
{
	unsigned char temp;
	Ewen();
	sk=0;	di=1;	// 101 A5-A0
	cs=0;	cs=1;
	sk=1;	sk=0;			// 1
	address=address&0x3f|0x40;
	for(temp=8;temp!=0;temp--) {	// 8
		di=address&0x80;
		sk=1;	sk=0;
		address<<=1;
	}
	for(temp=16;temp!=0;temp--) {	// 16
		di=InData&0x8000;
		sk=1;	sk=0;
		InData<<=1;
	}
	cs=0;	do=1;
	cs=1;	sk=1;
	while(do==0) {			// busy test
		sk=0;	sk=1;
	}
	sk=0;	cs=0;
	Ewds();
}

/*
// Erase memory location An - A0.
void Erase(unsigned char address) {
	unsigned char temp;
	Ewen();
	sk=0;	di=1;	// 111 A5-A0
	cs=0;	cs=1;
	sk=1;	sk=0;			// 1
	address|=0xc0;
	for(temp=8;temp!=0;temp--) {	// 8
		di=address&0x80;
		sk=1;	sk=0;
		address<<=1;
	}
	cs=0;	do=1;
	cs=1;	sk=1;
	while(do==0) {
		sk=0;	sk=1;
	}
	sk=0;	cs=0;
	Ewds();
}

// Erases all memory locations. Valid only at VCC = 4.5V to 5.5V.
void Eral(void) {
	unsigned char temp,InData;
	Ewen();
	cs=0;
	sk=0;
	cs=1;
	InData=0x90;	// 10010XXXX
	for(temp=9;temp!=0;temp--) {	// 9
		di=InData&0x80;
		sk=1;	sk=0;
		InData<<=1;
	}
	cs=0;	do=1;
	cs=1;	sk=1;
	while(do==0) {
		sk=0;	sk=1;
	}
	sk=0;	cs=0;
	Ewds();
}

// Writes all memory locations. Valid only at VCC = 4.5V to 5.5V.
void Wral(unsigned int InData) {
	unsigned char temp,address;
	Ewen();
	cs=0;
	sk=0;
	cs=1;
	address=0x88;	// 10001XXXX
	for(temp=9;temp!=0;temp--) {	// 9
		di=address&0x80;
		sk=1;	sk=0;
		address<<=1;
	}
	for(temp=16;temp!=0;temp--) {	// 16
		di=InData&0x8000;
		sk=1;	sk=0;
		InData<<=1;
	}
	cs=0;	do=1;
	cs=1;	sk=1;
	while(do==0) {
		sk=0;	sk=1;
	}
	sk=0;	cs=0;
	Ewds();
}

*/
/*
unsigned char ReadChar(unsigned char address) 
{
	unsigned char temp=address>>1;
	if(address&0x01) return((unsigned char)(Read(temp)>>8));
	else return((unsigned char)(Read(temp)));
}

void WriteChar(unsigned char address,unsigned char InData) 
{
	unsigned char temp=address>>1;
	if(address&0x01) Write(temp,(unsigned int)(Read(temp)&0x00ff|(InData<<8)));
	else Write(temp,(unsigned int)(Read(temp)&0xff00|InData));
}

void ReadString(unsigned char data *RamAddress,unsigned char RomAddress,
unsigned char Number) 
{
	while(Number!=0) {
		*RamAddress=ReadChar(RomAddress);
		RamAddress++;
		RomAddress++;
		Number--;
	}
}

void WriteString(unsigned char data *RamAddress,unsigned char RomAddress,
unsigned char Number) 
{
	unsigned int temp;
	if(Number==0) return;
	if(RomAddress&0x01) {
		WriteChar(RomAddress,*RamAddress);
		RamAddress++;
		RomAddress++;
		Number--;
	}
	if(Number==0) return;
	while(Number>>1) {
		temp=*RamAddress;
		RamAddress++;
		temp=temp|(*RamAddress)<<8;
		RamAddress++;
		Write(RomAddress>>1,temp);
		RomAddress++;
		RomAddress++;
		Number--;
		Number--;
	}
	if(Number) WriteChar(RomAddress,*RamAddress);
}  */