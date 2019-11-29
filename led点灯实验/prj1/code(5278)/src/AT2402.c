
//-------------------
//该芯片使用的是IIC协议，数据通信
#include <intrins.h>
#include "AT2402.h"



//IIC_start
void iic_start(void)
{
   	scl = 1;
  	sda = 1;
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
 	sda = 0;	 //数据线由高到低为通信的开始
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	scl = 0;
	
}


//IIC_stop
void iic_stop(void)
{
	 sda = 0;
	 scl = 1;
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();

	 sda = 1;	  //数据线由低到高为通信结束

	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();
	 sda = 0;
}

//IIC_write_byte
void iic_write(u8 byte)
{
	u8 i;

	for (i = 0; i < 8; i++) {

		if((byte << i) & 0x80)
			sda = 1;   //判断发送位
        else  
	   		sda = 0; 

  		scl = 1;
 		_nop_();
		_nop_();
 		_nop_();
		_nop_();
		_nop_();
		_nop_();
  		_nop_();
 		scl = 0;
	}
}
//iic_ack
bit iic_ack(void)
{
	bit ack;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
  	_nop_();
  	_nop_();
	_nop_();
	_nop_();
	sda = 1;
	scl = 1;

	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	if (sda == 1)
		ack = 1;     	  //未应答
    else 
		ack = 0;        //应答
    scl = 0;

    _nop_();
    _nop_();
	_nop_();
	_nop_();
	_nop_();

	return ack;
}


//IIC_read_byte
u8 iic_read(void)
{
    u8 i;
	u8 byte = 0;
//	bit ack;

	for (i = 0; i < 8; i++) {
		byte <<= 1;
		if (sda == 1)
			byte++;
		
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		scl = 1;

		_nop_();		
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();

		scl = 0	;
	}
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		sda = 1;
		return byte;

}	

//IIC_write_
bit c2404_write(u8 dat)
{
	iic_start();

	iic_write(dev_addrw);
	if (iic_ack())
		return 0;				  //如果未应答，则返回

	iic_write(word_addr);
	if (iic_ack())
		return 0;

	iic_write(dat);
	if (iic_ack())
		return 0;
	iic_stop();

}

//IIC_random_read
u8 c2404_read(void)
{
	u8 dat = 0;

	iic_start();

	iic_write(dev_addrw);
	if (iic_ack())
		return 0;				  //如果未应答，则返回

	iic_write(word_addr); 
	if (iic_ack())
		return 0;

	iic_start();

	iic_write(dev_addrr);
	if (iic_ack())
		return 0;				  //如果未应答，则返回

	dat = iic_read();

	iic_stop();
	return dat;
}



void c2402_app(void)
{
	u8 dat = 0;

		c2404_write(0x0a);
		dat = c2404_read();
		c2404_write(0x0c);
	 	dat = c2404_read();
//		delayms_lo(500);
		
}