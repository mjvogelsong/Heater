/*
	ReflowControl.cpp - Library (Source) for Reflow Oven Control.
	Michael Vogelsong
	Virginia Chen
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include <ReflowControl.h>
#include <LiquidCrystal.h>
#include <ButtonIO.h>
#include <PID_v1.h>

// alert compiler on external definitions
extern LiquidCrystal lcd;
extern ButtonIO btn;
extern PID myPID;
extern double currentTemp;
extern double pidOutput;
extern double setPoint;
extern int times[5];
extern int temps[5];
//extern int tempSamples[250];

// ********** Required in Sketch **********
// #include "LiquidCrystal.h"
// %% Global %%
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// ButtonIO btn(0);
// int times[5];
// int temps[5];

// %% Setup %%
// lcd.begin(16, 2);
// Serial.begin(9600);

// ********** Contructor **********
ReflowControl::ReflowControl()
{
	pinMode(READ_PIN, INPUT); // reading thermocouple
	pinMode(HEATER_PIN, OUTPUT); // controlling relay
	digitalWrite(HEATER_PIN, LOW); // start off for safety
	// Variable Initialization
	byte danger = 0; // used to signal dangerous temperatures (0, 1, or 2)
	// TODO: class enum DANGER (make error codes clearer)
	// char* stageNames[4] = {"Ramp", "Soak", "Ramp-to-Peak", "Cool"};
	// TODO: print stage names instead of stage numbers?
	long windowStartTime;
	long overallStartTime;
	long overallEndTime;
	long overallTimeLeft;
	int sampleIndex = 0;
	float maxTemp = 0;
}

// ********** Functions **********
// Runs the whole reflow heating process
void ReflowControl::main()
{
	waitForStart();
	prepare();
	initPID(); // initialize PID controller
	byte stageNumber = 1; // First stage: ramp
	printDisplay(); // prints template for displaying
	                // time, temp, and stage on the LCD
	while ( stageNumber < 5 ) // Last stage: cool (4)
	{
		stageNumber = operateStage(stageNumber);
	}
	finish();
}

// Waits until the user presses SELECT button to start the reflow
//  	oven heating
void ReflowControl::waitForStart()
{
	lcd.clear();
	lcd.home();
	lcd.print("Press SELECT");
	lcd.setCursor(0, 1);
	lcd.print("to prepare oven");
	lcd.home();
	waitForSelect();
}

void ReflowControl::prepare()
{
	lcd.clear();
	lcd.home();
	lcd.print("Preparing");
	lcd.setCursor(0, 1);
	lcd.print("Heating Element");
	digitalWrite(HEATER_PIN, HIGH);
	delay(PREPARE_TIME);
}

// Initializes the PID controller and calculates important
//  	time reference values (all in milliseconds)
void ReflowControl::initPID()
{
	// PID
	myPID.SetOutputLimits(0, WINDOW_SIZE); // set bounds on pidOutput
	myPID.SetSampleTime(WINDOW_SIZE); // don't need to calculate output
	                                  // until next window
	myPID.SetMode(AUTOMATIC); // turn on the PID
	// Time references
	windowStartTime = millis(); // dynamic - updated after each time window
	overallStartTime = millis();
	overallEndTime = overallStartTime + ( 1000 * (long)times[4] );
	overallTimeLeft = getTimeLeft(overallEndTime);
}

// Finds amount of time remaining between "now" and the end time point
//  	(in milliseconds)
//  	endTime: ending time reference (ms)
long ReflowControl::getTimeLeft( long endTime )
{
	return ( endTime - millis() );
}

// Finds amount of time since the starting time point (in milliseconds)
//  	startTime: starting reference (ms)
long ReflowControl::getTimeElapsed( long startTime )
{
	return ( millis() - startTime );
}

// Prints the template for displaying time remaining, current temp,
//  	and current stage
void ReflowControl::printDisplay()
{
	lcd.noBlink();
	lcd.clear();
	lcd.home();
	lcd.print("Time Rem (s):");
	lcd.setCursor(0, 1);
	lcd.print("Temp (C):     S");
	lcd.home();
}

// Controls the heater based on the current stage
//  	stageNumber: reflow curve stage number
//  		(1 - ramp-to-soak)
//  		(2 - soak)
//  		(3 - ramp-to-peak)
//  		(4 - cool)
byte ReflowControl::operateStage( byte stageNumber )
{
	displayInfo(stageNumber, 1, STAGE_COL, STAGE_ROW); // send current stage
	                                        // to the LCD
	// Stage-specific time and temp endpoints (milliseconds)
	long stageStartTime = overallStartTime + ( 1000 * (long)times[stageNumber-1] );
	int  stageStartTemp = temps[stageNumber-1];
	long stageEndTime = overallStartTime + ( 1000 * (long)times[stageNumber] );
	int  stageEndTemp = temps[stageNumber];
	long stageTimeLeft = getTimeLeft(stageEndTime); // time remaining in stage
	float rate = getSlope(stageStartTime, stageEndTime,
	                      stageStartTemp, stageEndTemp);
	                      // degrees / second
	int remainder = 1000;
	while ( stageTimeLeft > 0 ) // not done yet with this stage
	{
		// update current temp, set point, and overall time remaining
		updateInfo(rate, stageStartTime, stageStartTemp);
		// update PID control of relay
		updateHeater(rate, stageNumber, stageStartTime);
		// update LCD with current temp and time remaining
		displayInfo(toSeconds(overallTimeLeft), 3, TIME_COL, TIME_ROW);
		displayInfo(currentTemp, 3, TEMP_COL, TEMP_ROW);
		// take a sample point every second for statistical analysis
		// remainder = sampleTemp(remainder);
		// find out how much time is left in stage (ms)
		stageTimeLeft = getTimeLeft(stageEndTime);
		//Serial.print("Temp ");
		Serial.print(round(currentTemp));
		Serial.print(" ");
		//Serial.print(";  Set ");
		//Serial.print(setPoint);
		//Serial.print(";  Out ");
		//Serial.print(pidOutput);
		//Serial.print(";  Time ");
		Serial.println(getTimeElapsed(overallStartTime));
	}
	stageNumber++; // next stage
	return stageNumber;
}

// General function for updating data on LCD screen
//  	data: item to be displayed
//  	clearLength: maximum length of data item
//  	col, row: LCD locations
void ReflowControl::displayInfo( int data, byte clearLength, byte col, byte row )
{
	lcd.setCursor(col, row);
	btn.clearRegion(clearLength, col, row);
	lcd.print(data);
	lcd.setCursor(col, row);
}

// Gets the slope between two time/temp points
//  	inputs: stage endpoints
float ReflowControl::getSlope( long stageStartTime, long stageEndTime,
                               int stageStartTemp, int stageEndTemp )
{
	// slope = delta(temp) / delta(time)
	float slope = ((float)( stageEndTemp - stageStartTemp )) /
	        ((float)(( stageEndTime - stageStartTime ) / 1000));
	/*
	Serial.println(stageEndTemp);
	Serial.println(stageStartTemp);
	Serial.println(stageEndTime);
	Serial.println(stageStartTime);
	Serial.println(slope);
	*/
	return slope;
}

