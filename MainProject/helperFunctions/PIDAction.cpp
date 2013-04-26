/* 

Method:
	void PIDAction (double setPoint, double currentTemp, double heaterStatus)
======================================================
Author:
	Virginia Chen
	4/26/2013
======================================================
Library Dependencies:
	#include <PID_v1.h>
        #define RelayPin D2
======================================================
Function: 
	performs PID with relay output. 
======================================================
Parameters:    
	setPoint: (double) the temperature you want to set it at
        currentTemp: (double) current temperature
        heaterStatus: (double) whether heat is on/off, 
                    adjust this to change current temp
======================================================
Returns:
	
======================================================
Calls:
	
======================================================
Called by:
	reflowAction
======================================================
Other Notes:
	WindowSize = period of the output frequency (set to 2Hz)

*/


// PID with relay output
void PIDAction (double setPoint, double currentTemp, double heaterStatus){
  //Specify the links and initial tuning parameters
  PID myPID(&currentTemp, &heaterStatus, &setPoint,2,.1,5, DIRECT);
  
  int WindowSize = 50; // so the ouput frequency is 2 Hz
  unsigned long windowStartTime;

  windowStartTime = millis();

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  Input = analogRead(0);
  myPID.Compute();

  unsigned long now = millis();
  if(now - windowStartTime>WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if(Output > now - windowStartTime) digitalWrite(RelayPin,HIGH);
  else digitalWrite(RelayPin,LOW);
}
