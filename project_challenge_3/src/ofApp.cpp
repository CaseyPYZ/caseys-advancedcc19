#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.setup(640, 480);
    camHeight = 480;
    camWidth = 640;
    
    
    vector<ofVideoDevice> devices = cam.listDevices();
    
    cam.setDeviceID(0);
    cam.setDesiredFrameRate(30);
    cam.initGrabber(camWidth, camHeight);
    
    touchedPiece = nullptr;
    
    
    testCollage = Collage(bgPath, pathes, posVec, sizeVec);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    int counter = 0;
    if (cam.isFrameNew()) {
        video_pixels = cam.getPixels();
        for (int x = 0; x < camWidth; x++) {
            for (int y = 0; y < camHeight; y++) {
                ofColor temp = video_pixels.getColor(x, y);
                if(temp.r >= 240 && temp.g >= 240 && temp.b >= 240 ) {
                    midX += x;
                    midY += y;
                    counter += 1;
                }
            }
        }
        if (counter != 0) {
            midX /= counter;
            midY /= counter;
        }
        
    }
    
    cam.update();
    
    // check if any piece is touched
    checkPiece(ofVec2f(midX, midY));
    
    // check piece
    
    testCollage.update(ofVec2f(midX, midY));
    
//    for (auto p : testCollage.pieces) {
//        ofLog() << p.isSelected;
//    }
//
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    testCollage.draw();
    
    
    ofDrawEllipse(midX, midY, 50, 50);
    
}

//--------------------------------------------------------------
void ofApp::checkPiece(ofVec2f cursor){
    
    for(auto &p : testCollage.pieces){
        
        if( cursor.x > p.pos.x && cursor.x < p.pos.x+p.size.x && cursor.y > p.pos.y && cursor.y < p.pos.y+p.size.y){
            
            touching = true;
            
            ofLog() << p.FILE_PATH << endl;
            if ( !holding ){
                //cursor is winthin the range of this piece
                p.isTouched = true;
               
                holding = true;
            }
        } else {
            p.isTouched = false;
            touching = false;
        }
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // isSelected
    if(key == ' ' && touching){
        for(auto &p : testCollage.pieces){
        
            p.isSelected = p.isTouched;
            
        }
        //ofLogNotice() << "space bar is down" << endl;
    }
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    for(auto &p : testCollage.pieces){
        
        ofLog() << p.isSelected;
        
    }
    if(key == ' '){
        for(auto &p : testCollage.pieces){
          
            p.isSelected = false;
            
        }
    }
    
    holding=false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