// Converts time from milliseconds to (rounded) seconds
//  	time: value in milliseconds
int ReflowControl::toSeconds( long time )
{
	return round( time / 1000 );
}

// Gets/updates the current temperature, interpolated set point,
//  	and overall time remaining
//  	rate: heating rate (deg/s)
//  	stageStartTime, stageStartTemp: starting point
void ReflowControl::updateInfo( float rate, long stageStartTime,
                                long stageStartTemp )
{
	maxTemp = updateCurrentTemp(maxTemp);
	/*
	Serial.print("In updateInfo: ");
	Serial.print(setPoint);
	Serial.print(" ");
	Serial.print(rate);
	Serial.print(" ");
	Serial.println(stageStartTime);
	*/
	updateSetPoint(rate, stageStartTime, stageStartTemp);
	overallTimeLeft = getTimeLeft(overallEndTime);
}

// Reads in the data from the thermocouple and converts it to
//  	temperature in degrees celsius
// TODO: get actual conversion
float ReflowControl::updateCurrentTemp( float maxTemp )
{
	int sensorValue = analogRead(READ_PIN);
	int voltage = map(sensorValue, 0, 1023, 0, 5000);
	int roomTempmV = map(ROOM_TEMP_ADC, 0, 1023, 0, 5000);
	currentTemp = (((double)(voltage - roomTempmV))/5) + 25;
	if ( currentTemp > maxTemp ) return currentTemp;
	else return maxTemp;
}

