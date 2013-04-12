/*

*******************************************************
stopWatchFinal.ino
*******************************************************

Michael Vogelsong
Virginia Chen
Allison Finley
Khanh Bui

Functions:
    -asks for user to enter time
    -runs stopwatch down until time is up
    -allows start/stop functionality with "select" button

********************************************************
$$ Note that LCD functionality code comes from:
Mark Bramwell, July 2010
This program will test the LCD panel and the buttons
********************************************************

*/

// include LiquidCrystal library
#include <LiquidCrystal.h>

// Debugging
#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

// ~~~~~~~~~~~~~~~ Initialization ~~~~~~~~~~~~~~~~~

// select the pins used on the LCD panel (create instance of type LiquidCrystal)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// initialize values
int     lcd_key    = 0;            // indicator for button pressed
int     adc_key_in = 0;            // ADC voltage for button's voltage division
boolean SELECTED   = false;        // indicates whether "select" button was pushed
int     cRow       = 1;            // LCD cursor row
int     cCol       = 0;            // LCD cursor column
int     time[]     = {0,0,0,0,0};  // Int array to represent digits
                                   //     MM:SS
                                   //     time[2] just acts as a placeholder for the ":"

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


// ~~~~~~~~~~~~~~~ Methods ~~~~~~~~~~~~~~~~~

// read the ADC voltage to determine which button was pressed
int read_LCD_buttons(){
  adc_key_in = analogRead(0); // read the value from the sensor
      // centered at these valies: 0, 98, 255, 409, 639
      // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > VNONE) return btnNONE; // We make this the 1st option for speed reasons s
  if (adc_key_in < V1) return btnRIGHT;
  if (adc_key_in < V2) return btnUP;
  if (adc_key_in < V3) return btnDOWN;
  if (adc_key_in < V4) return btnLEFT;
  if (adc_key_in < V5) return btnSELECT;
  return btnNONE; // when all others fail, return this...
}

// determines the action to perform based on the button that was pressed
boolean buttonAction(int lcd_key){
  boolean _select = false;    // private indicator of whether or not "select" was pressed
  switch (lcd_key) { // depending on which button was pushed, we perform an action
    case btnRIGHT: {
      // Instructions for what to do on RIGHT button press:
      //   move cursor to the right
      cCol = abs((cCol + 1) % 5); // mod for staying within bounds of cursor
      if (cCol == 2) {            // skip ":"
        cCol = 3;
      }
      lcd.setCursor(cCol,cRow);
      break;
    }

      case btnLEFT: {
      // Instructions for what to do on LEFT button press
      //   move cursor to the left

      cCol = (cCol - 1) % 5;  // mode for staying within bounds of cursor
      DEBUG_PRINT(cCol);
      if (cCol == 2) {        // skip ":"
        cCol = 1;
      }
      else if (cCol == -1) {  // arduino defines negative mods differently than other languages
        cCol = 4;             // change -1 to 4
      }
      lcd.setCursor(cCol,cRow);
      break;
    }

    case btnUP: {
      // Instructions for what to do on UP button press:
      //   increment digit on cursor
      time[cCol] = abs((time[cCol] + 1) % 10);  // mod for 0-9
      lcd.print(time[cCol]);
      lcd.setCursor(cCol,cRow);
      break;
    }

    case btnDOWN: {
      // Instructions for what to do on DOWN button press:
      //   decrement digit on cursor
      if (time[cCol] == 0){  // arduino negative mods are weird
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
      // Instructions for what to do on SELECT button press:
      //   update _selected
      _select = true;
      DEBUG_PRINT("selected");
      break;
    }
    case btnNONE:{
      // Instructions for what to do if no button is pressed:
      //   nothing
      break;
    }
  }
  
  return _select; // true only if "select" button pushed
  
}

// user interface for inputting time
void inputTime() {
  lcd_key = read_LCD_buttons(); // read the buttons
  if (lcd_key != btnNONE){
    SELECTED = buttonAction(lcd_key);   // perform action based on button pressed
    DEBUG_PRINT(lcd_key);
    DEBUG_PRINT(SELECTED);
    delay(400);
  }
}

// general purpose printing of MM:SS time
void printTime(int timeArray[], int col, int row){
  lcd.setCursor(col, row);
  lcd.print(time[0]);
  lcd.print(time[1]);
  lcd.print(":");
  lcd.print(time[3]);
  lcd.print(time[4]);
}

// updating timer value
void updateTime(){
  if (time[4] != 0){  // seconds: ones digit
    time[4]=time[4]-1;
  }
  else if (time[3] != 0){  // seconds: tens digit
    time[3]=time[3]-1;
    time[4]=9;
  }
  else if (time[1] != 0){  // minutes: ones digit
    time[1]=time[1]-1;
    time[3]=5;
    time[4]=9;
  }
  else { // minutes: tens digit
    time[0]=time[0]-1;
    time[1]=9;
  }
}

// flash the screen when the timer reaches 00:00
void flashDone(){
  for (int i = 1;i<5;i++){
    lcd.noDisplay();
    delay(500);
    lcd.display();
    delay(500);
  }
}

// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~

void setup(){
  lcd.begin(16, 2); // start the library
  lcd.home();
  lcd.print("Enter Time:");
  
  cRow = 1;
  
  printTime(time, cCol, cRow);

  lcd.setCursor(cCol,cRow);
  lcd.blink();  // let user know where the cursor is located
  
  Serial.begin(9600);
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~

void loop(){
  DEBUG_PRINT("Starting loop");
  while(SELECTED == false){ // any button (or no buttons) other than "select"
    inputTime();
  }
  DEBUG_PRINT("Time Control Done");
  
  lcd.clear();
  cCol = 0;
  cRow = 0;
  
  printTime(time, cCol, cRow);

  int but = read_LCD_buttons(); // initialize but
  
  while (but != btnSELECT){  // don't start timer until user hits "select"
    delay(50);
    but = read_LCD_buttons();
  }
  
  if (but == btnSELECT){
    lcd.noBlink(); // no longer need cursor
    while (but == btnSELECT){  // read until button is unpressed
      but = read_LCD_buttons();
    }
    
    boolean flagSelect = false; // initialize flagSelect
    
    while (time[0] !=0 || time[1] !=0 || time[3] !=0 || time[4] !=0){ // timer non-zero
      long timeT = millis();  // get current millis()
      
      while ((millis() - timeT) < 1000){ // second has not elapsed, so keep looking for "select"
        but = read_LCD_buttons();
        if (but == btnSELECT){ // "select" pressed
          while (but == btnSELECT){ // wait until "select" is unpressed
            but = read_LCD_buttons();
          }
          flagSelect = !flagSelect; // flag the "select" (bi-directional so 
                                    //    that system can resume on 2nd "select"
        }
        if (flagSelect == true){
          DEBUG_PRINT("break");
          break;                  // breaking while loop
        }
        delay(50);
      }
      
      if ((millis() - timeT)>=1000){ // second has elapsed
        updateTime();
        lcd.clear();
        printTime(time, cCol, cRow);
      }
    }
      flashDone(); // reached 00:00
  }  
}

