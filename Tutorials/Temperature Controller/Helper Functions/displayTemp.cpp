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
  displayCurrentTemp = roundDigit(currentTemp,-1);
  lcd.print("Current:", displayCurrentTemp);
  lcd.setCursor(1,0);
  lcd.print("SetPoint:", setPoint);
}