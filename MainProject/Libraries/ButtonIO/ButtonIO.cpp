/*
	ButtonIO.cpp - Library (Source): Button Input/Output
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include "ButtonIO.h"

// ********** Required in Sketch **********
// NONE

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