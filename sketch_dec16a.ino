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
  for (int i=22; i <= 40; i++){
      pinMode(i, OUTPUT);
   }
   Serial.begin(57600);
   //eyesSerial.begin(9600);
}

void loop() {
  heart();
  /*if(bootInit == true){
    boot();
  }*/
  //sad();
  // put your main code here, to run repeatedly:
  //if(catchData == false){
    if(Serial.available() > 0) {
      for (int i=22; i <= 40; i++){
        digitalWrite(i, LOW);
      }
      bootInit = false;
      byte inByte = Serial.read();
      Serial.write(inByte);
      //Serial.println(inByte);
        switch (inByte) {
            case 'n':
                neutral();
                break;
            case 'h':
                happy();
                break;
            case 's':
                sad();
                break;
            case 'l':
                inLove();
                break;
            case 'y':
                sleepy();
                break;
            case 'c':
                crash();
                break;
            case 'u':
                searchingForHumans();
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
  /*}else{
    if(Serial.available() > 1) {
      xy[0] = Serial.read();
      xy[1] = Serial.read();
      float ratio = 180.0/255.0;
      moveEyes(xy[0] * ratio , xy[1] * ratio);
      Serial.println("x: " + xy[0]);
      Serial.println("y: " + xy[1]);
    }
  }*/
  delay(100);
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
