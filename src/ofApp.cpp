#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);

    // load image
    img.load("hadley.jpg");
    
    // load shaders
    pixelate.load("shaders/pixelate");
    mask.load("shaders/mask");
    
    // setup fbos
    ofFbo::Settings fboSettings;
    fboSettings.width = img.getWidth();
    fboSettings.height = img.getHeight();
    mainFbo.allocate(fboSettings);
    maskFbo.allocate(fboSettings);
    paintFbo.allocate(fboSettings);
    maskTexture = maskFbo.getTexture();
    
    // clear out the fbos
    clearPaintFbo();
    clearMaskFbo();
    
    // set window size
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    // setup gui
    gui.setup();
	gui.add(pixelWidth.setup("Pixel Width", 15.0, 0.0, 50.0));
	gui.add(pixelHeight.setup("Pixel Height", 15.0, 0.0, 50.0));
	gui.add(blend.setup("Blend", 1.0, 0.0, 1.0));

}

//--------------------------------------------------------------
void ofApp::update(){

    maskFbo.begin();
//        ofClear(0);
//        mask.begin();
//            mask.setUniformTexture("paint", paintFbo.getTexture(), 1);
//            mask.setUniformTexture("mask", maskTexture, 2);
//            mask.setUniform1i("eraser", useEraser);
//            img.draw(0,0);
//        mask.end();
        paintFbo.draw(0,0);
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
//    maskFbo.draw(0,0);
    ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 244, 100);
        paintFbo.draw(0,0);
    ofPopStyle();
    gui.draw();
}


void ofApp::updatePaintFbo(int x, int y) {
    paintFbo.begin();
        ofClear(0);
        ofDrawEllipse(x, y, 50, 50);
    paintFbo.end();
}

void ofApp::clearPaintFbo() {
    paintFbo.begin();
        ofClear(0);
    paintFbo.end();
}
void ofApp::clearMaskFbo() {
    maskFbo.begin();
        ofClear(0);
    maskFbo.end();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == OF_KEY_ALT) {
//        ofLogVerbose("Use eraser!");
//        useEraser = 1;
//    }

    if(key == 'c') {
        clearMaskFbo();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
//    useEraser = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    updatePaintFbo(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    updatePaintFbo(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    clearPaintFbo();
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
