#include <CapacitiveSensor.h>
#include <Servo.h>

int mouthInterval = 1000;
int blush = 0;
int blushUp = true;

//CrashLoop
int crashEven[8];
int crashUneven[8];
int crashStart;
bool crashBool = false;
int crashEmotion;

//SleepLoop
int sleepLeds[5];
int sleepEmotion;
int sleepStart;
int sleepCount;

int currentEmotion;
int heartBeatTempo = 30;
int current_h = 0;
bool up;

int servoGetal = 0;
int servoTestor = false;

Servo oogX;
Servo oogY;

int oogXR;
int oogYR;

//Wenkbrouwen
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

//CAPACITIVE
CapacitiveSensor   capacitive = CapacitiveSensor(53,52);  //DIGITAAL

//NAVEL
int navelIn = false;

//BREIN
int redBrain = 5;
int blueBrain = 4; //analoog
int yellowBrain = 2;
int greenBrain = 3;
int brain = 6; //analoog
int brainRotation = 20;
int brainRotating = false;
int brainDim = false;
int currentBrain;
int brainFlicker = false;
int brainLeds[4] = {redBrain, blueBrain, yellowBrain, greenBrain};
int ambientBrain = 0; // INSTELLEN
int ambientBrainOn = false;

void setup() {
  // CAPACITIVE 
  capacitive.set_CS_AutocaL_Millis(0xFFFFFFFF);
  // put your setup code here, to run once:
  pinMode(11, OUTPUT);
  oogX.attach(9);
  oogY.attach(10);
  
  browL.attach(8);
  browR.attach(7);
  
  for (int i = 22; i <= 41; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  //eyesSerial.begin(9600);
  //servoTest();
  analogWrite(6, 55);
  brainFunction();
  digitalWrite(41, HIGH);
}

void servoTest() {
  oogX.write(0);
  oogY.write(0);
  int xys = 0;
  
  for (int i = 0; i <= 10; i++) {
    //oogX.write((180 / 10)*i);
    browL.write(((36 / 10)*i));
    Serial.println("browL: " + String((180 / 10)*i));
    browR.write(((62/ 10)*i) + 108);
    delay(100);
  }
  oogX.write(180 / 2);
  oogY.write(180 / 2);
  browR.write((62 / 2) + 108);
  browL.write(36 / 2);
  
}
void loop() {
  /*if(bootInit == true){
    boot();
  }*/
  //sad();
  // put your main code here, to run repeatedly

  if (catchData == false) {
    if (Serial.available() > 0) {
      for (int i = 22; i <= 40; i++) {
        digitalWrite(i, LOW);
      }
      bootInit = false;
      int inByte = Serial.read();
      //Serial.write(inByte);
      Serial.println(inByte, DEC);
      //Serial.println("doen we!");
      switch (inByte) {
        case 'n':
          //neutral();
          currentEmotion = 1;
          break;
        case 'h':
          //happy();
          currentEmotion = 2;
          break;
        case 's':
          //sad();
          currentEmotion = 3;
          break;
        case 'l':
          //inLove();
          currentEmotion = 4;
          break;
        case 'y':
          //sleepy();
          currentEmotion = 5;
          break;
        case 'c':
          //crash();
          currentEmotion = 6;
          break;
        case 'u':
          //searchingForHumans();
          currentEmotion = 7;
          break;
        case 'e':
          Serial.println("eyes");
          catchData = true;
          break;
      }
    } else {
      if (bootInit == true) {
        boot();
      }
    }
  } else {
    //Serial.println("binnen");
    if (Serial.available() > 1) {
      xy[0] = Serial.read();
      xy[1] = Serial.read();
      float ratio = 180.0 / 255.0;
      moveEyes(xy[0] * ratio , xy[1] * ratio);
      //Serial.println("x: " + xy[0], DEC);
      Serial.println(xy[1], DEC);
      catchData = false;
    }
  }
  heart();
  emotionControl();
  delay(100);

  //CrashLoop
  if (currentEmotion == 6) {
    crashEmotion = true;
    if (crashBool) {
      //Serial.println("GELIJK");

      int i = 0;
      for (i = 0; i < 8; i = i + 1) {
        digitalWrite(crashEven[i], HIGH);
        digitalWrite(crashUneven[i], LOW);
      }
      int now = millis();
      if (crashStart + mouthInterval <= now) {
        crashStart = millis();
        crashBool = false;
      }

    } else {
      //Serial.println("ONGELIJk");

      int i = 0;
      for (i = 0; i < 8; i = i + 1) {
        digitalWrite(crashUneven[i], HIGH);
        digitalWrite(crashEven[i], LOW);
      }
      int now = millis();
      if (crashStart + mouthInterval <= now) {
        crashStart = millis();
        crashBool = true;
      }

    }
  }else{
    crashEmotion = false;
  }

  if(currentEmotion == 5){
    sleepEmotion = true;

    if(sleepCount == 5){
      sleepCount = 0;
    }
    
    int now = millis();
    if (sleepStart + mouthInterval <= now) {
      sleepStart = millis();
      for (int i = 0; i <= sleepCount; i = i + 1) {
        digitalWrite(sleepLeds[i], HIGH);
      }
      
      sleepCount += 1; 
   }
    
  }else{
    sleepEmotion = false; 
  }

    if(currentEmotion == 4){
      if(blush == 150){
        blushUp = false;
      }
      if(blush == 20){
        blushUp = true;
      }
      if(blushUp){
        blush += 10;
      }else{
        blush -= 10;
      }

      //Serial.println(blush, DEC);
      analogWrite(11, blush);
   }

   
   capacitiveLoop();
   brainLoop();
   navelLoop();
}
void browControl(int mode){
  switch (mode) {
    case 1:
    //neutral
      browR.write((62 / 2) + 108);
      browL.write(36 / 2);
      break;
    case 2:
    //happy
      browR.write(((62 / 3) * 2) + 108);
      browL.write((36 / 5) *2);
      break;
    case 3:
    //angry
      browR.write(108);
      browL.write(36);
      break;
    case 4:
      //sad
      browR.write((62 *2 ) + 26);
      browL.write(0);
      break;
    case 5:
      //happy
      browR.write((62 *2 ) + 36);
      browL.write(12);
      break;
  }
}
void emotionControl() {
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
  } else {
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
  heartBeatTempo = 100;
  analogWrite(11, current_h);
}
void moveEyes(float x, float y) {
  //Serial.println("oogX: "+ x);
  //Serial.println("oogY: "+ y);
  oogX.write(x);
  oogY.write(y);

}
void boot() {
  browControl(3);
  for (int i = 22; i <= 37; i++) {
    digitalWrite(i, HIGH);
    //delay(100);
  }
  for (int i = 22; i <= 40; i++) {
    digitalWrite(i, LOW);
  }
  currentBrain = blueBrain;
}
void neutral() {
  browControl(3);
  for (int i = 38; i <= 40; i++) {
    digitalWrite(i, HIGH);
  }
  digitalWrite(26, HIGH);
  digitalWrite(34, HIGH);
  currentBrain = yellowBrain;
}
void happy() {
  browControl(5);
  for (int i = 26; i <= 34; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 38; i <= 40; i++) {
    digitalWrite(i, HIGH);
  }

  browControl(1);
  currentBrain = yellowBrain;
}
void sad() {
  browControl(4); //SIP
  for (int i = 22; i <= 26; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 38; i <= 40; i++) {
    digitalWrite(i, HIGH);
  }
  for (int i = 34; i <= 38; i++) {
    digitalWrite(i, HIGH);
  }
  currentBrain = blueBrain;
}
void inLove() {
  for (int i = 26; i <= 34; i++) {
    digitalWrite(i, HIGH);
  }
  heartBeatTempo = 100;
  currentBrain = redBrain;
}
void sleepy() {
  browControl(1);
  sleepLeds[0] = 34;
  sleepLeds[1] = 38;
  sleepLeds[2] = 39;
  sleepLeds[3] = 40;
  sleepLeds[4] = 26;
  
  if(!sleepEmotion){
    sleepStart = millis();
  }
  //BRAIN
  currentBrain = 0;
}
void crash() {
  browControl(3);
  int cECount = 0;
  int cUECount = 0;
  for (int i = 22; i <= 37; i++) {
    if (i % 2) {
      crashEven[cECount] = i;
      cECount++;
    } else {
        crashUneven[cUECount] = i;
        cUECount++;
    }
  }
  mouthInterval = 700;
  
  if(!crashEmotion){
    crashStart = millis();
  }

  currentBrain = blueBrain;
}
void searchingForHumans() {
}

//BREIN
void brainFunction() {
  //digitalWrite(42, HIGH);
  //digitalWrite(47, HIGH);
  //digitalWrite(41, HIGH);
  //analogWrite(6, 55);
  analogWrite(4, 255);
  brainDim = true;
  currentBrain = blueBrain;
}

void brainLoop(){
  //ambientBrain aanzetten
  
  for (int i = 0; i <= 5; i++) {
    if(brainLeds[i] != currentBrain){
      analogWrite(brainLeds[i], 0);
    }
  }

  if(brainDim){
    if(brainFlicker){
      brainFlicker = false;
      analogWrite(currentBrain, 40);
      Serial.println("low");
    }else{
      Serial.println("high");
      analogWrite(currentBrain, 255);
      brainFlicker = true;
    }

    if(ambientBrainOn){
      digitalWrite(ambientBrain, HIGH); 
    }else{
      digitalWrite(ambientBrain, LOW);
    }
  }
}

void capacitiveLoop(){
  long start = millis();
  long total1 =  capacitive.capacitiveSensor(30);
  if(total1 > 0){
    //TOUCH = true
    Serial.println("touched!");
  }
}

void navelLoop(){
  int i = 9;
  if(i = 8){
    navelIn = true;
  }else{
    navelIn = false;
  }
  if(navelIn){
    
  }else{
    
  }
}


