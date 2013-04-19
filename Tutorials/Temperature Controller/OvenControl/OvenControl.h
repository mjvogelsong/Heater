/*
	OvenControl.h - Library (Header) for Reflow Oven Control.
	Michael Vogelsong
*/

#ifndef OvenControl_h
#define OvenControl_h

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
#define DEFAULT_SET_TEMP 100
#define UPPER_LIM 300
#define LOWER_LIM 0

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

class OvenControl
{
	
	public:
		OvenControl();
		void inputSetPoint();
		float volt2Temp( byte readPin );
		byte checkLimits( float tempValue, int tempMin, int tempMax );
		void updateHeater( float current, byte setPoint, byte heaterPin );
		void displayTemp( float currentTemp, int setPoint );
		void displayWarning( byte typeError );
		
		// ********** Variable Initialization **********
		byte setPoint; // Dynamic setPoint
		int adcKeyIn; // ADC value of input button
		float currentTemp; // dynamic current temperature
		byte danger; // used to signal dangerous temperatures
		
	private:
		void startingScreen();
		void adjustAndSelect( byte startVal, byte col, byte row );
		byte readLcdKeys();
		boolean buttonTempAction( byte LCD_key, byte col, byte row,
		                          byte clearLength );
		void clearRegion( byte clearLength, byte row, byte col );
};

#endif