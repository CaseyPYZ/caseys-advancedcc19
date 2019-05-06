#pragma once

#include "ofMain.h"
#include <string>
#include <iostream>
#include <fstream>
#include "ofxJSON.h"
#include "ofxXmlSettings.h"
#include "Incident.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        bool comparIncdt(Incident& lhs, Incident& rhs);
    
        ofxJSONElement json;
        string del = ":";
    
//        map borders; l = 169000
//        int NORTH = 283000;
//        int SOUTH = 114000;
//        int EAST = 1078000;
//        int WEST = 909000;
    
        string url = "https://data.cityofnewyork.us/resource/833y-fsy8.json?$limit=20000&$$app_token=gkNekzywG9Gf1HHElNzW9qaxc";
    
        vector<shared_ptr<Incident>> incidents;
    
        ofxXmlSettings xml;
        string FILE_PATH = "shooting_data.xml";
        bool data_ready =  false;
        bool data_saved = false;
        fstream fin;
        int fsize;
    
        ofImage ss;
        
};
