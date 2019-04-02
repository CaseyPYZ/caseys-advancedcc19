//
//  Cell.hpp
//  project_challenge_4
//
//  Created by Casey Pan on 3/31/19.
//

#ifndef Cell_hpp
#define Cell_hpp

#include <stdio.h>
#include "ofMain.h"

class Cell{
    
public:
    
    float h;
    float s;
    float b;
    
    ofColor clr;
    
    enum Target{
        AMPLITUDE,
        FREQUENCY,
        TEXTURE
    };
    
    Target target;
    
    ofVec2f HzRange;
    
    ofVec2f pos;
    ofVec2f size = ofVec2f(260.0f,260.0f);
    
    bool state;
    
    Cell();
    Cell(ofVec2f posVec, ofColor color, Target target, ofVec2f hz);
    
    void setColor(ofColor newClr);
    float getH();
    float getS();
    float getB();
   
    void update();
    void draw();
    
};

#endif /* Cell_hpp */
