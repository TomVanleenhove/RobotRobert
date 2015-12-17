#include <Servo.h>

int currentEmotion;
int heartBeatTempo = 30;
int current_h = 0;
bool up;

Servo oogX;
Servo oogY;

int oogXR;
int oogYR;

Servo browL;
Servo browR;

bool bootInit = true;
bool catchData = false;
int dataIndex = 0;
int dataCatcher[3];
int Lastfunction;
int incomingByte = 0;

int currentFLed = 21;
byte xy[2];

void setup() {
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  oogX.attach(9);
  oogY.attach(10);
  for (int i=22; i <= 40; i++){
      pinMode(i, OUTPUT);
   }
   Serial.begin(9600);
   //eyesSerial.begin(9600);
   servoTest();
}
void servoTest(){
  oogX.write(0);
  oogY.write(0);
  for (int i=0; i <= 10; i++){
     oogX.write((180 / 10)*i);
     delay(100);
  }
  for (int i=0; i <= 10; i++){
     oogY.write((180 / 10)*i);
     delay(100);
  }
  oogX.write(180 / 2);
  oogY.write(180 / 2);
}
void loop() {
  /*if(bootInit == true){
    boot();
  }*/
  //sad();
  // put your main code here, to run repeatedly:
  if(catchData == false){
    if(Serial.available() > 0) {
      for (int i=22; i <= 40; i++){
        digitalWrite(i, LOW);
      }
      bootInit = false;
      int inByte = Serial.read();
      //Serial.write(inByte);
      Serial.println(inByte, DEC);
      //Serial.println("doen we!");
        switch (inByte) {
            case 'n':
                neutral();
                currentEmotion = 1;
                break;
            case 'h':
                happy();
                currentEmotion = 2;
                break;
            case 's':
                sad();
                currentEmotion = 3;
                break;
            case 'l':
                inLove();
                currentEmotion = 4;
                break;
            case 'y':
                sleepy();
                currentEmotion = 5;
                break;
            case 'c':
                crash();
                currentEmotion = 6;
                break;
            case 'u':
                searchingForHumans();
                currentEmotion = 7;
                break;
            case 'e':
                Serial.println("eyes");
                catchData = true;
                break;
        }
    }else{
      if(bootInit == true){
        boot();
      }
    }
  }else{
    Serial.println("binnen");
    if(Serial.available() > 1) {
      xy[0] = Serial.read();
      xy[1] = Serial.read();
      float ratio = 180.0/255.0;
      moveEyes(xy[0] * ratio , xy[1] * ratio);
      //Serial.println("x: " + xy[0], DEC);
      Serial.println(xy[1], DEC);
      catchData = false;
    }
  }
  heart();
  emotionControl();
  delay(100);
}
void emotionControl(){
  switch (currentEmotion) {
            case 1:
                neutral();
                break;
            case 2:
                happy();
                break;
            case 3:
                sad();
                break;
            case 4:
                inLove();
                break;
            case 5:
                sleepy();
                break;
            case 6:
                crash();
                break;
            case 7:
                searchingForHumans();
                break;
        }
}
void heart() {
  // put your setup code here, to run once:
  if (up == true) {
        current_h += heartBeatTempo;
    }else{
        current_h -= heartBeatTempo;
    }
    
    if (0 >= current_h) {
        up = true;
        current_h = 0;
    }
    if (255 <= current_h) {
        up = false;
        current_h = 254;
    }
    analogWrite(11, current_h);
}
void moveEyes(float x, float y) {
   //Serial.println("oogX: "+ x);
   //Serial.println("oogY: "+ y);
   oogX.write(x);
   oogY.write(y);
   
}
void boot(){
            for (int i=22; i <= 37; i++){
               digitalWrite(i, HIGH);
               delay(100);
             }
             for (int i=22; i <= 40; i++){
               digitalWrite(i, LOW);
             }
}
void neutral(){
}
void happy(){
  for (int i=26; i <= 34; i++){
     digitalWrite(i, HIGH);
  }
  for (int i=38; i <= 40; i++){
     digitalWrite(i, HIGH);
  }
}
void sad(){
  for (int i=22; i <= 26; i++){
     digitalWrite(i, HIGH);
  }
  for (int i=38; i <= 40; i++){
     digitalWrite(i, HIGH);
  }
  for (int i=34; i <= 38; i++){
     digitalWrite(i, HIGH);
  }
}
void inLove(){
}
void sleepy(){
}
void crash(){
}
void searchingForHumans(){
}
