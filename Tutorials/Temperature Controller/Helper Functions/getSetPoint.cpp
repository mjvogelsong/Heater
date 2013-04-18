/* 

Method:
	returnType methodName(type1 param1, ...)
======================================================
Author:
	Virginia Chen
	Michael Vogelsong
	4/17/13
======================================================
Library Dependencies:
	#include <libraryName.h>
======================================================
Function: 
	function description
======================================================
Parameters:    
	param1: (type1) description of variable
		e.g. example explanation
	param2: ...
	...
======================================================
Returns:
	(returnType) returned value description
======================================================
Calls:
	what methods does it call?
======================================================
Called by:
	what methods/programs call this method?
======================================================
Other Notes:
	NONE

*/

// ************** Global Variables *********
int adc_key_in;
byte setPoint;


// ************** Constants ****************
#define DEFAULT_SET_TEMP 100
#define btnRIGHT   0
#define btnUP      1
#define btnDOWN    2
#define btnLEFT    3
#define btnSELECT  4
#define btnNONE    5
#define V1         50
#define V2         148
#define V3         305
#define V4         459
#define V5         689
#define VNONE      1000
#define SELECT_DELAY 100

// *************** Main *******************
void inputSetPoint(byte lowerLimit, byte upperLimit)
{
	setPoint = DEFAULT_SET_TEMP;
	startingScreen();
	adjustAndSelect(DEFAULT_SET_TEMP, 0, 1);
}

// ***************** Helpers ***************
void startingScreen()
{
	lcd.clear();
	lcd.home();
	lcd.print("Set Temp (C)?");
	lcd.setCursor(0, 1);
	lcd.print(DEFAULT_SET_TEMP);
}

void adjustAndSelect( byte startVal, byte col, byte row )
{
	boolean selected = false;
	byte _LCD_key;
	while ( selected == false )
	{
		_LCD_key = read_LCD_keys();
		if ( _LCD_key != btnNONE )
		{
			selected = buttonTempAction(_LCD_key, col, row, 3);
			delay(SELECT_DELAY);
		}
	}
}

// read the ADC voltage to determine which button was pressed
byte read_LCD_keys()
{
	adc_key_in = analogRead(0); // read the value from the sensor
		// centered at these values: 0, 98, 255, 409, 639
		// we add approx 50 to those values and check to see if we are close
	if (adc_key_in > VNONE) return btnNONE; // We make this the 1st option for speed reasons
	if (adc_key_in < V1) return btnRIGHT;
	if (adc_key_in < V2) return btnUP;
	if (adc_key_in < V3) return btnDOWN;
	if (adc_key_in < V4) return btnLEFT;
	if (adc_key_in < V5) return btnSELECT;
	return btnNONE; // when all others fail, return this...
}

boolean buttonTempAction( byte LCD_key, byte col,
                          byte row, byte clearLength )
// pressing up increases the set temperature by 1, down decreases it by 1. Press select when you are done btnRIGHT/LEFT/NONE do nothing
{
	DEBUG_PRINT(LCD_key);
	boolean _select = false;
	lcd.setCursor(col, row);
	for ( int i = 0; i < (clearLength); i++)
	{
		lcd.print(" ");
	}
	lcd.setCursor(col, row);
	switch ( LCD_key ) // depending on which button was pushed, we perform an action
	{
		case btnUP:
		{
			//Instructions for what to do on UP button press
			setPoint++;
			break;
		}

		case btnDOWN:
		{
			//Instructions for what to do on DOWN button press
			setPoint--;
			break;
		}

		case btnSELECT:
		{
			//Instructions for what to do on SELECT button press
			_select = true;
			DEBUG_PRINT("selected");
			break;
		}
	}
	lcd.print(setPoint);
	return _select ; 
}