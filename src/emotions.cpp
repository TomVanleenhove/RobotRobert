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
    ofAddListener(arduino.EInitialized, this, &emotions::setupArduino);
    /*for(unsigned int i = 0; i < deviceList.size(); i++) {
     printf("ID: %d /n",deviceList[i].getDeviceID());
     printf("Name: %s /n",deviceList[i].getDeviceName().c_str());
     printf("Path: %s /n",deviceList[i].getDevicePath().c_str());
     }*/
    arduino.connect(deviceList[0].getDevicePath().c_str(), 57600);
}
void emotions::setupArduino(const int &version){
    ofRemoveListener(arduino.EInitialized, this, &emotions::setupArduino);
    ofLog() << "setup arduino " << version;
    arduino.sendServoAttach(9);
    arduino.sendServoAttach(10);
    arduino.sendDigitalPinMode(11, ARD_PWM);
    
    arduino.sendServo(9, 180/2, false);
    arduino.sendServo(10, 180/2, false);
    
}
void emotions::update(){
    heart();
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
    arduino.update();
}
void emotions::neutral(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::sad(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::happy(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::inLove(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::sleepy(){
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::crashy(){
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
    //servo wenkbrouwen
    //servo ogen?
    //ledjes op lichaam
    //ledjes op in hoofd
}
void emotions::heart(){
    if (up == true) {
        current_h += heartBeatingSpeed;
    }else{
        current_h -= heartBeatingSpeed;
    }
    
    if (0 >= current_h) {
        up = true;
        current_h = 0;
    }
    if (255 <= current_h) {
        up = false;
        current_h = 255;
    }
    
    arduino.sendPwm(11, current_h);
}
void emotions::eyes(int x,int y){
    arduino.sendServo(9,y, false);
    arduino.sendServo(10,x, false);
    //printf("Eyes Moving");
}