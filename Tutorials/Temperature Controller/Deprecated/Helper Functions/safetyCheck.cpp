/* 

Method:
	void tempResponse(int tempValue, int tempMin, int tempMax)
======================================================
Author:
	Khanh Bui
	(updated by Michael Vogelsong)
	4/12/2013
======================================================
Library Dependencies:
	#include <LiquidCrystal.h>
======================================================
Function: 
	Arduino Lab 2, Objective 2
        Print messages to user that instruct them to handle this situation.
        Prints and blinks LCD display
======================================================
Parameters: 
        
	tempValue: (int) This is the temperature read from the Arduino
		e.g. Arduino code converts voltage to a temperature and back
        tempMin: (int) This is a constant that is set as the lower value of the range
        tempMax: (int) This is a constant that is set as the max value of the range

======================================================
Returns:
	tempResponse (void) returns lcd print
======================================================
Calls:
	needs function that reads the temperature
======================================================
Called by:
	would be used in conjunction with a function that turns on/off heat
======================================================
NOTES: 
        not sure how user would actually do anything if we're making sure everything
        if automatic
*/

const int CHECK_TIME = 500;

// ********* Main **************
// Deprecated
void safetyCheck(byte tempValue, byte tempMin, byte tempMax) 
{
	byte relativeTemp = checkLimits(tempValue, tempMin, tempMax); 
	if	(relativeTemp != 0)	displayWarning(relativeTemp);
}

//********** Helpers ***********	

byte checkLimits(float tempValue, int tempMin, int tempMax)
{
	if (tempValue >= tempMax) return 1;	// Arduino temp is greater than max temperature
	else if (tempValue <= tempMin) return 2; // Arduino temp is lower than min temperature
	else return 0; // Arduino temp is within range
}
	
void displayWarning(byte typeError)	// TODO: single printWarning function
{	
	if (typeError == 1)	// Arduino temp is greater than max temperature
	{			
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO HIGH!");
		lcd.setCursor(0,1);
		lcd.print('Turn off heat');
	}
	else	// typeError == 2: Arduino temp is lower than min temperature
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO LOW!");
		lcd.setCursor(0,1);
		lcd.print('Turn on heat');
	}
	for(int count = 0; count < 5; count++)
	{	// Blink off and on
		lcd.noDisplay();
		delay(200);
		lcd.display();
		delay(200);
	}
}