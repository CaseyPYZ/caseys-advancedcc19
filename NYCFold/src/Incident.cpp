//
//  Incident.cpp
//  NYCFold
//
//  Created by Casey Pan on 5/3/19.
//

#include "Incident.hpp"

//--------------------------------------------------------------
Incident::Incident(){
    
    ofLogNotice() << "An Incident is created." << endl;
    
}

//--------------------------------------------------------------
Incident::Incident(string time_s, string x, string y){
    
    timestamp = time_s;
    x_coord = std::stoi(x);
    y_coord = std::stoi(y);
    
    if( stoi(time_s.substr(2,1))==0 ){
        timeval = stoi(time_s.substr(3,9));
    } else if( stoi(time_s.substr(2,1))==1 ){
        timeval = stoi(time_s.substr(2,10));
    }
    
    x_pos = ofMap(x_coord, WEST, EAST, 0, ofGetWidth());
    y_pos = ofGetHeight()-ofMap(y_coord, SOUTH, NORTH, 0, ofGetHeight());
    
}

//--------------------------------------------------------------
Incident::Incident(string time_s, string timevals, int xp, int yp){
    
    timestamp = time_s;
    timeval = stoi(timevals);
    x_pos = xp;
    y_pos = yp;
    
}

//--------------------------------------------------------------
void Incident::display(){
    ofSetColor(160);
    ofDrawCircle(x_pos, y_pos, 0.5);
}



