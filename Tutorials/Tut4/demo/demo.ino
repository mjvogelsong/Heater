/* Tutorial 4 - demo
Lab Group 7

Code From:
Jeremy's First Program
It's awesome!
www.jeremyblum.com
*/

int ledPin = 13;

void setup()
{
  //initialize pins as outputs
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
