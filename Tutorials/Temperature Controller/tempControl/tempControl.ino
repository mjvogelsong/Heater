/*
********************************
tempControl.ino
********************************

Michael Vogelsong
4/14/13

Functions:

********************************
*/

#include <LiquidCrystal.h>

// Debugging
#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

// ~~~~~~~~~~~~~~~ Global Initialization ~~~~~~~~~~~~~~~~~

// select the pins used on the LCD panel (create instance of type LiquidCrystal)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

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
#define TOO_HIGH 1
#define TOO_LOW	2
const byte READ_PIN = 1;
const int CHECK_TIME = 500;
const byte HEATER_PIN = 13;

byte setPoint;
int adc_key_in;
float currentTemp;
byte danger;
boolean heaterStatus = LOW;

// ~~~~~~~~~~~~~~~ Methods ~~~~~~~~~~~~~~~~~
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
	adc_key_in = analogRead(0);// read the value from the sensor
DEBUG_PRINT(adc_key_in);
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
	boolean _select = false;
  DEBUG_PRINT(LCD_key);
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

float Volt2Temp( byte readPin )
{
	//int sensorValue = analogRead(readPin); 
        int sensorValue = -3;
	return sensorValue/204.6 *200; // convert analog readings to temperature
}

byte checkLimits(float tempValue, int tempMin, int tempMax)
{
	if (tempValue >= tempMax) return 1;	// Arduino temp is greater than max temperature
	else if (tempValue <= tempMin) return 2; // Arduino temp is lower than min temperature
	else return 0; // Arduino temp is within range
}

void updateHeater( float current, byte setPoint, byte heaterPin )
{
	digitalWrite(heaterPin, setPoint > current);
}

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

void displayWarning(byte typeError)	// TODO: single printWarning function
{	
	if (typeError == 1)	// Arduino temp is greater than max temperature
	{			
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO HIGH!");
		lcd.setCursor(0,1);
		lcd.print("Turning off heat!");
		digitalWrite(HEATER_PIN, LOW);
	}
	else	// typeError == 2: Arduino temp is lower than min temperature
	{
		lcd.clear();
		lcd.setCursor(0,0);
		lcd.print("TOO LOW!");
		lcd.setCursor(0,1);
		lcd.print("Turning on heat!");
		digitalWrite(HEATER_PIN, HIGH);
	}
	for(int count = 0; count < 5; count++)
	{	// Blink off and on
		lcd.noDisplay();
		delay(300);
		lcd.display();
		delay(300);
	}
}

// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(READ_PIN, INPUT);
  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~
void loop()
{
	inputSetPoint(0, 255);
	danger = 0;
	while ( danger == 0 )
	{
		currentTemp = volt2Temp(READ_PIN);
		danger = checkLimits(currentTemp, 0, 300);
		updateHeater(currentTemp, setPoint, HEATER_PIN);
		if ( danger == 0 )
		{
			displayTemp(currentTemp, setPoint);
			delay(CHECK_TIME);
		}
	}
	displayWarning(danger);
}
