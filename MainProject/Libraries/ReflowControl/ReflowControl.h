/*
	ReflowControl.h - Library (Header) for Reflow Oven Control.
	Michael Vogelsong
	Virginia Chen
*/

#ifndef ReflowControl_h
#define ReflowControl_h

#include "Arduino.h"
#include <PID_v1.h>

// ********** Constants **********
// Temperatures
#define UPPER_LIM 300
#define LOWER_LIM 0
#define RANGE_LOW 20
#define RANGE_HIGH 305

// Timing
#define BLINK_TIME   200

// Errors
#define TOO_HIGH 1
#define TOO_LOW	2

// Pins
#define READ_PIN  5
#define HEATER_PIN  2

// PID Tuning
#define KP 5
#define KI 2
#define KD 0.1
#define WINDOW_SIZE 500

#define TIME_COL 0
#define TIME_ROW 0
#define TEMP_COL 7
#define TEMP_ROW 1
#define STAGE_COL 15
#define STAGE_ROW 0

class ReflowControl
{
	public:
		// Functions
		ReflowControl();
		void main();
		
		// Variables
		byte danger; // used to signal dangerous temperatures
		
	private:
		// Functions
		void initPID();
		long getTimeLeft( long endTime );
		long getTimeElapsed( long startTime );
		void printDisplay();
		byte operateStage( byte stageNumber );
		void displayInfo( int data, byte clearLength,
		                  byte col, byte row );
		float getSlope( long stageStartTime, long stageEndTime,
                        int stageStartTemp, int stageEndTemp );
		int toSeconds( long time );
		void updateInfo( float rate, long stageStartTime,
		                 long stageStartTemp );
		float updateCurrentTemp();
		void updateSetPoint( float rate, long stageStartTime,
                             long stageStartTemp );
		void updateHeater( float rate, long stageStartTime);
		byte checkLimits( float tempValue, int tempMin, int tempMax );
		void displayWarning( byte typeError );
		// Variables
		byte stageNumber;
		long windowStartTime;
		long overallStartTime;
		long overallEndTime;
		long overallTimeLeft;
};

#endif