/*
Lab Group 7
Tutorial 4
*/

int ledPin = 13;

void setup()
{
  // initialize output pins
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
