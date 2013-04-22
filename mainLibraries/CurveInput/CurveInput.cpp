/*
	CurveInput.cpp - Library (Source): allows user to input reflow curve
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include "CurveInput.h"
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
CurveInput::CurveInput()
{
	
}

// ********** Functions **********
