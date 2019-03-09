#pragma once

#include "Piece.hpp"
#include "Collage.hpp"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        ofVideoGrabber cam;
        int camWidth;
        int camHeight;
        ofPixels video_pixels;
        ofImage buffer;
        int midX = 0;
        int midY = 0;
    
        bool touching = false;
        bool holding = false;

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
        void checkPiece(ofVec2f cursor);
		
    
        string bgPath = "bg.jpg";
        vector<string> pathes{"red.jpg","blue.jpg","black.jpg","yellow.jpg"};
        vector<ofVec2f> posVec{
            ofVec2f(85,86),ofVec2f(400,477),
            ofVec2f(88,398),ofVec2f(400,85) };
        vector<ofVec2f> sizeVec{
            ofVec2f(307,302),ofVec2f(189,112),
            ofVec2f(150,150),ofVec2f(189,146) };
    
        Collage testCollage;
        Piece* touchedPiece;
};
