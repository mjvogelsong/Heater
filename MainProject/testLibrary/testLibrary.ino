#include <ButtonIO.h>
#include <LiquidCrystal.h>
#include <CurveInput.h>
#include <ReflowControl.h>
#include <PID_v1.h>

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

// Debugging
#define DEBUG 1
#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.println(x)
#else
  #define DEBUG_PRINT(x)
#endif

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}
void loop()
{
  cinp.main();
  DEBUG_PRINT("Times");
  for ( int i = 0; i < 5; i++ )
  {
    DEBUG_PRINT(times[i]);
  }
  DEBUG_PRINT("Temps");
  for ( int i = 0; i < 5; i++ )
  {
    DEBUG_PRINT(temps[i]);
  }
  delay(4000);
  DEBUG_PRINT("");
}
