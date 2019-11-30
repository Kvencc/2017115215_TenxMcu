#ifndef __tm1628_h
#define __tm1628_h

//Hal-------------------------
#define  P_1628_STB  P3_4
#define  P_1628_CLK  P3_5
#define  P_1628_DIO  P3_6
//Const-----------------------
//TM1628�Զȵ���
#define D_lightOff  0x80
#define D_light1    0x89
#define D_light2    0x8A
#define D_light4    0x8B
#define D_light10    0x8C
#define D_light12    0x8D
#define D_light13    0x8E
#define D_light14    0x8F
//��ʾģʽ
#define D_mode4_13SEG   0x00
#define D_mode5_12SEG   0x01
#define D_mode6_11SEG   0x02
#define D_mode7_10SEG   0x03
//��������
#define D_burstWrite   0x40
#define D_byteWrite     0x44
//��ʾ���ݵĵ�ַ
#define D_adress00         0xC0
#define D_adress01         0xC1
#define D_adress02         0xC2
#define D_adress03         0xC3
#define D_adress04         0xC4
#define D_adress05         0xC5
#define D_adress06         0xC6
#define D_adress07         0xC7
#define D_adress08         0xC8
#define D_adress09         0xC9
#define D_adress0A         0xCA
#define D_adress0B         0xCB
#define D_adress0C         0xCC
#define D_adress0D         0xCD
//set dispaly bit mask
#define D_seg1  0x0001
#define D_seg2  0x0002
#define D_seg3  0x0004
#define D_seg4  0x0008
#define D_seg5  0x0010
#define D_seg6  0x0020
#define D_seg7  0x0040
#define D_seg8  0x0080
#define D_seg9  0x0100
#define D_seg10 0x0200
//grid1--7 map com0--6
#define D_grid1  0
#define D_grid2  1
#define D_grid3  2
#define D_grid4  3
#define D_grid5  4
#define D_grid6  5
#define D_grid7  6

//Var---------------------------------------
    #ifdef __tm1628_c
        // Ram 14Bytes
        uint16_t idata tm1628Buffer[7] ;
	#else
	    extern 	uint16_t idata tm1628Buffer[] ;

	#endif
//Function-----------------------------------

void WriteByteTo1628(uint8_t byte);
void Dislay1628() ;
void Init1628() ;
#endif
