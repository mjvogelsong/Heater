/*
	OvenControl.cpp - Library (Source) for Reflow Oven Control.
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include "OvenControl.h"
#include <LiquidCrystal.h>

// alert compiler that lcd will be defined in sketch
extern LiquidCrystal lcd;

// ********** Required in Sketch **********
// #include "LiquidCrystal.h"
// %% Global %%
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// %% Setup %%
// lcd.begin(16, 2);
// Serial.begin(9600);

// ********** Contructor **********
OvenControl::OvenControl()
{
	pinMode(BUTTON_PIN, INPUT);
	pinMode(READ_PIN, INPUT);
	pinMode(HEATER_PIN, OUTPUT);
	digitalWrite(HEATER_PIN, LOW);

	// ********** Variable Initialization **********
	byte setPoint = DEFAULT_SET_TEMP; // Dynamic set point
	int adcKeyIn; // ADC value of input button (0 to 1023)
	float currentTemp; // dynamic current temperature
	byte danger = 0; // used to signal dangerous temperatures (0, 1, or 2)
}

// ********** Functions **********
void OvenControl::inputSetPoint()
{
	setPoint = DEFAULT_SET_TEMP;
	startingScreen();
	adjustAndSelect(DEFAULT_SET_TEMP, 0, 1);
}

void OvenControl::startingScreen()
{
	lcd.clear();
	lcd.home();
	lcd.print("Set Temp (C)?");
	lcd.setCursor(0, 1);
	lcd.print(DEFAULT_SET_TEMP);
}

// read the ADC voltage to determine which button was pressed
byte OvenControl::readLcdKeys()
{
	adcKeyIn = analogRead(BUTTON_PIN); // read the value from the sensor
		// centered at these values: 0, 98, 255, 409, 639
		// we add approx 50 to those values
		// and check to see if we are close
	if (adcKeyIn > VNONE) return btnNONE; // speed reasons
	if (adcKeyIn < V1) return btnRIGHT;
	if (adcKeyIn < V2) return btnUP;
	if (adcKeyIn < V3) return btnDOWN;
	if (adcKeyIn < V4) return btnLEFT;
	if (adcKeyIn < V5) return btnSELECT;
	return btnNONE; // when all others fail, return this...
}

void OvenControl::adjustAndSelect( byte startVal, byte col, byte row )
{
	boolean _selected = false;
	byte _lcdKey;
	while ( _selected == false )
	{
		_lcdKey = readLcdKeys();
		if ( _lcdKey != btnNONE )
		{
			_selected = buttonTempAction(_lcdKey, col, row, 3);
			delay(SELECT_DELAY);
		}
	}
}

void OvenControl::clearRegion( byte clearLength, byte col, byte row )
{
	lcd.setCursor(col, row);
	for ( int i = 0; i < (clearLength); i++)
	{
		lcd.print(" ");
	}
	lcd.setCursor(col, row);
}

// Pressing up increases the set temperature by 1.
// Pressing down decreases it by 1.
// Press select when you are done.
// Other buttons: do nothing
boolean OvenControl::buttonTempAction( byte lcdKey, byte col,
									   byte row, byte clearLength )
{
	boolean _select = false;
	clearRegion(clearLength, col, row);
	switch ( lcdKey ) 	// depending on which button was pushed,
						// we perform an action
	{
		case btnUP:
		{
			setPoint++;
			break;
		}
		case btnDOWN:
		{
			setPoint--;
			break;
		}
		case btnSELECT:
		{
			_select = true;
			break;
		}
	}
	lcd.print(setPoint);
	lcd.setCursor(col, row); 
	return _select ; 
}

float OvenControl::volt2Temp( byte readPin ) // TODO: figure out thermocouple conversion
{
	int sensorValue = analogRead(readPin);
	return map(sensorValue, 0, 1023, RANGE_LOW, RANGE_HIGH); // convert analog readings to temperature
}

byte OvenControl::checkLimits( float tempValue, int tempMin, int tempMax )
{
	if (tempValue >= tempMax) return 1;	// too high
	else if (tempValue <= tempMin) return 2; // too low
	else return 0; // temperature is within range
}

void OvenControl::updateHeater( float current, byte setPoint, byte heaterPin )
{
	digitalWrite(heaterPin, ( setPoint > current ) );
}

void OvenControl::displayTemp(float currentTemp, int setPoint)
{
	lcd.clear();
	lcd.setCursor(0,0);
	int displayCurrentTemp = round(currentTemp);
	lcd.print("Current:");
	lcd.print(displayCurrentTemp);
	lcd.setCursor(0,1);
	lcd.print("SetPoint:");
	lcd.print(setPoint);
}

void OvenControl::displayWarning( byte typeError ) // TODO: choose string to print
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