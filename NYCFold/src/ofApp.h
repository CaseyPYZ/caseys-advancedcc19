#pragma once

#include "ofMain.h"
#include <string>
#include <iostream>
#include <fstream>
#include "ofxJSON.h"
#include "ofxXmlSettings.h"
#include "ofxOpenCv.h"
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
    
        void clockPlus();
        bool comparIncdt(shared_ptr<Incident> lhs, shared_ptr<Incident> rhs);
    
        void saveReverseImg();
        void exportPDF();
    
        bool paused = false;
    
        ofxJSONElement json;
        string del = ":";
    
        string url = "https://data.cityofnewyork.us/resource/833y-fsy8.json?$limit=20000&$$app_token=gkNekzywG9Gf1HHElNzW9qaxc";
    
        vector<shared_ptr<Incident>> incidents;
    
        ofxXmlSettings xml;
        string FILE_PATH = "shooting_data.xml";
        bool data_ready =  false;
        bool data_saved = false;
        fstream fin;
        int fsize;
    
        ofImage ss;
    
        //int itr = 0;
    
        int CLOCK_INIT = 601010000;
        int CLOCK_MAX = 1812310000;
        int pos_offset = 0;
        string full_month = "30";
        int clock = 601010000;
    
        string clkpre;
        string clkstr;
        string clkstr_b;
        ofTrueTypeFont clkfont;
    
        bool showstr = true;
    
        ofImage grabbedImg;
        ofPixels pix;
        ofTexture tex;
    
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage greyImg;
    
        ofxCvContourFinder ctrFinder;
    
        ofFbo canvas;
        
};
