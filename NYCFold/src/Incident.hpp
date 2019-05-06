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
    string timestamp;
    unsigned int timeval;
    int x_coord;
    int y_coord;
    
    int x_pos;
    int y_pos;
    
    int NORTH = 283000;
    int SOUTH = 114000;
    int EAST = 1078000;
    int WEST = 909000;
    
    Incident();
    Incident(string time_s, string x, string y);
    Incident(string time_s, string timevals, int xp, int yp);
    
    inline bool operator < (const Incident& _incdt) const{
        return this->timeval < _incdt.timeval;
    };
    
    inline bool operator > (const Incident& _incdt) const{
        return this->timeval > _incdt.timeval;
    };
    
    inline bool operator == (const Incident& _incdt) const{
        return this->timeval == _incdt.timeval;
    };
    
    
    void display();
    
} myObject;


#endif /* Incident_hpp */
