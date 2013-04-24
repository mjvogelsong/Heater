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
	int times[10];
	int temps[10];
}

// ********** Functions **********
void CurveInput::main();
{
	boolean choice = chooseCurve();
	loadCurve(choice);
}

void CurveInput::initLCD( byte* col, byte* row );
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
	byte buttonID = NONE;
	initLCD(&col, &row);
	lcd.blink(); // show cursor
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
		lcd.print("Loaded Default");
	}
	else
	{
		loadUserCurve();
		lcd.print("Loaded User"
	}
	
}

void CurveInput::loadDefault()
{
	temp[0] = 25;
	temp[1] = 150;
	temp[2] = 150;
	temp[3] = 245;
	temp[4] = 200;
	
	time[0] = 0;
	time[1] = getTime(1, 2);
	time[2] = time[1] + 90;
	time[3] = getTime(3, 2);
	time[4] = getTime(4, -6);
}

int CurveInput::getTime( int current, float rate );
{
	return time[current-1] + round((temp[current] - temp[current-1]) / rate);
}

void CurveInput::loadUserCurve()
{
	printAssumption();
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
	boolean keepTakingPoints = true;
	byte index = 1;
	while ( keepTakingPoints )
	{
		times[index] = getTimePoint(index);
	}
}

int CurveInput::getTimePoint( int index );
{
	
}