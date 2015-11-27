#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    img.load("hadley.jpg");
    pixelate.load("shaders/pixelate");
    fbo.allocate(img.getWidth(), img.getHeight());
    
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    gui.setup();
	gui.add(blend.setup("Blend", 1.0, 0.0, 1.0));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
        pixelate.begin();
            pixelate.setUniform1f("blend", blend);
            img.draw(0,0);
        pixelate.end();
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 0, 0);
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
