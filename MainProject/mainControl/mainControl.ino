/*
********************************
mainControl.ino
********************************
Michael Vogelsong
4/14/13

Functions:

********************************
*/
// ~~~~~~~~~~~~~~~~ Libraries ~~~~~~~~~~~~~~~~
#include <LiquidCrystal.h>
#include <ButtonIO.h>
#include <CurveInput.h>
#include <ReflowControl.h>
#include <PID_v1.h>

// ~~~~~~~~~~~~~~~ Global Initialization ~~~~~~~~~~~~~~~~~
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ButtonIO btn(0);
CurveInput cinp;
ReflowControl rCont;
double currentTemp; // dynamic current temperature
double pidOutput; // PID output
double setPoint; // dynamic set point
PID myPID(&currentTemp, &pidOutput, &setPoint, KP, KI, KD, DIRECT);
int times[5];
int temps[5];
int smoothTimes[9];
int smoothTemps[9];
byte error;

// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~
void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.clear();
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~
void loop()
{
	error = 0;
        cinp.main();
	rCont.main();
}
