#define     MAIN_C

#include    "includeAll.h"
uint8_t xdata csTimeFlag _at_  0x1fe0;
uint8_t xdata csTime _at_  0x1fe1;
uint8_t settedCsTime;
uint8_t xdata hcsTimeFlag _at_  0x1fe2; //手动加水
uint8_t xdata hcsTime _at_ 0x1fe3; //手动加水
uint8_t settedHcsTime;  //手动加水
//=============================================================================
void main(void)
{
	ChangeToFastClk();
	InitialIoport();
	InitialRegister();
	InitVar();
	powerDelayCounter = 0x0fff;
	while (powerDelayCounter > 0) {
		powerDelayCounter--;
		CLRWDT = 1;
	}
	Init1628();
	EA = 1;     //global interrupt enable
	Buzz();
	bSelfTest = 1;
	selfTestTimer = 2;
	//powerup InitVar
	if (csTimeFlag != 0x5A) {
		settedCsTime = D_assCsTime;
	}else{
		settedCsTime = csTime;
	}
	// if (hcsTimeFlag != 0x5A) {
	//  settedHcsTime = D_hcsTime;
	// }else{
	//  settedHcsTime = hcsTime;
	// }
	//
	settedHcsTime = D_hcsTime;
	F_turnOnWDT();
	while (1) {
		CLRWDT = 1;         //clear watchdog
		if (bKettleValid) {
			padValidTimer = D_padValidTime;
		}else {
			F_csOff();
			bCsing = 0;
			bHcsOn = 0;
			F_hcsLedOff();
			F_ssOff();
			bTestWaterLevel = 0;
			testWaterCounter = 0;
			testWaterLowCounter = 0;
			bWaterLow = 0;
			bWattSetted = 0;
			bMicroHeat = 0;
			bWater100 = 0;
			bWfSetted = 0;
			wfTimer = D_assWfTime;
			hssTimer = 0;
			if ((padValidTimer == 0)) {
				SsOff();
			}
		}
		//low water
		if (bWaterLow == 1) {
			F_ssOff();
			bWattSetted = 0;
		}
		//get highTemp
		if (bHighTemp == 0) {
			if (curTemp >= 80) {
				if ((bSsRelayOn == 1) || (bMicroHeat == 1)) {
					if ((curTemp < (lastTemp - 1)) || (curTemp > lastTemp)) {
						lastTemp = curTemp;
						tempChangeTimer = D_tempChangeTime;
					}else {
						if (tempChangeTimer == 0) {
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
		//Hss  Pro
		//Ass Pro
		if ((bWaterLow == 0) && (padInvalidTimer2 == 0) && (bTestWaterLevel == 0)) {
			if (((bAssOn == 1) || (bHssOn == 1)) && (bHwOn == 0)) {
				if ((curTemp >= highTemp) && (bWater100 == 0)) {
					bHighTemp = 1;
					if (b100Buzz == 0) {
						Buzz();
						b100Buzz = 1;
					}
					F_ssOff();
					if (bWfSetted == 0) {
						wfTimer = D_assWfTime;
						bWfSetted = 1;
					}
					bWater100 = 1;
					bMicroHeat = 1;
					bWattSetted = 0;
					fireType = D_fireType_1_16;
					bWattSetted = 1;
					// if (bHssOn == 1) {
					//  if (settedTemp != 100) {
					//      bHssOn = 0;
					//      bWattSetted = 0;
					//      bWfSetted = 0;
					//  }
					// }
				}
				if (curTemp <= (highTemp - D_highStep)) {
					if ((bHcsOn == 0)) {
						if (relayOffTimer == 0) {
							F_ssOn();
						}
					}
					bWater100 = 0;
					bMicroHeat = 0;
					bWattSetted = 0;
					//b100Buzz = 0;
					//bWfSetted = 0;
				}
                if (curTemp <= (highTemp - 5)) {
					b100Buzz = 0;
				}
				if (curTemp > (highTemp - D_highStep) && (curTemp <= (highTemp - 1))) {
					F_ssOff();
					if ((bWfSetted == 1) && (bWater100 == 1)) {
						relayOffTimer = D_relayOffTime;
						bMicroHeat = 1;
						bWattSetted = 0;
						fireType = D_fireType_4_16;
						bWattSetted = 1;
						bWater100 = 0;
					}
					if (bMicroHeat == 0) {
						relayOffTimer = D_relayOffTime;
						bMicroHeat = 1;
						bWattSetted = 0;
						fireType = D_fireType_4_16;
						bWattSetted = 1;
						bWater100 = 0;
					}
				}
			}
			//Hw pro
			if ((bHwOn == 1) && (bAssOn == 1)) {
				if (hwTimer == 0) {
					Buzz();
					SsOff();
				}else{
					if (curTemp >= settedTemp) {
						F_ssOff();
						bWattSetted = 0;
						bMicroHeat = 0;
					}else {
						if (curTemp <= (settedTemp - D_hwStep)) {
							if (relayOffTimer == 0) {
								F_ssOn();
							}
							bWater100 = 0;
							bMicroHeat = 0;
							bWattSetted = 0;
						}else {
							F_ssOff();
							if (bMicroHeat == 0) {
								relayOffTimer = D_relayOffTime;
								bMicroHeat = 1;
								bWattSetted = 0;
								fireType = D_fireType_4_16;
								bWattSetted = 1;
							}
						}
					}
				}
			}
		}
		//wf Pro
		if (bWfSetted == 1) {
			if (wfTimer == 0) {
				if ((bAssOn == 1) || (bHssOn == 1)) {
					Buzz();
					SsOff();
				}
			}else {
				//
				if (wfOnOffTimer == 0) {
					if (bWattSetted == 1) {
						bWattSetted = 0;
						wfOnOffTimer = D_wfOffTime;
					}else {
						bWattSetted = 1;
						wfOnOffTimer = D_wfOnTime;
					}
				}
			}
		}
		//cstime Adjust
		if ((bCsAdjust == 1) && (tempAdjustTimer == 0)) {
			bCsAdjust = 0;
			//write EEprom
			if (csTime != settedCsTime) {
				if (csTimeFlag != 0x5a) {
					INTE1 = 0xA0;
					csTimeFlag = 0x5a;
					INTE1 = 0x00;
					INTE1 = 0xA0;
					csTime = settedCsTime;
					INTE1 = 0x00;
				}else{
					INTE1 = 0xA0;
					csTime = settedCsTime;
					INTE1 = 0x00;
				}
			}
			// if (hcsTime != settedHcsTime) {
			//  if (hcsTimeFlag != 0x5a) {
			//      INTE1 = 0xA0;
			//      hcsTimeFlag = 0x5a;
			//      INTE1 = 0x00;
			//      INTE1 = 0xA0;
			//      hcsTime = settedHcsTime;
			//      INTE1 = 0x00;
			//  }else{
			//      INTE1 = 0xA0;
			//      hcsTime = settedHcsTime;
			//      INTE1 = 0x00;
			//  }
			// }
		}
		//temp adjust
		if ((bTempAdjust == 1) && (tempAdjustTimer == 0)) {
			Buzz();
			bTempAdjust = 0;
			hssTimer = 0;
			bHwOn = 1;
			bAssOn = 1;
			hwTimer = D_hwTime;
			if (settedTemp >= 100) {
				bHwOn = 0;
			}
			bWater100 = 0;
			bMicroHeat = 0;
			bWattSetted = 0;
			if (bKettleValid == 1) {
				bTestWaterLevel = 1;
				testWaterLowCounter = 0;
				testWaterCounter = 0;
				padInvalidTimer1 = D_padInvalidTime1;
				padInvalidTimer2 = D_padInvalidTime2;
			}
		}
		// //no water Pro
		// if ((bMotorOn == 1) && (csTimer <= 10) && (bAssOn == 1)) {
		//  if (bKettleValid == 1) {
		//      bTestWaterLevel = 1;
		//  }
		//  if (bWaterLow == 1) {
		//      //DISPLAY E3:
		//      if (csTimer < 5) {
		//          Buzz();
		//          bAssOn = 0;
		//          bHcsOn = 0;
		//          bAssToHcsOn = 0;
		//          F_ssOff();
		//          F_assLedOff();
		//          F_hcsLedOff();
		//          F_csOff();
		//      }
		//  }
		// }
		//Motor stop
		if ((bMotorOn == 1) && (csTimer == 0)) {
			if (bKettleValid == 1) {
				bTestWaterLevel = 1;
			}
			F_csOff();
			bHcsOn = 0;
			F_hcsLedOff();
		}
		//全自动加水结束后，测试水位，如果没水则关机
		if ((bMotorOn == 0) && (bCsing == 1)) {
			if ((bTestWaterLevel == 0)) {
				bCsing = 0;
				if ((bWaterLow == 1)) {
					Buzz();
					PowerOff();
				}
			}
		}
		//Ass Water Level Pro
		if ((bAssOn == 1) && (padInvalidTimer2 == 0) && (bTestWaterLevel == 0)) {
			//
			if ((bWaterLow == 1)) {
				bAssToHcsOn = 1;
				bHcsOn = 1;
				csTimerBack = settedCsTime;
				F_ssOff();
			}
		}
		//Hcs Pro
		if ((bHcsOn == 1) && (padInvalidTimer2 == 0)) {
			if (bMotorOn == 0) {
				csTimer = csTimerBack;
				F_csOn();
				bCsing = 1;
			}
		}
		//key Process
		GetKey();
		if (bPowerOn) {
			switch (keyValue) {
				case D_keyHcsOff:
					if ((bHcsOn == 1)) {
						Buzz();
						bHcsOn = 0;
						F_hcsLedOff();
						F_csOff();
					}
					break;
				case D_keyHcsOn:
					if (bHcsOn == 0) {
						Buzz();
						if (bKettleValid) {
							bHcsOn = 1;
							bAssToHcsOn = 0;
							F_hcsLedOn();
							bIdle = 0;
							csTimerBack = settedHcsTime;
						}
					}
					break;
				case D_keyHss:
					Buzz();
					bCsAdjust = 1;
					tempAdjustTimer = D_csTimeAdjustTime;
					settedCsTime += 2;
					if (settedCsTime > 36) {
						settedCsTime = 28;
					}
					// if (bAssOn == 1) {
					//  bCsAdjust = 1;
					//  tempAdjustTimer = D_csTimeAdjustTime;
					//  settedCsTime += 2;
					//  if (settedCsTime > 36) {
					//      settedCsTime = 28;
					//  }
					// }else{
					//  if (bHcsOn == 1) {
					//      bCsAdjust = 1;
					//      tempAdjustTimer = D_csTimeAdjustTime;
					//      settedHcsTime += 2;
					//      if (settedHcsTime > 26) {
					//          settedHcsTime = 18;
					//      }
					//  }
					// }
					break;
				case D_keyAss:
					Buzz();
					bAssToHcsOn = 0;
					if ((bAssOn == 1) || (bHwOn == 1)) {
						bTempAdjust = 0;
						bAssOn = 0;
						bHwOn = 0;
						bHcsOn = 0;
						bHssOn = 0;
						F_ssOff();
						F_csOff();
						bWattSetted = 0;
						bWfSetted = 0;
						hwIndex = 0;
						settedTemp = hwTempTable[hwIndex];
					}else {
						bTempAdjust = 1;
						tempAdjustTimer = D_tempAdjustTime;
						bIdle = 0;
						F_assLedOn();
						padValidTimer = D_padValidTime;
						//
						bAssOn = 0;
						bHssOn = 0;
						bHwOn = 0;
						bHcsOn = 0;
						F_csOff();
						bWfSetted = 0;
						bWattSetted = 0;
						bWater100 = 0;
						bMicroHeat = 0;
						hssTimer = 0;
						if (hwIndex >= D_hwTableSize) {
							hwIndex = 0;
						}
						settedTemp = hwTempTable[hwIndex];
						hwIndex++;
					}
					break;
			}// end switch
		}
		if (keyValue == D_keyPower) {
			Buzz();
			if (bPowerOn == 1) {
				bPowerOn = 0;
				PowerOff();
			}else {
				bPowerOn = 1;
				bIdle = 1;
				idleTimer = D_idleTime;
			}
		}
		keyValue = 0;
		//
		if (b4ms == 1) {
			b4ms = 0;
			GetTemp();
			if (buzzLastTimer > 0) {
				buzzLastTimer--;
			}
			timer40ms++;
			timer500ms++;
			timer1s++;
		}
		if (timer40ms >= D_40ms) {
			timer40ms = 0;
			bAdTest = ~bAdTest;
			if (bAdTest == 1) {
				//GetTemp();
				if (bTestWaterLevel == 1) {
					P3MODL |= 0xc0;     //ad0=P3.3
				}else {
					P3MODL &= 0x3f;
					P3MODL |= 0x80;     //P3.3 mode2
					F_clrWater();
				}
			}else {
				if ((bTestWaterLevel == 1) && (padInvalidTimer1 == 0)) {
					TestWaterLevel();
				}
			}
		}
		if (timer500ms >= D_500ms) {
			timer500ms = 0;
			bLedFlash = !bLedFlash;
			if (buzzCounter > 0) {
				Buzz();
				buzzCounter--;
			}
			DisplayDispatcher();
		}
		if (timer1s >= D_1s) {
			timer1s = 0;
			//user code...
			if (selfTestTimer > 0) {
				selfTestTimer--;
			}
			if (csTimer > 0) {
				csTimer--;
			}
			if (hssTimer > 0) {
				hssTimer--;
			}
			if (padInvalidTimer1 > 0) {
				padInvalidTimer1--;
			}
			if (padInvalidTimer2 > 0) {
				padInvalidTimer2--;
			}
			if (tempChangeTimer > 0) {
				tempChangeTimer--;
			}
			if (tempAdjustTimer > 0) {
				tempAdjustTimer--;
			}
			if (relayOffTimer > 0) {
				relayOffTimer--;
			}
			if (wfOnOffTimer > 0) {
				wfOnOffTimer--;
			}
			//
			timer1m++;
			if (timer1m >= D_1m) {
				//1m
				timer1m = 0;
				//user code...
				if (padValidTimer > 0) {
					padValidTimer--;
				}
				if (wfTimer > 0) {
					wfTimer--;
				}
				if (hwTimer > 0) {
					hwTimer--;
				}
				timer1h++;
				if (timer1h >= D_1h) {
					//1h
					timer1h = 0;
					//user code...
				}
			}
		}
	}
}
//==============================================================================
void InitVar()
{
	highTemp = 100;
	csTimer = 0;
	xdTimer = 0;
	testWaterCounter = 0;
	testWaterLowCounter = 0;
	padInvalidTimer1 = D_padInvalidTime1;
	padInvalidTimer2 = D_padInvalidTime2;
	padValidTimer = D_padValidTime;

	timer40ms = D_40ms;
	timer500ms = D_500ms;
	timer1s = D_1s;
	timer1m = D_1m;
	timer1h = D_1h;
	buzzCounter = 0;

	F_csOff();
	F_ssOff();

	bPowerOn = 0;
	bTestWaterLevel = 0;
	bWaterLow = 0;
	bAssOn = 0;
	bHssOn = 0;
	bHwOn = 0;
	bHcsOn = 0;
	bAssToHcsOn = 0;
	bHighTemp = 0;
	bCsAdjust = 0;
	bCsing = 0;
	hwIndex = 0;
	settedTemp = hwTempTable[hwIndex];
}
//==============================================================================//==============================================================================
void PowerOff()
{
	bPowerOn = 0;
	bHxdOn = 0;
	SsOff();
	bCsAdjust = 0;
	bCsing = 0;
}
//=============================================================================
void SsOff()
{
	F_csOff();
	F_ssOff();
	bAssOn = 0;
	bHssOn = 0;
	bHwOn = 0;
	bHcsOn = 0;
	bAssToHcsOn = 0;
	bTempAdjust = 0;
	bResetStepMotor = 0;
	bTestWaterLevel = 0;
	bWater100 = 0;
	bWfSetted = 0;
	bWattSetted = 0;
	bMicroHeat = 0;
	hwIndex = 0;
	settedTemp = hwTempTable[hwIndex];
}
//==============================================================================
void DisplayDispatcher(void)
{
	if (bSelfTest == 1) {
		F_displayAll();
		if (selfTestTimer == 0) {
			bSelfTest = 0;
		}
		goto exit;
	}
	F_displayClrAll();
	if (bPowerOn == 0) {
		F_powerIconOn();
		F_powerLedOn();
		goto exit;
	}else {
		F_powerIconOff();
		F_powerLedOn();
		F_displayPowerOn();
	}

	if (bHcsOn) {
		if (bAssToHcsOn == 0) {
			F_hcsLedOn();
		}
	}
	if (bCsAdjust) {
		if (bLedFlash) {
			F_csTimeLedOn();
		}
	}
	if (bTempAdjust) {
		if (bLedFlash) {
			F_assLedOn();
		}
	}else{
		if (bAssOn) {
			F_assIconOn();
			F_assLedOn();
		}
	}
	//sz
	if (bCsAdjust == 1) {
		F_csIconOn();
		F_displayClrSz();
		// if (bAssOn) {
		//  DisplayNumber(settedCsTime);
		// }else{
		//  DisplayNumber(settedHcsTime);
		// }
		DisplayNumber(settedCsTime);
		goto exit;
	}
	if (bTempAdjust == 1) {
		F_displayTempLogo();
		F_displayClrSz();
		DisplayNumber(settedTemp);
		goto exit;
	}
	if (bMotorOn) {
		F_csIconOn();
		F_displayClrSz();
		DisplayNumber(csTimer);
		goto exit;
	}
	if ((bAssOn == 1) || (bHwOn == 1) || (bHssOn == 1)) {
		if (bAdShort) {
			F_displayAdShort();
			goto exit;
		}
		if (bAdOff) {
			F_displayAdOff();
			goto exit;
		}
		if (bWaterLow == 1) {
			F_displayWaterLow();
			goto exit;
		}
		//
		F_displayTempLogo();
		DisplayNumber(curTemp);
		goto exit;
	}
	//
	if (bIdle == 0) {
		bIdle = 1;
		idleTimer = D_idleTime;
	}
	if (bIdle == 1) {
		idleTimer--;
		if (idleTimer == 0) {
			idleTimer = D_idleTime;
			PowerOff();
		}
	}
 exit:
	DisplayScan();
}
//==============================================================================
void GetKey()
{
	static int16_t lastTkStatus = 0;
	static uint8_t longPressCounter;
	uint8_t mask, i;
	//����ʱ��[5 * 4ms Timer0��ʱ]��[20msT3]��ʱ = 20ms�������޸���T0��T3��ʱʱ����Ҫȷ������ʱ��Ϊ20ms

		#ifdef POWERSAVE
	PRO_SLEEP20MS();
		#else
	if (gBTimer0RollOver >= 5)
		#endif
	{
		gBTimer0RollOver = 0;
		TKScan();
		mask = 0x01;
		for (i = 0; i < TKCOUNT; i++) {
			if (((lastTkStatus & mask) == 0) && (TkStatus & mask)) {
				//click
				keyValue = i + 1;
				longPressCounter = 0;
				break;
			}
			if (((lastTkStatus & mask)) && (TkStatus & mask)) {
				longPressCounter++;
				if (longPressCounter >= D_longPressCount) {
					longPressCounter = 0;
					keyValue = i + 1 + 10;
				}
				break;
			}
			if (TkStatus == 0) {
				//release
				longPressCounter = 0;
			}
			mask <<= 1;
		}
		lastTkStatus = TkStatus;
	}
}
//---------------------------------
