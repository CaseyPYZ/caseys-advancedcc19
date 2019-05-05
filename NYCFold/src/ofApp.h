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
    
        ofxJSONElement json;
        string del = ":";
    
        int xmin = 1000000;
        int xmax = 1000000;
        int ymin = 200000;
        int ymax = 200000;
    
        // map borders
        int NORTH = 0;
        int SOUTH = 0;
        int EAST = 0;
        int WEST = 0;
    
        string url = "https://data.cityofnewyork.us/resource/833y-fsy8.json?$limit=20000&$$app_token=gkNekzywG9Gf1HHElNzW9qaxc";
    
        vector<shared_ptr<Incident>> incidents;
    
        ofxXmlSettings xml;
        string file_path = "shooting_data.xml";
        bool data_ready =  false;
        fstream fin;
        int fsize;
        
};
