#define READ_PIN 5
#define ROOM_TEMP_ADC 20

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(5, INPUT);
}
void loop()
{
  int sensorValue = analogRead(READ_PIN);
  int voltage = map(sensorValue, 0, 1023, 0, 5000);
  int roomTempmV = map(ROOM_TEMP_ADC, 0, 1023, 0, 5000);
  float currentTemp = (((float)(voltage - roomTempmV))/5) + 25;
  Serial.print("ADC ");
  Serial.print(sensorValue);
  Serial.print("; mV ");
  Serial.print(voltage);
  Serial.print("; RTmV ");
  Serial.print(roomTempmV);
  Serial.print("; Temp ");
  Serial.println(currentTemp);
  delay(1000);
}
