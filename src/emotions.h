//
//  emotions.h
//  RoboVision
//
//  Created by Tom Vanleenhove on 15/11/15.
//
//

#ifndef __RoboVision__emotions__
#define __RoboVision__emotions__
#endif /* defined(__RoboVision__emotions__) */

#include "ofMain.h"
#include "ofArduino.h"

class emotions : public ofArduino{
public:
    
    void setup();
    void update();
    
    void neutral(); // emotion 1
    void sad();     // emotion 2
    void happy();   // emotion 3
    void inLove();  // emotion 4
    void sleepy();  // emotion 5
    void crashy();  // emotion 6
    void shutdown();// emotion 7
    void searchingForHumans();// emotion 8
    
    //ofArduino arduino;
    int currentEmotion;
    
};


