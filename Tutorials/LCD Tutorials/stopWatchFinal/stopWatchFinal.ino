/*
*******************************************************
stopWatch.ino
Michael Vogelsong

$$ Note that LCD functionality code comes from:
Mark Bramwell, July 2010
This program will test the LCD panel and the buttons
********************************************************
*/

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Initialize values
int     lcd_key    = 0;
int     adc_key_in = 0;
boolean SELECTED   = false;
int     cRow       = 1;
int     cCol       = 0;
int     time[]     = {0,0,0,0,0};

// define constants so that mapped values are easier to understand
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

int read_LCD_buttons(){
  adc_key_in = analogRead(0); // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 98, 255, 409, 639
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > VNONE) return btnNONE; // We make this the 1st option for speed reasons s
  if (adc_key_in < V1) return btnRIGHT;
  if (adc_key_in < V2) return btnUP;
  if (adc_key_in < V3) return btnDOWN;
  if (adc_key_in < V4) return btnLEFT;
  if (adc_key_in < V5) return btnSELECT;
  return btnNONE; // when all others fail, return this...
}

boolean buttonAction(int lcd_key){
  boolean _select = false;
  
  switch (lcd_key) {// depending on which button was pushed, we perform an action
    case btnRIGHT: {
      //Instructions for what to do on RIGHT button press
      cCol = abs((cCol + 1) % 5);
      if (cCol == 2) {
        cCol = 3;
      }
      lcd.setCursor(cCol,cRow);
      break;
    }

      case btnLEFT: {
      //Instructions for what to do on LEFT button press
      Serial.print("before:");
      Serial.print(cCol);
      cCol = (cCol - 1) % 5;
      Serial.println(cCol);
      if (cCol == 2) {
        cCol = 1;
      }
      else if (cCol == -1) {
        cCol = 4;
      }
      lcd.setCursor(cCol,cRow);
      break;
    }

    case btnUP: {
      //Instructions for what to do on UP button press
      time[cCol] = abs((time[cCol] + 1) % 10);
      lcd.print(time[cCol]);
      lcd.setCursor(cCol,cRow);
      break;
    }

    case btnDOWN: {
      //Instructions for what to do on DOWN button press
      if (time[cCol] == 0){
        time[cCol] = 9;
      }
      else {
      time[cCol] = abs((time[cCol] - 1) % 10);
      }
      lcd.print(time[cCol]);
      lcd.setCursor(cCol,cRow);
      break;
    }
    
    case btnSELECT:{
      //Instructions for what to do on SELECT button press
      _select = true;
      Serial.println("selected");
      break;
    }
    case btnNONE:{
      //Instructions for what to do if no button is pressed.
      break;
    }
  }
  
  return _select;
  
}

void printTime(int timeArray[], int col, int row){
  lcd.setCursor(col, row);
  lcd.print(time[0]);
  lcd.print(time[1]);
  lcd.print(":");
  lcd.print(time[3]);
  lcd.print(time[4]);
}

void updateTime(){
  if (time[4] != 0){
    time[4]=time[4]-1;
  }
  else if (time[3] != 0){
    time[3]=time[3]-1;
    time[4]=9;
  }
  else if (time[1] != 0){
    time[1]=time[1]-1;
    time[3]=5;
    time[4]=9;
  }
  else {
    time[0]=time[0]-1;
    time[1]=9;
  }
}

void flashDone(){
// Turn off the display:
  for (int i = 1;i<5;i++){
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);
  }
}

void setup(){
  lcd.begin(16, 2); // start the library
  lcd.home();
  lcd.print("Enter Time:");
  
  cRow = 1;
  
  printTime(time, cCol, cRow);

  lcd.setCursor(cCol,cRow);
  lcd.blink();
  
  Serial.begin(9600);
}

void loop(){
  Serial.println("Starting loop");
  
  while(SELECTED == false){
    lcd_key = read_LCD_buttons(); // read the buttons
    if (lcd_key != btnNONE){
      SELECTED = buttonAction(lcd_key);
      Serial.print(lcd_key);
      Serial.println(SELECTED);
      delay(400);
    }
  }
  
  Serial.println("Time Control Done");
  
  lcd.clear();
  cCol = 0;
  cRow = 0;
  
  printTime(time, cCol, cRow);

  int but = read_LCD_buttons();
  
  while (but!=4){
    delay(50);
    but = read_LCD_buttons();
  }
  
  if (but==4){
    lcd.noBlink();
    while (but == 4){
      but = read_LCD_buttons();
    }
    boolean flag = false;
    
    while (time[0] !=0 || time[1] !=0 || time[3] !=0 || time[4] !=0){
      long timeT = millis();
      
      while ((millis() - timeT) < 1000){
        but = read_LCD_buttons();
        if (but==4){
          while (but == 4){
            but = read_LCD_buttons();
          }
          flag = !flag;
        }
        if (flag == true){
          Serial.println("break");
          break;
        }
        delay(50);
      }
      
      if ((millis() - timeT)>=1000){
        updateTime();
        lcd.clear();
        printTime(time, cCol, cRow);
      }
    }
      flashDone();
  }  
}

