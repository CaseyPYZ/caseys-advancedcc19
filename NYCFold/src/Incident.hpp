//
//  Incident.hpp
//  NYCFold
//
//  Created by Casey Pan on 5/3/19.
//

#ifndef Incident_hpp
#define Incident_hpp

#include "ofMain.h"
#include <stdio.h>
#include <string>
#include <iostream>

class Incident{
    
public:
    string timestr;
    long long int timestamp;
    int x_coord;
    int y_coord;
    
    int x_pos;
    int y_pos;
    
    Incident();
    Incident(string time_s, string x, string y);
    
    inline bool operator < (const Incident& _incdt){
        return this->timestamp < _incdt.timestamp;
    };
    
    inline bool operator > (const Incident& _incdt){
        return this->timestamp > _incdt.timestamp;
    };
    
    inline bool operator == (const Incident& _incdt){
        return this->timestamp == _incdt.timestamp;
    };
    
    
    void display();
    
};


#endif /* Incident_hpp */
