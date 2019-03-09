#pragma once
// this tells the compiler to only compile once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
    
        // first time: runs in following order
        // starting second time, runs repetedly update() & draw()
        // syncronise functions
		void setup();
        void update();
		void draw();

    
        // asyncronise functions
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
    
        // load image
        // m for member variables
        ofImage mOrange;
        ofImage mFactal;
    

    
		
};
