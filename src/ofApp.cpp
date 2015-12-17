#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

//--------------------------------------------------------------
void ofApp::setup(){
    videoWidth = 640;
    videoHeight = 480;
    grabber.initGrabber(videoWidth, videoHeight);
    trackImage.load("dirk.jpg");
    vector<ofVideoDevice> devices = grabber.listDevices();
    grabber.setDeviceID(devices[0].id);
    finder.setup("haarcascade_frontalface_alt_tree.xml");
    serial.listDevices();
    emotion.setup(serial.getDeviceList());
    ofSetWindowShape(640, 480);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    //arduino.update();
    emotion.update();
    
    if(grabber.isFrameNew()) {
        ofImage frame;
        frame.setFromPixels(grabber.getPixels());
        
        //searchForImage(trackImage,frame,recognised);
        
        finder.findHaarObjects(frame);
    }
    //printf("arduino: %d \n",arduino.getPwm(11));
    
}

//--------------------------------------------------------------

void ofApp::draw(){
    grabber.draw(0, 0);
    ofDrawBitmapString(matchfinder.size(),10,10);
    ofDrawBitmapString(recognised,30,10);
    ofDrawBitmapString(normalMatches,10,470);
    ofDrawBitmapString(goodMatches,40,470);
    ofDrawBitmapString(emotion.capSense,150,470);
    primeBlob.boundingRect.width = 0;
    primeBlob.boundingRect.height = 0;
    for(unsigned int i = 0; i < finder.blobs.size(); i++) {
        ofRectangle cur = finder.blobs[i].boundingRect;
        ofDrawRectangle(cur.x, cur.y, cur.width, cur.height);

        if((primeBlob.boundingRect.width + primeBlob.boundingRect.height) < (finder.blobs[i].boundingRect.height + finder.blobs[i].boundingRect.width)){
            primeBlob = finder.blobs[i];
        }
    }
    int servoY = (int)((180 - ((primeBlob.boundingRect.x + (primeBlob.boundingRect.width / 2)) / 640)*180) );
    int servoX = (int)(((primeBlob.boundingRect.y + (primeBlob.boundingRect.height / 2)) / 480)*180);
    emotion.eyes(servoX, servoY);
    ofDrawBitmapString(servoY, 60, 470);
    ofDrawBitmapString(servoX, 60, 490);
}
void ofApp::searchForImage(ofImage trackImage,ofImage frame, bool recogniser){
    ofxCvColorImage img_1;
    ofxCvColorImage img_2;
    ofxCvGrayscaleImage grayImg_1;
    ofxCvGrayscaleImage grayImg_2;
    img_1.setFromPixels(frame.getPixels());
    img_2.setFromPixels(trackImage.getPixels());
    grayImg_1 = img_1;
    grayImg_2 = img_2;
    
    img1 = grayImg_1.getCvImage();
    img2 = grayImg_2.getCvImage();
    
    if(img1.empty() || img2.empty())
    {
        printf("Can't read one of the images\n");
        return -1;
    }
    
    OrbFeatureDetector detector;
    vector<KeyPoint> keypoints1, keypoints2;
    detector.detect(img1, keypoints1);
    detector.detect(img2, keypoints2);
    
    OrbDescriptorExtractor extractor;
    Mat descriptors1, descriptors2;
    extractor.compute(img1, keypoints1, descriptors1);
    extractor.compute(img2, keypoints2, descriptors2);
    
    BFMatcher matcher;
    vector<cv::DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);
    
    double min_dist = DBL_MAX;
    normalMatches = (int)matches.size();
    for (int i = 0; i < (int)matches.size(); i++){
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
    }
    if (min_dist < 1.0) min_dist = 1.0;
    
    const double threshold = 3.0 * min_dist;
    std::vector<cv::DMatch> matches_good;
    for (int i = 0; i < (int)matches.size(); i++) {
        if (matches[i].distance < threshold) {
            matches_good.push_back(matches[i]);
        }
    }
    
    namedWindow("RoboVision", 0);
    matchfinder.push_back(matches_good.size());
    printf("good matches: %lu",matches_good.size());
    drawMatches(img1, keypoints1, img2, keypoints2, matches_good, img_matches);
    imshow("RoboVision", img_matches);
    
    if(matchfinder.size() > 20){
        int threshold = 200;
        goodMatches = 0;
        for (int i = 0; i < (int)matchfinder.size(); i++){
            if(matchfinder[i] < threshold){
                goodMatches ++;
            }
        }
        if (goodMatches > 10 && normalMatches > 400) {
            trackImage.draw(0, 0);
            printf("MATCH FOUND!!!");
            recognised = true;
        }else{
            recognised = false;
        }
        matchfinder.clear();
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    emotion.currentEmotion = 3;
    if (key == OF_KEY_UP) {
        emotion.heartBeatingSpeed += 5;
    }
    if (key == OF_KEY_DOWN) {
        emotion.heartBeatingSpeed -= 5;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    emotion.currentEmotion = 2;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
