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
    
    timestr = time_s;
    timestamp = std::stoll(time_s);
    x_coord = std::stoi(x);
    y_coord = std::stoi(y);
    
}

//--------------------------------------------------------------
void Incident::display(){
    
}



