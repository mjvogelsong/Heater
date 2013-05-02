/*
	CurveInput.cpp - Library (Source): allows user to input reflow curve
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include <CurveInput.h>
#include <LiquidCrystal.h>
#include <ButtonIO.h>

// alert compiler on external definitions
extern LiquidCrystal lcd;
extern ButtonIO btn;
extern int times[5];
extern int temps[5];

// ********** Required in Sketch **********
// #include "LiquidCrystal.h"
// %% Global %%
// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// ButtonIO btn(0);

// %% Setup %%
// lcd.begin(16, 2);
// Serial.begin(9600);

// ********** Contructor **********
CurveInput::CurveInput()
{
	byte col;
	byte row;
}

// ********** Functions **********
void CurveInput::main()
{
	boolean choice = chooseCurve();
	loadCurve(choice);
	sendTimesAndTemps();
}

// Allows the user to choose whether they want to use
//		a default heating curve or define their own curve
// Returns the user's choice
boolean CurveInput::chooseCurve()
{
	printWelcome(WELCOME_DURATION);
	printCurveChoices();
	lcd.blink(); // show cursor
	byte buttonID = NONE;
	while ( buttonID != SELECT ) // any button other than SELECT
	{
		buttonID = btn.waitForButton();
		btn.actionNavigate(buttonID, CURVE_CHOICE_DURATION,
						   &col, &row, 0, 0, 0, 1); // up/down choice
								// between default (A) and user
								// defined curve (B)
	}
	lcd.noBlink();
	return row; // Choice will either be top (Defaut)
		// or bottom row (User-Defined)
}

// Prints welcome screen on LCD
//  	duration: time spent on welcome screen
void CurveInput::printWelcome( int duration )
{
	initLCD(&col, &row);
	lcd.print("Welcome to");
	lcd.setCursor(0, 1);
	lcd.print("Reflow Control!");
	delay(duration);
}

// Prints curve choices on the LCD screen
void CurveInput::printCurveChoices()
{
	initLCD(&col, &row);
	lcd.print("A: Default Curve");
	lcd.setCursor(0, 1);
	lcd.print("B: User Curve");
	lcd.setCursor(0, 0);
}

// Simple clearing of LCD screen while simultaneously
//  	updating the col and row trackers
//  	col, row: pointers to locations on LCD
void CurveInput::initLCD( byte* col, byte* row )
{
	lcd.clear();
	*col = 0; *row = 0;
	lcd.setCursor(*col, *row);
}

// Master function for obtaining the information needed
//  	to define the reflow curve
//  	choice: 0 - default
//  	        1 - user-defined
void CurveInput::loadCurve( boolean choice )
{
	if ( !choice ) // Default
	{
		loadDefault(); // get the default times and temps
		initLCD(&col, &row);
		//lcd.print("Loaded Default");
	}
	else
	{
		loadUserCurve(); // get the user's times and temps
		initLCD(&col, &row);
		//lcd.print("Loaded User");
	}
}

// Loads the times and temps arrays with the default curve data
void CurveInput::loadDefault()
{
	temps[0] = 25; // assume starting at room temperature
	temps[1] = 150; // end ramp-to-soak, begin soak
	temps[2] = 150; // end soak, begin ramp-to-peak
	temps[3] = 245; // peak, begin cooling
	temps[4] = 200; // cooled
	
	times[0] = 0;
	times[1] = getTime(1, 1); // 1-3 deg/s
	times[2] = times[1] + 120; // soak duration: 90 s
	times[3] = getTime(3, 1); // 1-3 deg/s
	times[4] = getTime(4, -2); // -6 deg/s
}

// Calculates next time point based on the temperature change
//      and the desired rate of heating (+) / cooling (-)
// Simple y = mx + b model
//  	current: index for current time point
//  	rate: degrees C / second
int CurveInput::getTime( int current, float rate )
{
	return times[current-1] + round((temps[current] - temps[current-1]) / rate);
}

// Gets the time and temp information from the user, and
//  	loads it into the arrays
void CurveInput::loadUserCurve()
{
	printAssumption(); // assume time[0] = 25
	loadDefault(); // this will set the starting values for when the
	               // user inputs the times and temps
	getCurvePoints();
}

// Tells user that we are assuming room temperature start
void CurveInput::printAssumption()
{
	initLCD(&col, &row);
	lcd.print("Assuming");
	lcd.setCursor(0, 1);
	lcd.print("temp[0] = 25 C");
	delay(ASSUME_DURATION);
}

// Prompts the user to input times and temps
void CurveInput::getCurvePoints()
{
	for ( int i = 1; i < 5; i++ ) // need 4 points
	{
		times[i] = getTimePoint(i);
		temps[i] = getTempPoint(i);
	}
	delay(SELECT_DURATION);
}

// Allows user to change and select the time point
//  	index: index of the current time point
int CurveInput::getTimePoint( int index )
{
	initLCD(&col, &row);
	lcd.print("Enter Time ");
	lcd.print(index);
	lcd.print(" (s)");
	lcd.setCursor(0, 1);
	byte buttonID = NONE;
	int lowerLimit, upperLimit;
	times[index] = getTimeLimits(index, &lowerLimit, &upperLimit);
	int thisTime = times[index]; // scoping current time
	lcd.print(thisTime);
	col = 0; row = 1;
	lcd.setCursor(col, row);
	delay(SELECT_DURATION);
	while ( buttonID != SELECT ) // any button other than SELECT
	{
		buttonID = btn.waitForButton();
		thisTime = btn.actionIncDec(buttonID, TIME_TEMP_DURATION,
		                            col, row, thisTime, 3,
		                            lowerLimit, upperLimit);
		                            // user adjusts time
	}
	return thisTime;
}

int CurveInput::getTimeLimits( int index, int* lowerLimit,
                               int* upperLimit )
{
	*lowerLimit = times[index-1] + 1;
	*upperLimit = *lowerLimit + TIME_RANGE;
	int suggestedTime = *lowerLimit + (int)(.75*TIME_RANGE);
	//Serial.println(suggestedTime);
	return suggestedTime;
}

// Allows user to change and select the temperature point
//  	index: index of the current temperature point
int CurveInput::getTempPoint( int index )
{
	initLCD(&col, &row);
	lcd.print("Enter Temp ");
	lcd.print(index);
	lcd.print(" (C)");
	lcd.setCursor(0, 1);
	byte buttonID = NONE;
	int lowerLimit, upperLimit;
	temps[index] = getTempLimits(index, &lowerLimit, &upperLimit);
	int thisTemp = temps[index]; // scoping
	lcd.print(thisTemp);
	col = 0; row = 1;
	lcd.setCursor(col, row);
	delay(SELECT_DURATION);
	while ( buttonID != SELECT ) // any button other than SELECT
	{
		buttonID = btn.waitForButton();
		thisTemp = btn.actionIncDec(buttonID, TIME_TEMP_DURATION,
		                            col, row, thisTemp, 3,
									lowerLimit, upperLimit);
		                            // user adjusts temperature
	}
	return thisTemp;
}

int CurveInput::getTempLimits( int index, int* lowerLimit,
                               int* upperLimit )
{
	float minRate, maxRate, suggestRate;
	if ((index == 1) || (index == 3))
	{
		minRate = .75; maxRate = 3.25; suggestRate = 1;
	}
	else if ( index == 2 )
	{
		minRate == -.5; maxRate = .5; suggestRate = 0;
	}
	else
	{
		minRate = -6; maxRate = -1; suggestRate = -2;
	}
	*lowerLimit = projectTemp(times[index-1], times[index],
                              temps[index-1], minRate);
	*upperLimit = projectTemp(times[index-1], times[index],
                              temps[index-1], maxRate);
	int suggestedTemp = projectTemp(times[index-1], times[index],
                                    temps[index-1], suggestRate);
	/*
	Serial.println(index);
	Serial.println(minRate);
	Serial.println(maxRate);
	Serial.println(suggestRate);
	Serial.println(*lowerLimit);
	Serial.println(*upperLimit);
	Serial.println(suggestedTemp);
	*/
	return suggestedTemp;
}

int CurveInput::projectTemp( int previousTime, int currentTime,
	                         int previousTemp, float rate )
{
	int temp = previousTemp + round(((float)( currentTime - previousTime ))*rate);
	if ( temp > MAX_TEMP ) temp = MAX_TEMP;
	else if ( temp < MIN_TEMP ) temp = MIN_TEMP;
	return temp;
}

void CurveInput::sendTimesAndTemps()
{
	Serial.println("Times");
	for ( int i = 0; i < 5; i++ )
	{
		Serial.println(times[i]);
	}
	Serial.println("Temps");
	for ( int i = 0; i < 5; i++ )
	{
		Serial.println(temps[i]);
	}
}