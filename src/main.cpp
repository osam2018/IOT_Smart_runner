#include <Arduino.h>

int ANALOG_TEMPERATURE = A0;

void setup() 
{
  Serial.begin(9600);
}


double GetTemperature(int value) {
  double Temp;
  Temp = log(10000.0/(1024.0/value-1));
  Temp = 1/(0.001129148+(0.000234125+(0.0000000876741*Temp*Temp))*Temp);
  Temp = Temp - 233.15;
  return Temp;
}


void loop() 
{ 
	
}