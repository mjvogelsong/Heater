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
	byte currentButton; 		// init
	int adcKeyIn; 				// init
	pinMode(BUTTON_PIN, INPUT); // prepare button input pin
}

// ********** Functions **********

// Waits for button to be pushed
// Returns with the button ID
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

// Helper function reads the ADC value and converts it to the
// 		button ID
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

// General purpose navigation of the LCD screen:
// Params:
// 		button: button ID
//		duration: how long to delay (prevents too-fast movement)
//		col, row: LCD locations (use pointers to access/change)
//		left, right, top, bottom: sets boxed limit on where the cursor
//			can move
// **Note** the generality adds params, but it also makes it easier to reuse
//		for different input strategies
void ButtonIO::actionNavigate( byte button, int duration,
							 byte* col, byte* row,
							 byte left, byte right,
							 byte top, byte bottom )
{
	switch ( button )
	{
		case UP:
		{
			if ( *row == top ) *row = bottom; 	// only need to move
			else *row = top; 					// between top and bottom
			break;								// row
		}
		case DOWN:
		{
			if ( *row == bottom ) *row = top;	// opposite of case UP
			else *row = bottom;
			break;
		}
		case LEFT:
		{
			if ( *col == left ) *col = right;	// wrap back to right edge
			else (*col)--;						// move 1 left
			break;
		}
		case RIGHT:
		{
			if ( *col == right ) *col = left;	// wrap back to left edge
			else (*col)++;						// move 1 right
			break;
		}
	}
	lcd.setCursor(*col, *row);	// new location of cursor
	delay(duration);		// prevent quick movement
}

// General purpose increment/decrement:
// Params:
// 		button: button ID
//		duration: how long to delay (prevents too-fast movement)
//		col, row: LCD locations (no changes => no pointers needed)
//		value: value to be changed
//		maxDigits: how big the value can be (digits wide)
//		upperLim, lowerLim: limits on range of values
int ButtonIO::actionIncDec( byte button, int duration,
							byte col, byte row,
							int value, int maxDigits,
							int upperLim, int lowerLim )
{
	switch ( button ) 	// depending on which button was pushed
	{
		case UP:
		{
			if ( value == upperLim ) value = lowerLim; // reached upper limit
			else value++;
			break;
		}
		case DOWN:
		{
			if ( value == lowerLim ) value = upperLim; // reached lower limit
			else value--;
			break;
		}
	}
	clearRegion(maxDigits, col, row); // clear number space on LCD
	lcd.print(value);
	delay(duration);
	return value;	// still need the value (in addition to changing 
					// 		the LCD display)
}

// Helper function clears a specified string of digits
void ButtonIO::clearRegion( byte clearLength, byte col, byte row )
{
	lcd.setCursor(col, row);
	for ( int i = 0; i < (clearLength); i++)
	{
		lcd.print(" "); // single element clear
	}
	lcd.setCursor(col, row); // return to original cursor location
}