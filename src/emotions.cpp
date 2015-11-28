//
//  emotions.cpp
//  RoboVision
//
//  Created by Tom Vanleenhove on 15/11/15.
//
//

#include "emotions.h"

void emotions::setup(){
    currentEmotion = 1;
}
void emotions::update(){
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