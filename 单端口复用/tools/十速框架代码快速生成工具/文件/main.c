//=============================================================================
//ALL IO PINS' Status is save to a GLOBAL RAM address(P0Temp,P1Temp,P2Temp,P3Temp)
//ex: if u want change P0.1 status,please do not use "=" to write P0 directly
//u should use "and" or "or" to change the P0Temp,and then write P0Temp to P0
//=============================================================================
//=============================================================================
//Name		:main.c
//Purpose	:main loop
//=============================================================================
#define         MAIN_C

#include    "includeAll.h"

//=============================================================================
void main(void)
{	

	CLRWDT = 1; 
	ChangeToFastClk();
	//init_IOMOD();
	PowerOff();
	init_Timer();
	InitTriac();
	timer1s=0;
	StarShow();

	highTemp=100;
	bHighTemp=0;
	bPowerOff=1;
	
	while (1) {
	CLRWDT = 1;                     //clear watchdog
	TimerProcess() ;
	UserTaskSetting() ;
	DisplayDispatcher();
	TasksProcess();
	}//end while
}
void TimerProcess() 
{
	if(b4ms)
	{
		b4ms=0;
		timer1s++;
		timer40ms++;
		timer500ms++;
		timer800ms++;
		
		DisplayScan() ;	
		if(buzzLastTimer >0)
		{
			buzzLastTimer --;
		}
		else
		{
			bBuzz=0;
		}
		keyCounter++;
		if(keyCounter >= 4){
				keyCounter = 0 ;
				GetKeys() ;				
		}
		//------------40ms----
		if(timer40ms>=D_40ms)
		{
			timer40ms=0;
			
		}
		//-------------------500ms-------------------
		if(timer500ms>=D_500ms)
		{
			timer500ms=0;
			b500ms=~b500ms;

		}
		//-----------------800ms----------
		if(timer800ms>D_800ms)
		{
			timer800ms=0;
			
		}
		//---------------1s-------------------
		if(timer1s>=D_1s)
		{
			timer1s=0;
			timer1min++;
			if (starShowTimer>0)
			{
				starShowTimer--;
			}
			if(buzzCounter>0)
			{
				buzzCounter--;
				Buzz();
			}
		}
		//----------------1min------------
		if(timer1min>=3)//D_1min
		{
			timer1min=0;
			
		}
	}
}

void TasksProcess()
{
	if(bAdShort==1)
	{
		Buzz();
		PowerOff();
	}
	else
	{
		if(bAdOff==1||selShowTimer>0)
		{
			bHeat=0;
			bMicroHeat=0;
			bMicroHeat2=0;
			bWattSetted = 0;
			
		}
		else
		{
			
			if (bHighTemp == 0) {
				if ((curTemp >= 90)) {
					if ((padInvalidTimer2 == 0) && (bZs == 1)) { 
						if ((curTemp != lastTemp)) {
							lastTemp = curTemp;
							tempChangeTimer = D_tempChangeTime;
						}else {
							if (tempChangeTimer == 0 ) {
								highTemp = curTemp - 1;
								bHighTemp = 1;
							}
							
						}
					}else {
						tempChangeTimer = D_tempChangeTime;
						
					}
				}else {
					tempChangeTimer = D_tempChangeTime;
					
				}
			}else {
				tempChangeTimer = D_tempChangeTime;
				
			}
						//煮沸过程
			if(bZs==1 && bOrder==0 && padInvalidTimer2==0)
			{
				
				
				
			}
			
				//wf
			if(bWf==1 && bOrder==0 && padInvalidTimer2==0)
			{
				
			
				
			}
		
			//hw
			
			if(bHw==1 && bOrder==0 && padInvalidTimer2==0)
			{

			}
			//order
			if(bOrder==1)
			{
			
			}
			
		}
	}
}
////用户输入
void UserTaskSetting() 
{
	if(bKey==1)
	{
		if(bPowerOn)
		{

			switch(keyValue)
			{
				
			}
		}
		if (keyValue==4) 
		{

		}
		
		bKey=0;
	}
}

void PowerOff()
{
	//timer
		orderTimer=0;
		wfTimer1=0;
		wfTimer2=0;
		wfTimer=0;
		hwTimer=0;
		onlyOnTimer=0;
	
		orderShowTimer=0;
		selShowTimer=0;
		
	//bit
		bPowerOn=0;
		bPowerOff=1;
		bOnlyOn=0;
		bHw=0;
		bWf=0;
		bZs=0;
		
	
		bOrder=0;
		bFirstOrder=1;
		bSetTimer=0;
		bSel=0;
	
		b500ms=1;
	//fire
	
	bWattSetted =0;
	fireType=0;
	//buzz
	buzzCounter=0;
}
void DisplayDispatcher()
{
	'displayStatus=0x00;
	'displayBuffer[]
	'displayBuffer2[]
	if(starShowTimer==0)
	{
		
	}
}


////切换到快时钟
void ChangeToFastClk(void)
{
	CLKCON = 0x03;	//Clock div 2
	STPPCK = 0;
	STPFCK = 0;	
	_nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    _nop_();
	_nop_();
	SELFCK = 1;
    _nop_();	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
    _nop_();
	_nop_();
}



//初始化定时器
void init_Timer()
{
	EA = 1;                         //global interrupt enable
	TH0 = (65536 - 7372) / 256; //4ms timer0 interrupt
	TL0 = (65536 - 7372) % 256;
	
//	TH0 = (65536 - 14000) / 256; //4ms timer0 interrupt
//	TL0 = (65536 - 14000) % 256;
	TMOD=0x01;
	ET0=1;
	TR0=1;
	
	TH2 = (65536-450)/256;      //0.25ms==4khz timer2 interrupt
	RCP2H = TH2  ;
	TL2 = (65536-450)%256;
	RCP2L = TL2  ;
	ET2 = 1;
	TR2 = 1;
}
void StarShow()
{
	displayStatus=0x00;
	displayBuffer[2]=displayBuffer[1]=displayBuffer[0]=0xff;
	starShowTimer=1;
}
//初始化IO模式
void init_IOMOD()
{
P0OE&=0xFF;
P0OE|=0x00;
P1MODL&=0x0F;
P1MODL|=0xA0;
P1MODH&=0x3C;
P1MODH|=0x82;
P2MOD&=0xF3;
P2MOD|=0x08;
P3MODL&=0xCF;
P3MODL|=0x20;
P3MODH&=0xC0;
P3MODH|=0x2A;
}