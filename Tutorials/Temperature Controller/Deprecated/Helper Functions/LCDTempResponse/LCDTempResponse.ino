/* 

Method:
	void tempResponse(int TempValue, int TempMin, int TempMax)
======================================================
Author:
	Khanh Bui
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
        
	TempValue: (int) This is the temperature read from the Arduino
		e.g. Arduino code converts voltage to a temperature and back
        TempMin: (int) This is a constant that is set as the lower value of the range
        TempMax: (int) This is a constant that is set as the max value of the range

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

// set variables
int TempValue   = Temp; // set temperature value to Arduino's read temperature
int TempMin     = 25;    // set a minimum temperature value
int TempMax     = 218;  // set a maximum temperature value

void tempResponse(TempValue, TempMin, TempMax) {
  // if Arduino temp is greater than max temperature 
  if (Temp >= TempMax) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature is getting too HIGH!")
    lcd.setCursor(0,2);
    lcd.print('Turn off the heat')
  }
  
  // if Arduino temp is lower than min temperature
  if (Temp <= TempMin) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temperature is getting too LOW!")
    lcd.setCursor(0,1);
    lcd.print('Turn on the heat')
  }
};

void setup() {
  lcd.begin(16,2);
  TempValue = Temp;
};

void loop() {
  tempResponse(TempValue, TempMin, TempMax);
  if (Temp >= TempMax || Temp <= TempMin) {  
    for(int count = 0; count < 5; x++) {
    lcd.noDisplay();
    delay(200);
    lcd.display();
    delay(200);
    }
  }
};
