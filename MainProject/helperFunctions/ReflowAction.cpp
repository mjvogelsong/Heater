/* 

Method:
	void reflowAction(int tStart, int tempStart, int tEnd, int tempEnd)
======================================================
Author:
	Virginia Chen
	4/26/2013
======================================================
Library Dependencies:
	
======================================================
Function: 
	finds the slope of the segment and performs 
        PID until the end of the user defined period
======================================================
Parameters:    
	tStart: (int) start time of the segment
        tEnd:   (int) end time of the segment
        tempStart: (int) starting temperature of segment
        tempEnd: (int) ending temperature of segment
======================================================
Returns:
======================================================
Calls:
	PIDAction
======================================================
Called by:
======================================================
Other Notes:
	

*/


// performs PID for one segment of reflow curve
void reflowAction(int tStart, int tempStart, int tEnd, int tempEnd){
  
  // determine slope
  int reflowSlope = (tempEnd-tempStart)/(tEnd-tStart); // degrees C/sec
  tStartOfStage=millis()/1000; // sec
  
  // increases the set temperature by an amount every __ seconds, then performs PID
  while ((millis()/1000) < tEnd){
    int currentSetTemp=tempStart+(((millis()/1000)-tStartOfStage)*reflowSlope);
    PIDAction(currentSetTemp, currentTemp, heaterStatus);
    delay(2000) //milliseconds
  }
}
