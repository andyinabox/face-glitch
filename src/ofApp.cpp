#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableSmoothing();

    bShowHud = true;

    // load image
    img.load("emir_of_bukhara.jpg");
    
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
    
    // clear out the fbos
    clearPaintFbo();
    clearMaskFbo();
    
    // set window size
    ofSetWindowShape(img.getWidth(), img.getHeight());
    
    // setup gui
    gui.setup();
	gui.add(pixelWidth.setup("Pixel Width", 15.0, 0.0, 50.0));
	gui.add(pixelHeight.setup("Pixel Height", 15.0, 0.0, 50.0));
	gui.add(brushRadius.setup("BrushRadius", 25.0, 1.0, 100.0));
	gui.add(blend.setup("Blend", 1.0, 0.0, 1.0));
    
    gui.add(animationLabel.setup("Animation", ""));
    gui.add(enableAnimation.setup("Enable animation", false));
    gui.add(animSpeed.setup("Animation speed", 1000.0, 1.0, 10000.0));

}

//--------------------------------------------------------------
void ofApp::update(){

    maskFbo.begin();
        paintFbo.draw(0,0);
    maskFbo.end();

    mainFbo.begin();
        ofClear(0);
        pixelate.begin();
            pixelate.setUniformTexture("src", img.getTexture(), 1);
            pixelate.setUniformTexture("mask", maskFbo.getTexture(), 2);
    
            pixelate.setUniform1f("width", ofGetWidth());
            pixelate.setUniform1f("height", ofGetHeight());
            pixelate.setUniform1f("t", ofGetElapsedTimeMillis());

            pixelate.setUniform1f("pixel_w", pixelWidth);
            pixelate.setUniform1f("pixel_h", pixelHeight);
    
            pixelate.setUniform1i("animation", enableAnimation ? 1 : 0);
            pixelate.setUniform1f("animSpeed", animSpeed);

            pixelate.setUniform1f("blend", blend);

            img.draw(0,0);
        pixelate.end();
    mainFbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0);

    // draw image
    img.draw(0,0);
    
    // draw fbo over image
    mainFbo.draw(0,0);
    
    // draw mask if requested
    if(bDrawMask) {
        maskFbo.draw(0,0);
    }
    
    // draw brush
    ofPushStyle();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 244, 100);
        // draw paint fbo
        paintFbo.draw(0,0);
    
        // draw brush outline
        ofNoFill();
        ofDrawEllipse(mouseX, mouseY, brushRadius, brushRadius);
    ofPopStyle();
    
    // draw gui
    gui.draw();
    
    if(bShowHud) {
        string hud = "Press 'c' to clear \nPress 'm' to show mask\nPress 'h' to show/hide this\n";
        ofDrawBitmapString(hud, ofGetWidth()-300, 15);
    }
}


void ofApp::updatePaintFbo(int x, int y) {
    paintFbo.begin();
        ofClear(0);
        ofDrawEllipse(x, y, brushRadius, brushRadius);
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
    if(key == 'c') {
        ofLogVerbose("Clear mask");
        clearMaskFbo();
    } else if (key == 'm') {
        bDrawMask = true;
    } else if (key == 'h') {
        bShowHud = !bShowHud;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    bDrawMask = false;
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
