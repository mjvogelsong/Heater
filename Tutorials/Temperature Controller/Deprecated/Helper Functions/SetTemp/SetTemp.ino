short SetTemp=140;

void tempRange(SetTemp,THigh,TLow){
  if(SetTemp >= THigh){  // absolute max temperature
  lcd.clear();
  lcd.print("Temperature too high! Set new temperature.");
  softReset();
  }
  
  if(SetTemp <= TLow){  // absolute min temperature
  lcd.clear();
  lcd.print("Temperature too low! Set new temperature.");
  softReset();
  }
}

void (softReset){ // restart the program from the beginning, does not reset the peripherals and registers FOUND THIS ONLINE, NOT SURE IF IT WORKS
// but only want to reset to the point where you input the set temperature, so this may need be to changed.
asm volatile ("  jmp 0");
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

void setup()
{
  lcd.begin(16, 2); // start the library

  lcd.print("Enter Set Temperature:");

  // lcd.setCursor(cCol,cRow);

  lcd.print(SetTemp);
  lcd.print("(char)223");
  lcd.print("C");
  lcd.blink();  

}

void loop()
{
  
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
  
  tempRange(SetTemp,218,130);
}


