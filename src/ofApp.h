#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

	public:
    
    /***********************************************************************
     * Standard openFrameworks methods
     *
     * these are provided by oF and present in every oF app
     *
     **********************************************************************/
    
        // default oF method that runs when the application opens
		void setup();
    
        // default oF method that runs every frame
        // this is more for CPU-based calculations etc
		void update();
    
        // default oF method that draws to the screen
		void draw();

        // these are various oF event functions
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

    /***********************************************************************
     * Custom methods and members
     *
     * these are specific to this app
     *
     **********************************************************************/

        // this method draws a circle to the paint Frame Buffer Object
        // centered on the mouse position
        void updatePaintFbo(int x, int y);
    
        // erase the paint Frame Buffer Object
        void clearPaintFbo();
    
        // erase the mask Frame Buffer Object
        void clearMaskFbo();
    
        // toggle for showing/hiding the HUD menu
        bool bShowHud;
        // toggle for showing/hiding the mask
        bool bDrawMask;
    
        // this is our main source image
        ofImage img;
    
        // shader for applying the pixelation effect
        ofShader pixelate;
        // shader used to mask the pixelation effect
        ofShader mask;
    
        // our main Frame Buffer object where masked pixelation
        // effect is applied
        ofFbo mainFbo;
        // the fbo that stores our alpha mask
        ofFbo maskFbo;
        // the fbo that stores a single frame of painting
        ofFbo paintFbo;
    
        // GUI parameters
        // these not only show up in GUI, but are used as members
        // to store parameters
        
        ofxPanel gui;
		ofxFloatSlider pixelWidth;
        ofxFloatSlider pixelHeight;
        ofxFloatSlider blend;
        ofxFloatSlider brushRadius;
    
        ofxLabel animationLabel;
        ofxToggle enableAnimation;
        ofxFloatSlider animSpeed;
    
};
