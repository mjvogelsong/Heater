/*
********************************
mainControl.ino
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



// ~~~~~~~~~~~~~~~ Methods ~~~~~~~~~~~~~~~~~


// ~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~
void setup()
{
  
}

// ~~~~~~~~~~~~~~~ Main Loop ~~~~~~~~~~~~~~~~~
void loop()
{
  inputCurve();
  {
   printWelcome();
   printChoice();
   buttonAction();
   if (defaultReflow)
   {
     pattern = applyDefault();
   }
   else // User-Defined
   {
     pattern = applyUserControl();
     {
       printAssumption();
       userCurvePoints();
       {
         while (keepTakingPoints);
         {
           getPoint();
           {
             nextTimePoint = getTimePoint();
             nextTempPoint = getTempPoint();
           }
           error = checkPoint();
           while (error)
           {
             printError();
             getPoint();
             checkPoint();
           }
           keepTakingPoints = askNextPoint();
          } 
        }
      }
    } 
  }
  controlHeater();
  {
    while (timeRemaining && !error)
    {
      
    }
  }
}
