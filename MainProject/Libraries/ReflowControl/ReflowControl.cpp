/*
	ReflowControl.cpp - Library (Source) for Reflow Oven Control.
	Michael Vogelsong
	Virginia Chen
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include <ReflowControl.h>
#include <LiquidCrystal.h>
#include <ButtonIO.h>
#include <PID_v1.h>

// alert compiler on external definitions
extern LiquidCrystal lcd;
extern ButtonIO btn;
extern PID myPID;
extern double currentTemp;
extern double pidOutput;
extern double setPoint;
extern int times[5];
extern int temps[5];

// ********** Required in Sketch **********
// #include "LiquidCrystal.h"
// %% Global %%
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// ButtonIO btn(0);
// int times[5];
// int temps[5];

// %% Setup %%
// lcd.begin(16, 2);
// Serial.begin(9600);

// ********** Contructor **********
ReflowControl::ReflowControl()
{
	pinMode(READ_PIN, INPUT);
	pinMode(HEATER_PIN, OUTPUT);
	digitalWrite(HEATER_PIN, LOW);
	// Variable Initialization
	byte danger = 0; // used to signal dangerous temperatures (0, 1, or 2)
	                 // TODO: class enum DANGER (make error codes clearer)
	// char* stageNames[4] = {"Ramp", "Soak", "Ramp-to-Peak", "Cool"};
	// TODO: print stage names instead of stage numbers?
}

// ********** Functions **********
void ReflowControl::main()
{
	initPID();
	byte stageNumber = 1;
	printDisplay();
	while ( stageNumber < 5 )
	{
		stageNumber = operateStage(stageNumber);
	}
}

void ReflowControl::initPID()
{
	// PID
	myPID.SetOutputLimits(0, WINDOW_SIZE);
	myPID.SetMode(AUTOMATIC);
	// time references
	long windowStartTime = millis();
	long overallStartTime = millis();
	long overallEndTime = overallStartTime + ( 1000 * times[4] );
	long overallTimeLeft = getTimeLeft(overallEndTime);
}

long ReflowControl::getTimeLeft( long endTime )
{
	return ( endTime - millis() );
}

long ReflowControl::getTimeElapsed( long startTime )
{
	return ( millis() - startTime );
}

void ReflowControl::printDisplay()
{
	lcd.noBlink();
	lcd.clear();
	lcd.home();
	lcd.print("S");
	lcd.setCursor(0, 1);
	lcd.print("Temp:");
	lcd.home();
}

byte ReflowControl::operateStage( byte stageNumber )
{
	displayInfo(stageNumber, 1, STAGE_COL, STAGE_ROW);
	long stageStartTime = overallStartTime + ( 1000 * times[stageNumber-1] );
	int  stageStartTemp = temps[stageNumber-1];
	long stageEndTime = overallStartTime + ( 1000 * times[stageNumber] );
	int  stageEndTemp = temps[stageNumber];
	long stageTimeLeft = getTimeLeft(stageEndTime);
	float rate = getSlope(stageStartTime, stageEndTime,
	                      stageStartTemp, stageEndTemp);
	while ( stageTimeLeft < 0 )
	{
		updateInfo(rate, stageStartTime, stageStartTemp);
		updateHeater(rate, stageStartTime);
		displayInfo(toSeconds(overallTimeLeft), 3, TIME_COL, TIME_ROW);
		displayInfo(currentTemp, 3, TEMP_COL, TEMP_ROW);
		stageTimeLeft = getTimeLeft(stageEndTime);
	}
	stageNumber++;
	return stageNumber;
}

void ReflowControl::displayInfo( int data, byte clearLength, byte col, byte row )
{
	lcd.setCursor(col, row);
	btn.clearRegion(clearLength, col, row);
	lcd.print(data);
	lcd.setCursor(col, row);
}

float ReflowControl::getSlope( long stageStartTime, long stageEndTime,
                               int stageStartTemp, int stageEndTemp )
{
	float slope = ( stageEndTemp - stageStartTemp ) /
	        ( stageEndTime - stageStartTime );
	return slope;
}

int ReflowControl::toSeconds( long time )
{
	return round( time / 1000 );
}

void ReflowControl::updateInfo( float rate, long stageStartTime,
                                long stageStartTemp )
{
	updateCurrentTemp();
	updateSetPoint(rate, stageStartTime, stageStartTemp);
	overallTimeLeft = getTimeLeft(overallEndTime);
}

float ReflowControl::updateCurrentTemp()
{
	int sensorValue = analogRead(READ_PIN);
	return map(sensorValue, 0, 1023, RANGE_LOW, RANGE_HIGH);
}

void ReflowControl::updateSetPoint( float rate, long stageStartTime,
                                   long stageStartTemp )
{
	setPoint = ( rate * ( millis() - stageStartTime ) ) + stageStartTemp;
}

void ReflowControl::updateHeater( float rate, long stageStartTime)
{
	myPID.Compute();
	long now = millis();
	if ( (now - windowStartTime) > WINDOW_SIZE ) windowStartTime += WINDOW_SIZE;
	if ( pidOutput > (now - windowStartTime) ) digitalWrite(HEATER_PIN, HIGH);
	else digitalWrite(HEATER_PIN, LOW);
}

byte ReflowControl::checkLimits( float tempValue, int tempMin, int tempMax )
{
	if (tempValue >= tempMax) return TOO_HIGH;
	else if (tempValue <= tempMin) return TOO_LOW;
	else return 0; // temperature is within range
}

void ReflowControl::displayWarning( byte typeError ) // TODO: choose string to print
{	
	if (typeError == 1)	// current temp is greater than upper limit
	{			
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO HIGH!");
		lcd.setCursor(0,1);
		lcd.print("Turning off heat");
		digitalWrite(HEATER_PIN, LOW);
	}
	else // typeError == 2: current temp is less than lower limit
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO LOW!");
		lcd.setCursor(0,1);
		lcd.print("Turning on heat");
		digitalWrite(HEATER_PIN, HIGH);
	}
	for(int count = 0; count < 5; count++)
	{	// Blink off and on
		lcd.noDisplay();
		delay(BLINK_TIME);
		lcd.display();
		delay(BLINK_TIME);
	}
}