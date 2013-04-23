#include <ButtonIO.h>
#include <LiquidCrystal.h>
#include <CurveInput.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
ButtonIO btn(0);
CurveInput cinp;

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
  boolean x = cinp.chooseCurve();
  Serial.println(x);
}
