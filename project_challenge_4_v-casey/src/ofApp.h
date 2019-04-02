#pragma once

#include "Cell.hpp"
#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

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
    
        void drawGrid(float x, float y);
    
        void setGUI1();
        void setGUI2();
		
        ofxUISuperCanvas *gui1;
        ofxUISuperCanvas *gui2;
    
        ofxUITextInput *textInput;
    
        bool hideGUI;
        
        float red, green, blue;
        bool bdrawGrid;
        bool bdrawPadding;
    
        void guiEvent(ofxUIEventArgs &e);
    
        void loadImgFile();
        void loadAudFile();
        void audToggle();
    
        ofxUIMovingGraph *mg;
        ofxUIDropDownList *ddl;
        ofxUIToggleMatrix *tm;
    
        float *buffer;
        ofImage *img;
    
        ofSoundPlayer aud;
    
        float vol;
    
        float lowMin = 60.0f;
        float midMin = 800.0f;
        float highMin = 1600.0f;
        float highMax = 2500.0f;
    
    
        // Cells
    
        // initial color
        ofColor initClr = ofColor(20,20,20,255);
    
        ofVec2f pos1 = ofVec2f(230.0f, 30.0f);
        ofVec2f pos2 = ofVec2f(500.0f, 30.0f);
        ofVec2f pos3 = ofVec2f(770.0f, 30.0f);
        ofVec2f pos4 = ofVec2f(230.0f, 300.0f);
        ofVec2f pos5 = ofVec2f(500.0f, 300.0f);
        ofVec2f pos6 = ofVec2f(770.0f, 300.0f);
        ofVec2f pos7 = ofVec2f(230.0f, 570.0f);
        ofVec2f pos8 = ofVec2f(500.0f, 570.0f);
        ofVec2f pos9 = ofVec2f(770.0f, 570.0f);
    
        vector<Cell::Target> tVec{Cell::AMPLITUDE, Cell::FREQUENCY, Cell::TEXTURE};
    
        vector<ofVec2f> HzVec{
            ofVec2f(60.0f, 800.0f),
            ofVec2f(80.1f, 1600.0f),
            ofVec2f(1600.1f, 2500.0f)
        };
    
        vector<ofVec2f> poses{pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9};
    
        vector<Cell> cells;
        Cell tempc;
    
};
