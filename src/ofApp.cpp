#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("hadley.jpg");
    pixelate.load("shaders/pixelate");
    fbo.allocate(img.getWidth(), img.getHeight());
    
    ofSetWindowShape(img.getWidth(), img.getHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
        pixelate.begin();
            float blendValue = ofMap(mouseX, 0, ofGetWidth(), 0.0, 1.0, true);
            pixelate.setUniform1f("blend", blendValue);
            img.draw(0,0);
        pixelate.end();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 0, 0);
    fbo.draw(0,0);
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
