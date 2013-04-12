//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
/*
*******************************************************
stopWatch.ino
Michael Vogelsong

$$ Note that LCD functionality code comes from:
Mark Bramwell, July 2010
This program will test the LCD panel and the buttons
********************************************************
*/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key = 0;
int adc_key_in = 0;
boolean SELECTED = false;

#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5
#define V1 50
#define V2 195
#define V3 380
#define V4 555
#define V5 790
#define VNONE 1000

int read_LCD_buttons()
{
  adc_key_in = analogRead(0); // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > VNONE) return btnNONE; // We make this the 1st option for speed reasons s
  if (adc_key_in < V1) return btnRIGHT;
  if (adc_key_in < V2) return btnUP;
  if (adc_key_in < V3) return btnDOWN;
  if (adc_key_in < V4) return btnLEFT;
  if (adc_key_in < V5) return btnSELECT;
  return btnNONE; // when all others fail, return this...
}

boolean buttonAction(lcd_key)
{
  boolean _select = false;
  
  switch (lcd_key) // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
    {
      //Instructions for what to do on RIGHT button press
      cCol = (cCol + 1) % 5;
      if (cCol == 2)
      {
        cCol = 3;
      }
      break;
    }

      case btnLEFT:
    {
      //Instructions for what to do on LEFT button press
      cCol = (cCol - 1) % 5;
      if (cCol == 2)
      {
        cCol = 1;
      }
      break;
    }

    case btnUP:
    {
      //Instructions for what to do on UP button press
      time[cCol] = (time[cCol] + 1) % 10;
      lcd.print(time[cCol]);
      lcd.setCursor(cRow,cCol);
      break;
    }

    case btnDOWN:
    {
      //Instructions for what to do on DOWN button press
      time[cCol] = (time[cCol] - 1) % 10;
      lcd.print(time[cCol]);
      lcd.setCursor(cRow,cCol);
      break;
    }
    
    case btnSELECT:
    {
      //Instructions for what to do on SELECT button press
      boolean _select = true;
      break;
    }
    case btnNONE:
    {
      //Instructions for what to do if no button is pressed.
      break;
    }
  }
  
  return _select
  
}

void setup()
{
  lcd.begin(16, 2); // start the library

  lcd.print("Enter Time:");

  int cRow = 1;
  int cCol = 0;

  lcd.setCursor(cRow,cCol);

  int time = {0,0,0,0,0}

  lcd.print(time[0]);
  lcd.print(time[1]);
  lcd.print(":");
  lcd.print(time[3]);
  lcd.print(time[4]);
  
  lcd.setCursor(cRow,cCol);

}

void loop()
{
  lcd_key = read_LCD_buttons(); // read the buttons
  
  while (!SELECTED)
  {
    SELECTED = buttonAction(lcd_key);
  }
  
  int minutes = 10*time[0] + time[1];
  int seconds = 10*time[3] + time[4];
  
  lcd.clear();
  lcd.home();
  lcd.print(minutes);
  lcd.print(":");
  lcd.print(
  
  while (minutes > 0) || (seconds > 0)
  {
    while (millis() - startMillis)
    {
      
    }
  }
  
  
}
