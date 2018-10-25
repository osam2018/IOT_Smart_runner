static double standard = 1.0;

// 실행시 가장 먼저 호출되는 함수이며, 최초 1회만 실행됩니다.
// 변수를 선언하거나 초기화를 위한 코드를 포함합니다.

int piezo = 3; 

void playTone(String pos)
{
  int data = 523;
  if (pos == "도")
  {
      data = 261;
  }
  else if (pos == "레")
  {
      data = 294;
  }
  else if (pos == "미")
  {
    data = 330;
  }
  else if (pos == "파")
  {
    data = 349;
  }
  else if (pos == "솔")
  {
    data = 392;
  }
  else if (pos == "라")
  {
    data = 440;
  }
  else if (pos == "시")
  {
    data = 494;
  }
  else if (pos == "높은도")
  {
    data = 523;
  }else if (pos == "높은도")
  {
    data = 523;
  }
  else if (pos == "높은레")
  {
    data = 587
    ;
  }
 
  tone(piezo, data); 
}
// setup() 함수가 호출된 이후, loop() 함수가 호출되며,
// 블록 안의 코드를 무한히 반복 실행됩니다.



#define buttonPin 7                 // button on pin 7
int R = 9;
int G = 10;
int B = 11;
int value = LOW;                     // previous value of the LED
int buttonState;                     // variable to store button state
int lastButtonState;                 // variable to store last button state
int blinking;                     // condition for blinking - timer is timing
long interval = 100;                 // blink interval - change to suit
long previousMillis = 0;             // variable to store last time LED was updated
long startTime ;                     // start time for stop watch
long elapsedTime ;                 // elapsed time for stop watch
int fractional;                     // variable used to store fractional part of time
int elapsed_integer;



void setup()
{
  Serial.begin(9600);
  Serial.println("Start!");
  pinMode(buttonPin, INPUT);     // not really necessary, pins default to INPUT anyway
  pinMode(piezo, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

double ConvIntegersToDouble(int _integer, int fractional)
{
  String string_integer = String(_integer);
  String string_fractional = String(fractional);
  String str = string_integer + "." + string_fractional;
  return str.toDouble();
}

void oneStepTime(){
  double result= 0.0;
  // 요기에다 코드 붙혀주세요
  // check for button press
  buttonState = digitalRead(buttonPin);                 // read the button state and store

  if (buttonState == LOW && lastButtonState == HIGH && blinking == false)   // check for a high to low transition
  {  
    // if true then found a new button press while clock is not running - start the clock
    Serial.println("Start check"); 
    startTime = millis();                                 // store the start time
    blinking = true;                                     // turn on blinking while timing
    delay(5);                                             // short delay to debounce switch
    lastButtonState = buttonState;                         // store buttonState in lastButtonState, to compare next time
  }
  else if (buttonState == LOW && lastButtonState == HIGH && blinking == true)  // check for a high to low transition
  {
    Serial.println("End check"); 
    elapsedTime = millis() - startTime;             // store elapsed time
    blinking = false;                                 // turn off blinking, all done timing
    lastButtonState = buttonState;                     // store buttonState in lastButtonState, to compare next time

        // use modulo operator to get fractional part of time 
    elapsed_integer = (int)(elapsedTime / 1000L);
    fractional = (int)(elapsedTime % 1000L);
    
    result = ConvIntegersToDouble(elapsed_integer, fractional);
    Serial.println(result);
    
  if ( result > standard)
  {
        playMusic();
  }
    
  }
  else
  {
    lastButtonState = buttonState;                         // store buttonState in lastButtonState, to compare next time
  }
  // Usage Example
  // ConvIntegersToDouble( (int)(elapsedTime / 1000L), fractional)
 
}

void playMusic(){
  playTone("높은레");
    delay(250);
    noTone(3);
    playTone("높은도");
    delay(250);
    noTone(3);
    playTone("높은레");
    delay(250);
    noTone(3);
    delay(1100);
    playTone("높은레");
    delay(250);
    noTone(3);
    playTone("높은도");
    delay(250);
    noTone(3);
    playTone("높은레");
    delay(250);
    noTone(3);
    delay(1100);
   //--------------------
    playTone("높은레");
    delay(700);
    playTone("높은도");
    delay(200);
    playTone("파");//원키
    delay(400);
    playTone("솔");//원키
    delay(400);
    playTone("라");//원키
    delay(800);
    noTone(3);
    delay(800);
    //--------------------(2번째 verse)
    playTone("높은레");
    delay(300);
    noTone(3);
    playTone("높은레");
    delay(500);
    noTone(3);
    playTone("높은도");
    delay(300);
    noTone(3);
    playTone("높은레");
    delay(400);
    noTone(3);
    delay(500);
    playTone("높은레");
    delay(300);
    noTone(3);
    playTone("높은레");
    delay(500);
    noTone(3);
    playTone("높은도");
    delay(300);
    noTone(3);
    playTone("높은레");
    delay(400);
    noTone(3);
    delay(500);
    //--------------------
    playTone("솔");//원키
    delay(700);
    playTone("라");//원키
    delay(300);
    playTone("솔");//원키
    delay(300);
    playTone("파");//원키
    delay(300);
    playTone("레");//원키
    delay(400);
    playTone("파");//원키
    delay(800);
    noTone(3);
    delay(2000);
}


void blinkLED(int latency, int color) {
  // TO do : 매개변수 latency 초마다 1개의 LED(왼발)을 번갈아 깜빡거리는 함수 -> 왼발 기준으로 속도를 맞출수있게
  latency = 1000;
  if(color == 1){ // 현재 pace가 양호하면 '초록불'
    analogWrite(G,50);
    delay(latency/9);
    analogWrite(G,0);
    delay(latency-(latency/9));
  }else{  //현재 pace가 늦을 경우 '빨간불' 깜빡임으로 왼발기준 구보속도 조절시켜주기
      analogWrite(R,50);
      delay(latency/9);
      analogWrite(R,0);
      delay(latency-(latency/9));
  }
}

void loop()
{
  oneStepTime();
  
  
  /* 
  playTone("도");
    playTone("레");
    playTone("미");
    playTone("파");   
    playTone("솔");
    playTone("라");
    playTone("시");
    playTone("높은도");
  */
}