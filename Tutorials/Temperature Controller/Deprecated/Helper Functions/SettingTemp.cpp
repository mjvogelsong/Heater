/* 

Method:
  void SettingTemp(short SetTemp, int THigh, int TLow)
======================================================
Author:
	Virginia Chen
	4/17/13
======================================================
Library Dependencies:
	#include <libraryName.h>
======================================================
Function: 
	Asks user to input the temperature they want 
        to set, checks to see if it is within range, 
        asks for new set temperature if not.
======================================================
Parameters:    
	(short)  SetTemp user defined set temperature
        (int)    THigh maximum allowed temperature
        (int)    TLow  minimum allowed temperature
======================================================
Returns:
	void
======================================================
Calls:
	(boolean) buttonTempAction  added into code
======================================================
Called by:
	what methods/programs call this method?
======================================================
Other Notes:
	NONE

*/



void SettingTemp(short SetTemp, int THigh, int TLow)
{  
  TEMPOK = false;
  while (TEMPOK == false){
    lcd.print("Enter Set Temperature:");  
    lcd.print(SetTemp);
    lcd.print("(char)223");
    lcd.print("C");
    lcd.blink();  
  
    SELECTED = false;
    while(SELECTED == false)
    {
      lcd_key = read_LCD_buttons(); // read the buttons
      if (lcd_key != btnNONE)
      {
        SELECTED = buttonTempAction(lcd_key);
        delay(400);
      }
    }
    
    lcd.clear();
    lcd.home();
    lcd.print(SetTemp);
    
    if(SetTemp >= THigh){  // absolute max temperature
      lcd.clear();
      lcd.print("Temperature too high! Set new temperature.");
      }
    else if(SetTemp <= TLow){  // absolute min temperature
      lcd.clear();
      lcd.print("Temperature too low! Set new temperature.");
      }
    else {
      TEMPOK=true;
    }
}

boolean buttonTempAction(int lcd_key)
// pressing up increases the set temperature by 1, down decreases it by 1. Press select when you are done btnRIGHT/LEFT/NONE do nothing
{
  boolean _select = false;
  
  switch (lcd_key) // depending on which button was pushed, we perform an action
  {
    case btnUP:
    {
      //Instructions for what to do on UP button press
      SetTemp=SetTemp+1;
      lcd.print(SetTemp);
      break;
    }

    case btnDOWN:
    {
      //Instructions for what to do on DOWN button press
      SetTemp=SetTemp+1;
      lcd.print(SetTemp);
      break;
    }
    
    case btnSELECT:
    {
      //Instructions for what to do on SELECT button press
      _select = true;
      Serial.println("selected");
      break;
    }
    case btnNONE:
    {
      //Instructions for what to do if no button is pressed.
      break;
    }
    case btnRIGHT:
    {
      break;
    }
    case btnLEFT:
    {
      break;
    }
  }
  return _select; 
}
