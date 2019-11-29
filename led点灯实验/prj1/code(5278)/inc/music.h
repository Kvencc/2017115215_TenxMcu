#ifndef _music_h_
#define _music_h_


#define SPK	P2_4				   //无源蜂鸣器输出口

void DelayUs2x(unsigned char t);
void DelayMs(unsigned char t);
void delay(unsigned char t);
void Song(void);
void sing_the_song(void);

//Timer1初始化
void timer1_init(void);




#endif