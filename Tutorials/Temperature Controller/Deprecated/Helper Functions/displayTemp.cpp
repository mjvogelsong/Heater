/* 

Method:
	void displayTemp(short currentTemp, int setPoint)
======================================================
Author:
	Michael Vogelsong
	4/12/13
======================================================
Library Dependencies:
	#include <LiquidCrystal.h>
======================================================
Function: 
	displays the current temperature
    	displays the set point temperature
======================================================
Parameters:    
	currentTemp: (short) current temperature
	setPoint: (int) set point temperature 
======================================================
Returns:
	void
======================================================
Calls:
	float roundDigit(float num, int digit)
======================================================
Called by:
	NONE
======================================================
Other Notes:
	To be placed in WHILE loop in Temperature Control Program

*/



void displayTemp(float currentTemp, int setPoint)
{
  lcd.clear();
  lcd.setCursor(0,0);
  int displayCurrentTemp = round(currentTemp);
  lcd.print("Current:");
  lcd.print(displayCurrentTemp);
  lcd.setCursor(0,1);
  lcd.print("SetPoint:");
  lcd.print(setPoint);
}