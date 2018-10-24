#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdio.h>

//====== Define ===================
#define HEART_BEAT_LIST_NUM 30
LiquidCrystal lcd(7,8,9,10,11,12); // (RS, E, D4, D5, D6, D7)
//================================
//====== ALL PORT DEFINE ===========
#define ALERT 5
//==================================

//====== HEART BEAT VALUE===========
double oldValue = 0;
double value = 0;
int rawValue = 0;
//==================================

int ANALOG_TEMPERATURE = A0;
int ANALOG_HEARTBEAT = A1;

int main(int argc, char** argv)
{
	printf("asdf");
}

void setup() 
{
  Serial.begin(9600);
  pinMode(ALERT, OUTPUT);
  lcd.begin(16,2);
}

// description : S (A0, VCC, GND)
double Getheartbeat(int input)
{
  rawValue = input;
  value = 0.75 * oldValue + (1-0.75) * rawValue;
  oldValue = value;
  
  return value;

}

double GetTemperature(int value) {
  double Temp;
  Temp = log(10000.0/(1024.0/value-1));
  Temp = 1/(0.001129148+(0.000234125+(0.0000000876741*Temp*Temp))*Temp);
  Temp = Temp - 233.15;
  return Temp;
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

void displayLED(double heart, double temp) {

  lcd.clear();
    if(heart>=0.0 && heart<=1.0){ //손가락 터치 않함
      lcd.print("Heart  : DANGER");
      digitalWrite(ALERT, HIGH);
    }else{
      lcd.print("Heart  : Average");
      digitalWrite(ALERT, LOW);
    }
  lcd.setCursor(0,1);
  if(temp<=70){ // 안 누르고 있을때 
      lcd.print("Temp   : DANGER");
      digitalWrite(ALERT, HIGH);
    }else{
      lcd.print("Temp   : Average");
      digitalWrite(ALERT, LOW);
    }
}

void loop() 
{ 
  // Getting raw Data from analog pin
  displayLED(GetAvgHeartBeat(), GetTemperature(analogRead(ANALOG_TEMPERATURE)));
  delay(40);
}

// params - 
//      iter : 소리 반복 횟수
//      delay_ms : Latency (1000 equals 1sec)

// S (Pin, +, - ) -
void AlertFire(int iter, int delay_ms)
{
  while(iter--)
  {
    digitalWrite(ALERT, HIGH);
    delay(delay_ms);
    digitalWrite(ALERT, LOW);
    delay(delay_ms);
  }

  return;
  
}

