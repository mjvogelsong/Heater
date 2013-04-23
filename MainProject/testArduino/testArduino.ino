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
}
void loop()
{
  byte x = btn.waitForButton();
  Serial.println(x);
}
