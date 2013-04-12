#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int ledPin = A0; 
int val = 0;

void setup ()
{
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop ()
{
  val = analogRead(ledPin); // read the input pin
  Serial.println(val); // for purposes of debugging
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(val);
}

