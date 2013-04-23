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
	
}

// ********** Functions **********
void CurveInput::printWelcome()
{
	lcd.clear();
	lcd.home();
	lcd.print("Welcome to");
	lcd.setCursor(0, 1);
	lcd.print("Reflow Control!");
}

boolean CurveInput::chooseCurve()
{
	printCurveChoices();
	byte buttonID = NONE;
	byte col = 0;
	byte row = 0;
	lcd.blink();
	while ( buttonID != SELECT )
	{
		buttonID = btn.waitForButton();
		actionNavigate(buttonID, col, row, 0, 0, 0, 1);
	}
	return row;
}

void CurveInput::printCurveChoices();
{
	lcd.clear();
	lcd.home();
	lcd.print("A: Default Curve");
	lcd.setCursor(0, 1);
	lcd.print("B: User Curve");
	lcd.setCursor(0, 0);
	lcd.blink();
}