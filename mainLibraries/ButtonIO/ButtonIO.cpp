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
	const BUTTON_PIN = buttonPin;
}

// ********** Functions **********
byte ButtonIO::readLcdKeys()
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