/*
	CurveInput.h - Library (Header): allows user to input reflow curve.
	Michael Vogelsong
*/

#ifndef CurveInput_h
#define CurveInput_h

#include "Arduino.h"

// ********** Constants **********
// Buttons
#define btnRIGHT   0
#define btnUP      1
#define btnDOWN    2
#define btnLEFT    3
#define btnSELECT  4
#define btnNONE    5

// Button ADC Limits
#define V1         50
#define V2         148
#define V3         305
#define V4         459
#define V5         689
#define VNONE      1000

// Temperatures
#define UPPER_LIM 300
#define LOWER_LIM 0
#define RANGE_LOW 20
#define RANGE_HIGH 305

// Timing
#define SELECT_DELAY 100
#define CHECK_TIME   500
#define BLINK_TIME   200

// Errors
#define TOO_HIGH 1
#define TOO_LOW	2

// Pins
#define BUTTON_PIN   0
#define READ_PIN  1
#define HEATER_PIN  13

class CurveInput
{
	public:
		CurveInput();

	private:
		
};

#endif