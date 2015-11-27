#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void updatePaintFbo(int x, int y);
        void clearPaintFbo();
        void clearMaskFbo();

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
    
        int useEraser;
    
        ofImage img;
    
        ofShader pixelate;
        ofShader mask;
        ofFbo mainFbo;
        ofFbo maskFbo;
        ofFbo paintFbo;
        ofTexture maskTexture;
    
    
        ofxPanel gui;
		ofxFloatSlider pixelWidth;
        ofxFloatSlider pixelHeight;
        ofxFloatSlider blend;
        ofxFloatSlider brushRadius;
        ofxLabel clearLabel;
   
};
