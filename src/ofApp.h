#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofArduino.h"
#include "emotions.h"

class ofApp : public ofBaseApp{
public:
    
    void setup();
    void update();
    void draw();
    void searchForImage(ofImage,ofImage, bool);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofArduino arduino;
    ofSerial serial;
    ofVideoGrabber grabber;
    int videoWidth;
    int videoHeight;
    
    ofImage trackImage;
    ofImage frame;
    
    cv::Mat img1;
    cv::Mat img2;
    cv::Mat img_matches;
    vector<int> matchfinder;
    int normalMatches;
    int goodMatches;
    
    bool recognised;
    
    ofxCvHaarFinder finder;
    void setupArduino(const int & version);
    ofxCvBlob primeBlob;
};
