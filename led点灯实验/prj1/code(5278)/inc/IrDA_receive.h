#ifndef  _IrDA_receive_h_
#define  _IrDA_receive_h_

//uint uchar宏定义
#define u8 		unsigned char
#define u16	 	unsigned int
#define uchar 	unsigned char
#define uint 	unsigned int

#define in P2_0

extern uchar sj[4];			    //放置解码数据
extern u16 IrDA_cnt;		    //用于对红外波段进行计数
extern bit biaoz;


void IrDA_receive(void);	 			//注意TImer2_init中的TR2要置0

//发送一个字节
extern void SendByte(unsigned char dat);

//发送两个字节
extern void SendWord(unsigned int dat);




#endif