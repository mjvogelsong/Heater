/*
	CurveInput.cpp - Library (Source): allows user to input reflow curve
	Michael Vogelsong
*/

// ********** Library Dependencies **********
#include "Arduino.h"
#include "CurveInput.h"
#include <LiquidCrystal.h>
#include <ButtonIO.h>

// alert compiler
extern LiquidCrystal lcd;
extern ButtonIO btn;

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
	int times[5];
	int temps[5];
}

// ********** Functions **********
void CurveInput::main()
{
	boolean choice = chooseCurve();
	loadCurve(choice);
}

void CurveInput::initLCD( byte* col, byte* row )
{
	lcd.clear();
	*col = 0; *row = 0;
	lcd.setCursor(*col, *row);
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

void CurveInput::loadCurve( boolean choice )
{
	if ( !choice ) 
	{
		loadDefault();
		initLCD(&col, &row);
		lcd.print("Loaded Default");
	}
	else
	{
		loadUserCurve();
		initLCD(&col, &row);
		lcd.print("Loaded User");
	}
	
}

void CurveInput::loadDefault()
{
	temps[0] = 25;
	temps[1] = 150;
	temps[2] = 150;
	temps[3] = 245;
	temps[4] = 200;
	
	times[0] = 0;
	times[1] = getTime(1, 2);
	times[2] = times[1] + 90;
	times[3] = getTime(3, 2);
	times[4] = getTime(4, -6);
}

int CurveInput::getTime( int current, float rate )
{
	return times[current-1] + round((temps[current] - temps[current-1]) / rate);
}

void CurveInput::loadUserCurve()
{
	printAssumption();
	loadDefault();
	getCurvePoints();
}

void CurveInput::printAssumption()
{
	initLCD(&col, &row);
	lcd.print("Assuming");
	lcd.setCursor(0, 1);
	lcd.print("temp[0] = 25 C");
	delay(ASSUME_DURATION);
}

void CurveInput::getCurvePoints()
{
	for ( int i = 1; i < 5; i++ )
	{
		times[i] = getTimePoint(i);
		temps[i] = getTempPoint(i);
	}
	delay(SELECT_DURATION);
}

int CurveInput::getTimePoint( int index )
{
	initLCD(&col, &row);
	lcd.print("Enter Time ");
	lcd.print(index);
	lcd.print(":");
	lcd.setCursor(0, 1);
	byte buttonID = NONE;
	int thisTime = times[index];
	lcd.print(thisTime);
	col = 0; row = 1;
	lcd.setCursor(col, row);
	delay(SELECT_DURATION);
	while ( buttonID != SELECT ) // any button other than SELECT
	{
		buttonID = btn.waitForButton();
		thisTime = btn.actionIncDec(buttonID, TIME_TEMP_DURATION,
		                            col, row, thisTime, 3, 0, 300);
		                            // TODO: index-specific bounds
	}
	return thisTime;
}

int CurveInput::getTempPoint( int index )
{
	initLCD(&col, &row);
	lcd.print("Enter Temp ");
	lcd.print(index);
	lcd.print(":");
	lcd.setCursor(0, 1);
	byte buttonID = NONE;
	int thisTemp = temps[index];
	lcd.print(thisTemp);
	col = 0; row = 1;
	lcd.setCursor(col, row);
	delay(SELECT_DURATION);
	while ( buttonID != SELECT ) // any button other than SELECT
	{
		buttonID = btn.waitForButton();
		thisTemp = btn.actionIncDec(buttonID, TIME_TEMP_DURATION,
		                            col, row, thisTemp, 3, 0, 300);
		                            // TODO: index-specific bounds
	}
	return thisTemp;
}