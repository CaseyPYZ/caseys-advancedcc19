//
//  Cell.cpp
//  project_challenge_4
//
//  Created by Casey Pan on 3/31/19.
//

#include "Cell.hpp"

//--------------------------------------------------------------
Cell::Cell(){
    
}

//--------------------------------------------------------------
Cell::Cell(ofVec2f posVec, ofColor color, Target tgt, ofVec2f hz){
    color.getHsb(h,s,b);
    pos = posVec;
    target = tgt;
    HzRange = hz;
    state = false;
}

//--------------------------------------------------------------
void Cell::update(){
    
    // adjust alpha value according to button state
    if( state ){
        clr.a = 255;
    } else {
        clr.a = 60;
    }
}


//--------------------------------------------------------------
void Cell::draw(){
    ofSetColor(clr);
    ofDrawRectangle(pos.x, pos.y, size.x, size.y);
}


//--------------------------------------------------------------
void Cell::setColor(ofColor newClr){
    
    clr = newClr;
    clr.getHsb(h,s,b);
}


//--------------------------------------------------------------
float Cell::getH(){
    return h;
}


//--------------------------------------------------------------
float Cell::getS(){
    return s;
}


//--------------------------------------------------------------
float Cell::getB(){
    return b;
}
