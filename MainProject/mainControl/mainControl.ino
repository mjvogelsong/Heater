/*
********************************
mainControl.ino
********************************
Michael Vogelsong
4/14/13

Functions:

********************************
*/
// ~~~~~~~~~~~~~~~~ Libraries ~~~~~~~~~~~~~~~~
#include <LiquidCrystal.h>
#include <ButtonIO.h>
#include <CurveInput.h>

// ~~~~~~~~~~~~~~~~ Debugging ~~~~~~~~~~~~~~~~~
#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

// ~~~~~~~~~~~~~~~ Global Initialization ~~~~~~~~~~~~~~~~~
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ButtonIO btn(0);
CurveInput curvIn;
int times[5]; // will hold time points to define the stages
int temps[5]; // will hold temperature points

// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~
void setup()
{
  
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~
void loop()
{
	// TODO: improve
	curvIn.main()
	// TODO: implement
	controlHeater();
	{
		while ((stageCounter <= maxStage) && !error)
		{
			calculateStageInfo();
			while (secondCounter <= maxSeconds)
			{
				loopBegin = millis();
				getCurrentStats();
				printCurrentStats();
				getModelTemp();
				controlHeater();
				checkUnsafe();
				secondCounter = secondCounter + 1;
				delay(1000 - (millis() - loopBegin));
			}
			stageCounter = stageCounter + 1;
			checkError();
		}
	}
	endReport()
	{
		if (error)
		{
			printError();
		}
		else
		{
			printDone();
			printSimpleResults();
			if (askExportStats())
			{
				exportStats();
			}
		}
	}
	finish();
}
