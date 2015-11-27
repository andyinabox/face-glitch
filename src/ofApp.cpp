#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofLogVerbose();

    img.load("hadley.jpg");
    pixelate.load("shaders/pixelate");
    fbo.allocate(img.getWidth(), img.getHeight());
    
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    gui.setup();
	gui.add(pixelWidth.setup("Pixel Width", 15.0, 0.0, 50.0));
	gui.add(pixelHeight.setup("Pixel Height", 15.0, 0.0, 50.0));
	gui.add(blend.setup("Blend", 1.0, 0.0, 1.0));
    
}

//--------------------------------------------------------------
void ofApp::update(){

    fbo.begin();
        pixelate.begin();
            pixelate.setUniform1f("width", ofGetWidth());
            pixelate.setUniform1f("height", ofGetHeight());
            pixelate.setUniform1f("pixel_w", pixelWidth);
            pixelate.setUniform1f("pixel_h", pixelHeight);

            pixelate.setUniform1f("blend", blend);


            img.draw(0,0);
        pixelate.end();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 0, 0);
    img.draw(0,0);
    fbo.draw(0,0);
    
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
