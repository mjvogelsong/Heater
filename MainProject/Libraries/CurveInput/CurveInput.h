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
#define ASSUME_DURATION 1000

class CurveInput
{
	public:
		CurveInput();
		boolean chooseCurve();
		int times[10];
		int temps[10];
	private:
		void printCurveChoices();
		void printWelcome( int duration );
		byte col;
		byte row;
};

#endif