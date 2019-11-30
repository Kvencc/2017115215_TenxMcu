#ifndef __LED_DRIVER_H_
#define __LED_DRIVER_H_

#define u8 unsigned char
#define u16 unsigned int





//通过内部LED驱动4个数码管显示,对应开发板从左边数0-3
void com0_disp(u8 com0_seg);
void com1_disp(u8 com1_seg);
void com2_disp(u8 com2_seg);
void com3_disp(u8 com3_seg);









#endif