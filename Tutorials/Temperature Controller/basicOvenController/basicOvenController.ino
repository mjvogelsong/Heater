/*
********************************
basicOvenController.ino	
********************************
Michael Vogelsong
4/18/13

Asks the user to input a set point temperature (scrolling)
Measures the temperature (simulated by pot or thermocouple)
Updates the heater based on whether the current temperature
	is greater or less than the set point temperature
Checks for dangerously low or high temperatures, alerts user,
	and asks for a new set point (restarts loop)
********************************
*/

// Libraries
#include <LiquidCrystal.h>
#include <OvenControl.h>

// Debugging
#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

// ~~~~~~~~~~~~~~~ Global Initialization ~~~~~~~~~~~~~~~~~
// Select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Gets OvenControl functions
OvenControl ovc;

// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~
void loop()
{
	ovc.inputSetPoint();
	ovc.danger = 0;
	while ( ovc.danger == 0 )
	{
		ovc.currentTemp = ovc.volt2Temp(READ_PIN);
		ovc.danger = ovc.checkLimits(ovc.currentTemp, 0, 300);
		ovc.updateHeater(ovc.currentTemp, ovc.setPoint, HEATER_PIN);
		if ( ovc.danger == 0 )
		{
			ovc.displayTemp(ovc.currentTemp, ovc.setPoint);
			delay(CHECK_TIME);
		}
	}
	ovc.displayWarning(ovc.danger);
}
