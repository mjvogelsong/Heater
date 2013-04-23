/*
	ButtonIO.h - Library (Header): Button Input/Output
	Michael Vogelsong
*/

#ifndef ButtonIO_h
#define ButtonIO_h

#include "Arduino.h"

// Buttons
#define RIGHT   0
#define UP      1
#define DOWN    2
#define LEFT    3
#define SELECT  4
#define NONE    5

// Button ADC Limits
#define V1         50
#define V2         148
#define V3         305
#define V4         459
#define V5         689
#define VNONE      1000

class ButtonIO
{
	public:
		// Functions
		ButtonIO( byte buttonPin );
		byte waitForButton();
		// Variables
		byte currentButton;
	private:
		// Functions
		byte readLcdKeys();
		// Variables
		int adcKeyIn;
		byte BUTTON_PIN;
};

#endif