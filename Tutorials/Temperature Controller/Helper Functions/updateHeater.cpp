/* 

Method:
	returnType methodName(type1 param1, ...)
======================================================
Author:
	Michael Vogelsong
	4/17/13
======================================================
Library Dependencies:
	#include <libraryName.h>
======================================================
Function: 
	function description
======================================================
Parameters:    
	param1: (type1) description of variable
		e.g. example explanation
	param2: ...
	...
======================================================
Returns:
	(returnType) returned value description
======================================================
Calls:
	what methods does it call?
======================================================
Called by:
	what methods/programs call this method?
======================================================
Other Notes:
	NONE

*/

const byte HEATER_PIN = 13;
boolean heaterStatus = LOW;

// Quick description
void updateHeater( float current, byte setPoint, byte heaterPin )
{
	digitalWrite(heaterPin, ( setPoint > current ));
}