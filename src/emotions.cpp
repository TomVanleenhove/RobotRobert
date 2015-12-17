//
//  emotions.cpp
//  RoboVision
//
//  Created by Tom Vanleenhove on 15/11/15.
//
//

#include "emotions.h"

void emotions::setup(vector <ofSerialDeviceInfo> deviceList){
    
    currentEmotion = 1;
    heartBeatingSpeed = 50;
    current_h = 0;
    CurrentFLed = 22;
    bootInit = true;
    emotionSerial.setup(deviceList[0].getDevicePath().c_str(), 9600);
    //eyesSerial.setup(deviceList[0].getDevicePath().c_str(), 9600);
    //ofAddListener(arduino.EInitialized, this, &emotions::setupArduino);
    /*for(unsigned int i = 0; i < deviceList.size(); i++) {
     printf("ID: %d /n",deviceList[i].getDeviceID());
     printf("Name: %s /n",deviceList[i].getDeviceName().c_str());
     printf("Path: %s /n",deviceList[i].getDevicePath().c_str());
     }
    arduino.connect(deviceList[0].getDevicePath().c_str(), 57600);*/
}
/*void emotions::setupArduino(const int &version){
    ofRemoveListener(arduino.EInitialized, this, &emotions::setupArduino);
    ofLog() << "setup arduino " << version;
    arduino.sendDigitalPinMode(9,ARD_INPUT);
    arduino.sendDigitalPinMode(10,ARD_INPUT);
    arduino.sendDigitalPinMode(13, ARD_INPUT);
    for (int i = 22; i < 39; i++){
        arduino.sendDigitalPinMode(i, ARD_INPUT);
    }
    arduino.sendDigitalPinMode(11, ARD_PWM);
    arduino.sendAnalogPinReporting(0, ARD_ANALOG);
    arduino.sendServo(9, 180/2, false);
    arduino.sendServo(10, 180/2, false);
    arduino.sendDigital(13, ARD_HIGH);
    ofAddListener(arduino.EAnalogPinChanged, this, &emotions::analogPinChanged);
}
void emotions::analogPinChanged(const int & pinNum) {
    // do something with the analog input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    //potValue = "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum));
    capSense = arduino.getAnalog(pinNum);
    //printf("pin: %d \n",pinNum);
    //printf(" pinVal: %d",arduino.getAnalog(pinNum));
    
    touchfinder.push_back(arduino.getAnalog(pinNum));
    if(touchfinder.size() > 20){
        int threshold = 70;
        int touched = 0;
        for (int i = 0; i < (int)touchfinder.size(); i++){
            if(touchfinder[i] < threshold){
                touched ++;
            }
        }
        if (touched > 10) {
            printf("TOUCHING!!!");
            heartBeatingSpeed = 200;
        }else{
            //not touched
            heartBeatingSpeed = 50;
        }
        touchfinder.clear();
    }
}*/
void emotions::update(){
    /*heart();
    boot();*/
    /*if (emotionSerial.available() == 0) return;
    else if (emotionSerial.available() > 1){
        while(emotionSerial.available() > 0){
            int byte8 = emotionSerial.readByte();
            string msg = " " + ofToString(byte8);
            printf("byte: %s \n",msg.c_str());
        }
    }*/
    switch (currentEmotion) {
        case 1: //neutral:
            neutral();
            break;
        case 2: //sad:
            sad();
            break;
        case 3: //happy:
            happy();
            break;
        case 4: //inLove:
            inLove();
            break;
        case 5: //sleepy:
            sleepy();
            break;
        case 6: //crashy:
            crashy();
            break;
        case 7: //shutdown:
            shutdown();
            break;
        case 8: //searchingForHumans:
            searchingForHumans();
            break;
        default:
            neutral();
            break;
    }
    previousEmotion = currentEmotion;
    //arduino.update();
}
void emotions::neutral(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"n");
        printf("otto => neutral  \n");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::sad(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"s");
        printf("otto => sad  \n");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::happy(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"h");
        printf("\n otto => happy");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::inLove(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"l");
        printf("\n otto => in love");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::sleepy(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"y");
        printf("\n otto => sleepy");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::crashy(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"c");
        printf("\n otto => crashy");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::shutdown(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::searchingForHumans(){
    if (previousEmotion != currentEmotion) {
        emotionSerial.writeByte(*"u");
        printf("\n otto => searching for humans");
    }
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::eyes(int x,int y){
    //arduino.sendServo(9,y, false);
    //printf("xInteger: %d \n",x);
    //printf("send Byte: %d \n",x);
    unsigned char xByte = x;
    unsigned char yByte = y;
    //printf("xByte: %d \n",xByte);
    emotionSerial.writeByte(*"e");
    emotionSerial.writeByte(xByte);
    emotionSerial.writeByte(yByte);
    
}
