/*
	CurveInput.h - Library (Header): allows user to input reflow curve.
	Michael Vogelsong
*/

#ifndef CurveInput_h
#define CurveInput_h

#include "Arduino.h"

// ********** Constants **********
#define WELCOME_DURATION 2000
#define CURVE_CHOICE_DURATION 250
#define ASSUME_DURATION 2000
#define SELECT_DURATION 500
#define TIME_TEMP_DURATION 80

class CurveInput
{
	public:
		// Functions
		CurveInput();
		void main();
		boolean chooseCurve();
		// Variables
	private:
		// Functions
		void printCurveChoices();
		void printWelcome( int duration );
		void initLCD( byte* col, byte* row );
		void loadCurve( boolean choice );
		void loadDefault();
		int getTime( int current, float rate );
		void loadUserCurve();
		void printAssumption();
		void getCurvePoints();
		int getTimePoint( int index );
		int getTempPoint( int index );
		int getTimeLimits( int index, int* lowerLimit,
		                   int* upperLimit );
		// Variables
		byte col;
		byte row;
};

#endif