// Updates the set point based on interpolation between the stage's two
//  	endpoints.
// Linear Model: temp = slope * time + tempOffset
void ReflowControl::updateSetPoint( float rate, long stageStartTime,
                                   long stageStartTemp )
{
	setPoint = ( (double)rate * (double)( (millis() - stageStartTime)/1000 ) ) + (double)stageStartTemp;
	/*
	Serial.print("In updateSetPoint: ");
	Serial.println(setPoint);
	*/
}

// Runs the "slow PWM" technique of PID control for a relay.
//  	Since the relay cannot switch faster than 20 Hz, we expand
//  	the pidOutput to a desired window length. A larger output
//  	value is produced when the error is larger, and this will
//  	correspond to a greater portion of the time window being
//  	spent in the ON position
void ReflowControl::updateHeater( float rate, byte stageNumber,
                                  long stageStartTime)
{
	myPID.Compute(); // calculate an output based on error
	long now = millis();
	// Slide the time window over?
	if ( (now - windowStartTime) > WINDOW_SIZE ) windowStartTime += WINDOW_SIZE;
	// Relay ON for portion of window, OFF for remainder
	//if ( stageEndTime - now > APPROACH_TIME )
	//{
	if ( pidOutput > (now - windowStartTime) ) digitalWrite(HEATER_PIN, HIGH);
	else digitalWrite(HEATER_PIN, LOW);
	//}
	/*
	else
	{
		if ( stageNumber == 1 ) digitalWrite(HEATER_PIN, LOW);
		else if ( stageNumber == 2 ) digitalWrite(HEATER_PIN, HIGH);
		pause(5);
	}
	*/
}

/*
int ReflowControl::sampleTemp( int previousRemainder )
{
	long overallTimeElapsed = getTimeElapsed(overallStartTime);
	int thisRemainder = (int)(overallTimeElapsed % 1000);
	if ( thisRemainder < previousRemainder )
	{
		tempSamples[sampleIndex] = (int)currentTemp;
		sampleIndex++;
	}
	return thisRemainder;
}
*/

// not used yet
byte ReflowControl::checkLimits( float tempValue, int tempMin, int tempMax )
{
	if (tempValue >= tempMax) return TOO_HIGH;
	else if (tempValue <= tempMin) return TOO_LOW;
	else return 0; // temperature is within range
}

// not used yet
void ReflowControl::displayWarning( byte typeError ) // TODO: choose string to print
{	
	if (typeError == 1)	// current temp is greater than upper limit
	{			
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO HIGH!");
		lcd.setCursor(0,1);
		lcd.print("Turning off heat");
		digitalWrite(HEATER_PIN, LOW);
	}
	else // typeError == 2: current temp is less than lower limit
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO LOW!");
		lcd.setCursor(0,1);
		lcd.print("Turning on heat");
		digitalWrite(HEATER_PIN, HIGH);
	}
	for(int count = 0; count < 5; count++)
	{	// Blink off and on
		lcd.noDisplay();
		delay(BLINK_TIME);
		lcd.display();
		delay(BLINK_TIME);
	}
}

void ReflowControl::finish()
{
	digitalWrite(HEATER_PIN, LOW);
	lcd.clear();
	lcd.home();
	lcd.print("     DONE!");
	for(int count = 0; count < 5; count++)
	{	// Blink off and on
		lcd.noDisplay();
		delay(BLINK_TIME);
		lcd.display();
		delay(BLINK_TIME);
	}
	lcd.clear();
	lcd.home();
	lcd.print("Set Peak (C):");
	lcd.print(temps[3]);
	lcd.setCursor(0, 1);
	lcd.print("Act Peak (C):");
	lcd.print(round(maxTemp));
	waitForSelect();
}

void ReflowControl::waitForSelect()
{
	boolean selected = false;
	while ( !selected )
	{
		selected = btn.waitForButton();
	}
}