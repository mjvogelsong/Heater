/*
	ButtonIO.cpp - Library (Source): Button Input/Output
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include "ButtonIO.h"
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
ButtonIO::ButtonIO( byte buttonPin )
{
	byte BUTTON_PIN = buttonPin;
	byte currentButton;
	int adcKeyIn;
	pinMode(BUTTON_PIN, INPUT);
}

// ********** Functions **********
byte ButtonIO::waitForButton()
{
	adcKeyIn = 1023; // ADC corresponding to no buttons pushed
	currentButton = NONE;
	while ( currentButton == NONE )
	{
		while ( currentButton == NONE )
		{
			currentButton = readLcdKeys();
		}
		delay(5); // debounce
		currentButton = readLcdKeys();	// make sure the button is
										// still pressed
	}
	return currentButton;
}

byte ButtonIO::readLcdKeys()
{
	adcKeyIn = analogRead(BUTTON_PIN); // read the value from the sensor
		// centered at these values: 0, 98, 255, 409, 639
		// we add approx 50 to those values
		// and check to see if we are close
	if (adcKeyIn > VNONE) return NONE; // speed reasons
	if (adcKeyIn < V1) return RIGHT;
	if (adcKeyIn < V2) return UP;
	if (adcKeyIn < V3) return DOWN;
	if (adcKeyIn < V4) return LEFT;
	if (adcKeyIn < V5) return SELECT;
	return NONE; // when all others fail, return this...
}

void ButtonIO::actionNavigate( byte button, byte* col, byte* row,
							 byte left, byte right,
							 byte top, byte bottom )
{
	switch ( button ) 	// depending on which button was pushed
	{
		case UP:
		{
			if ( *row == top ) *row = bottom;
			else *row = top;
			break;
		}
		case DOWN:
		{
			if ( *row == bottom ) *row = top;
			else *row = bottom;
			break;
		}
		case LEFT:
		{
			if ( *col == left ) *col = right;
			else (*col)--;
			break;
		}
		case RIGHT:
		{
			if ( *col == right ) *col = left;
			else (*col)++;
			break;
		}
	}
	lcd.setCursor(*col, *row);
}

int ButtonIO::actionIncDec( byte button, byte col, byte row,
							int value, int maxDigits,
							int upperLim, int lowerLim )
{
	switch ( button ) 	// depending on which button was pushed
	{
		case UP:
		{
			if ( value == upperLim ) value = lowerLim;
			else value++;
			break;
		}
		case DOWN:
		{
			if ( value == lowerLim ) value = upperLim;
			else value--;
			break;
		}
	}
	clearRegion(maxDigits, col, row);
	lcd.print(value);
	return value;
}

void ButtonIO::clearRegion( byte clearLength, byte col, byte row )
{
	lcd.setCursor(col, row);
	for ( int i = 0; i < (clearLength); i++)
	{
		lcd.print(" ");
	}
	lcd.setCursor(col, row);
}