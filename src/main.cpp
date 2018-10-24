#include <Arduino.h>


//====== HEART BEAT VALUE===========
double oldValue = 0;
double value = 0;
int rawValue = 0;
//==================================

int ANALOG_TEMPERATURE = A0;
int ANALOG_HEARTBEAT = A1;

void setup() 
{
  Serial.begin(9600);
}


// description : S (A0, VCC, GND)
double Getheartbeat(int input)
{
  rawValue = input;
  value = 0.75 * oldValue + (1-0.75) * rawValue;
  oldValue = value;
  
  return value;

}


double GetAvgHeartBeat()
{
    double heartBeat_list[HEART_BEAT_LIST_NUM];
    double heartBeat_total = 0.0;
    for(int i = 0; i < HEART_BEAT_LIST_NUM; i++)
    {
      heartBeat_list[i] = Getheartbeat(analogRead(ANALOG_HEARTBEAT));
      heartBeat_total += heartBeat_list[i];
  }
    Serial.print("Avg : ");
    Serial.println(heartBeat_total/HEART_BEAT_LIST_NUM);
  
  return heartBeat_total/HEART_BEAT_LIST_NUM;
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