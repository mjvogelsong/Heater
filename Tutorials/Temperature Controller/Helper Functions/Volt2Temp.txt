/* 

Method:
	Volt2Temp (int Volt, int Heater)
======================================================
Author:
	Allison Finley
	4/12/13
======================================================
Library Dependencies:
	None
======================================================
Function: 
	Convert voltage to temperature
	Turn heater on/off if temperature is too low/high
======================================================
Parameters:    
	param1: (int Volt) define Volt as input, corresponds to pin A1
	param2: (int Heater) define Heater as output, corresponds to pin 13
	param3: (Temp) converts voltage of thermocouple to temperature

======================================================
Returns:
	short Temp
======================================================
Calls:
	None
======================================================
Called by:
	Temperature control program
======================================================
Other Notes:
	May need to modify voltage-temp conversion according to
	the values of the thermocouple. Right now it is in sync
	with the potentiometer. May need to modify temperatures
	that turn the heater on and off.

*/



void Volt2Temp (int Volt, int Heater)
{
int sensorValue = analogRead(Volt); 
short Temp = sensorValue/204.6 *200; // convert analog readings to temperature

Serial.println(Temp);
delay(1000);
if (Temp >= 215) {
digitalWrite(Heater, LOW); // turn heater off if temp too high
  } else if (Temp < 150) {
    digitalWrite(Heater, HIGH); // turn heater on if temp too low
  }

}