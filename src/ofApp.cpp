#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofLogVerbose();

    // load image
    img.load("hadley.jpg");
    
    // load shaders
    pixelate.load("shaders/pixelate");
    
    // setup fbos
    ofFbo::Settings fboSettings;
    fboSettings.width = img.getWidth();
    fboSettings.height = img.getHeight();
    mainFbo.allocate(fboSettings);
    maskFbo.allocate(fboSettings);
    
    // set window size
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    // setup gui
    gui.setup();
	gui.add(pixelWidth.setup("Pixel Width", 15.0, 0.0, 50.0));
	gui.add(pixelHeight.setup("Pixel Height", 15.0, 0.0, 50.0));
	gui.add(blend.setup("Blend", 1.0, 0.0, 1.0));
    
    // draw simple mask in center
    simpleMask.setFromCenter(ofPoint(ofGetWidth()/2, ofGetHeight()/2), ofGetWidth()/2, ofGetHeight()/2);
    
}

//--------------------------------------------------------------
void ofApp::update(){

    maskFbo.begin();
        ofClear(0);
        ofSetColor(255);
        ofDrawRectangle(simpleMask);
    maskFbo.end();


    mainFbo.begin();
        ofClear(0);
        pixelate.begin();
            pixelate.setUniformTexture("src", img.getTexture(), 1);
            pixelate.setUniformTexture("mask", maskFbo.getTexture(), 2);
    
            pixelate.setUniform1f("width", ofGetWidth());
            pixelate.setUniform1f("height", ofGetHeight());
            pixelate.setUniform1f("pixel_w", pixelWidth);
            pixelate.setUniform1f("pixel_h", pixelHeight);

            pixelate.setUniform1f("blend", blend);

            img.draw(0,0);
        pixelate.end();
    mainFbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);
    ofBackground(255, 0, 0);
    img.draw(0,0);
    mainFbo.draw(0,0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
