#ifndef __93c46_h_
#define __93c46_h_

#include <REGtenxTM52F5278.h>
//#include "delay.h"

//uint uchar∫Í∂®“Â
#define u8 		unsigned char
#define u16	 	unsigned int
#define uchar 	unsigned char
#define uint 	unsigned int



#define	cs	P2_2  
#define sk 	P1_1
#define di	P1_2
#define do	P1_3

// Write enable must precede all programming modes.
void Ewen(void);

// disables all programming instructions.
void Ewds(void);
 
// Reads data stored in memory, at specified address.
unsigned int Read(unsigned char address); 

// Writes memory location An - A0.
void Write(unsigned char address,unsigned int InData); 




#endif