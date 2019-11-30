
#define	TKCOUNT  4
#define	TKTMR 4			//Ĭ�ϲ���ʱ�� = TKTMR * T1 = 20ms

// #define TKOUTPUT
// #define POWERSAVE
// #define PlugInGetBaseline		//���������ϵ�ƽ��ȡ��ֵ�������ϵ�����ȡ��ֵ

//#define UpdateUpperLimit 2		//������������
//#define UpdateLowerLimit 1		//������������
#define UpdateUpperLimit 5
#define UpdateLowerLimit 4


#define UpdateBaselineTimer 0xe4 // 2000ms  		//���»�ֵʱ��
#define GetBaselineTimer    0x9e // 600ms  		//�ϵ�ȡ��ֵʱ��

#ifdef	MAIN_C
unsigned char idata	gbAntiNoiseTimer;			//����������
int idata TkRawDataArray[TKCOUNT+1];		//����TKͨ����ԭʼֵ
int idata TkBaselineArray[TKCOUNT+1];		//�����õ��Ļ�׼ֵ
unsigned char idata	gBTkCh;					//TKͨ��
unsigned char idata	gBTimer0RollOver;		//TIMER0��ʱ
signed char	idata TkCalcArray[TKCOUNT][5];	//����������
int idata TkOutputArray[TKCOUNT];			//�������Ľ�������AP����ʾ�İ����߶�ֵ
unsigned char idata TkArrayIndex;			//������
int idata TkStatus;							//�������������������İ���״̬��0��ʾ�ɿ� 1��ʾ����
int idata UpdateBasepointArray[TKCOUNT+1];	//����������
unsigned int idata UpdateCounter[TKCOUNT+1];//����������
unsigned char idata AntiNoiseTimer;			//����������
unsigned char idata AntiNoiseDebounceTimer;	//����������
unsigned char idata TkNoise;				//����������
#ifdef	TKOUTPUT
unsigned char idata P0Temp;					//P0��״̬����
unsigned char idata P1Temp;					//P0��״̬����
unsigned char idata P2Temp;					//P0��״̬����
unsigned char idata P3Temp;					//P0��״̬����
unsigned char idata TkDebounceTimer[TKCOUNT];//TKȥ��ʱ��
unsigned int idata TkPressedFlag;			 //TK״̬
#endif
unsigned int idata TkBaselineSetFlag;		//ȡ��׼ֵ��
unsigned char TkBaselineSetNum;				//ȡ��׼ֵ��
bit AllTkBaselineSetFlag;					//ȡ��׼ֵ��
bit	RawDataInvalidFlag;						//�����ж���
bit PlugInGetBaseline;						//�ϵ�ֱ��ȡ��ֵд1���ϵ��ȴ�ƽ��ȡ��ֵд0(ƽ�ȳ���ʱ��ȡ����GetBaselineTimer)
bit UseReferenceTK;							//д1ʹ���ڲ��ο��ż���������д0���òο��ţ�����������
#else

extern unsigned char idata	gbAntiNoiseTimer;
extern int idata TkRawDataArray[TKCOUNT+1];
extern int idata TkBaselineArray[TKCOUNT+1];
extern unsigned char idata gBTkCh;
extern unsigned char idata gBTimer0RollOver;
extern signed char idata TkCalcArray[TKCOUNT][5];
extern int idata TkOutputArray[TKCOUNT];
extern unsigned char idata TkArrayIndex;
extern int idata TkStatus;
extern int idata UpdateBasepointArray[TKCOUNT+1];
extern unsigned int idata UpdateCounter[TKCOUNT+1];
extern unsigned char idata AntiNoiseTimer;
extern unsigned char idata AntiNoiseDebounceTimer;
extern unsigned char idata TkNoise;
#ifdef	TKOUTPUT
extern unsigned char idata P0Temp;
extern unsigned char idata P1Temp;
extern unsigned char idata P2Temp;
extern unsigned char idata P3Temp;
extern unsigned char idata TkDebounceTimer[TKCOUNT];
extern unsigned int idata TkPressedFlag;
#endif
extern unsigned int idata TkBaselineSetFlag;
extern unsigned char TkBaselineSetNum;
extern bit AllTkBaselineSetFlag;
extern bit RawDataInvalidFlag;
extern bit PlugInGetBaseline;
extern bit UseReferenceTK;
#endif
