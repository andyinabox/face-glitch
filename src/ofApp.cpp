#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // some global configuration for oF
    // show all logging info
    ofSetLogLevel(OF_LOG_VERBOSE);
    // enable anti-aliasing on OpenGL stuff
    ofEnableSmoothing();

    // show HUD by default
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

    // draw the paint FBO to the mask every frame
    // (notice that we aren't clearing the fbo, so it accumulates)
    maskFbo.begin();
        paintFbo.draw(0,0);
    maskFbo.end();

    // draw to the main FBO
    mainFbo.begin();
        // gesso the canvas so we can paint a new frame
        ofClear(0);
    
        // draw to the pixelate shader
        pixelate.begin();
    
            // set uniforms for our shader!
    
            // send textures to pixelate shader
            pixelate.setUniformTexture("src", img.getTexture(), 1);
            pixelate.setUniformTexture("mask", maskFbo.getTexture(), 2);
    
            // these give basic information about our environment
            // (many shader tools will provide these automatically
            pixelate.setUniform1f("width", ofGetWidth());
            pixelate.setUniform1f("height", ofGetHeight());
            pixelate.setUniform1f("t", ofGetElapsedTimeMillis());

            // pixel width and height parameters
            pixelate.setUniform1f("pixel_w", pixelWidth);
            pixelate.setUniform1f("pixel_h", pixelHeight);
    
            // animation parameters
            pixelate.setUniform1i("animation", enableAnimation ? 1 : 0);
            pixelate.setUniform1f("animSpeed", animSpeed);

            // this will control the amount "wetness" of the filter
            // (how much it is blended)
            pixelate.setUniform1f("blend", blend);

            // draw our image in the shader context
            // this will by default send a texture uniform `tex0` which
            // we aren't currently using. it will also provide texture
            // coordinates to the shader (i think)
            img.draw(0,0);
        pixelate.end();
    mainFbo.end();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // clear the canvas before w paint a new frame
    ofClear(0);

    // draw the image at coordinates 0, 0
    img.draw(0,0);
    
    // draw fbo over image (any opacity in the main Fbo will let the
    // image show through)
    mainFbo.draw(0,0);
    
    // draw mask if enabled
    if(bDrawMask) {
        maskFbo.draw(0,0);
    }
    
    // draw brush
    // `ofPushStyle` allows us to set styles without
    // having them applied to the rest of the application
    ofPushStyle();
        // set color to be white with partial transparency
        ofSetColor(255, 255, 255, 100);
    
        // draw paint fbo
        paintFbo.draw(0,0);
    
        // draw brush outline
        ofNoFill();
        ofDrawEllipse(mouseX, mouseY, brushRadius, brushRadius);
    
    ofPopStyle();
    
    // draw gui
    gui.draw();
    
    // draw the HUD if enabled
    if(bShowHud) {
        string hud = "Press 'c' to clear \n";
        hud = hud + "Press 'm' to show mask\n";
        hud = hud + "Press 'h' to show/hide this\n";
        ofDrawBitmapString(hud, ofGetWidth()-300, 25);
    }
}


void ofApp::updatePaintFbo(int x, int y) {
    paintFbo.begin();
        ofClear(0);
        // draw an ellipse to the paint fbo at the mouse position
        ofDrawEllipse(x, y, brushRadius, brushRadius);
    paintFbo.end();
}

void ofApp::clearPaintFbo() {

    // clear out the paint fbo
    paintFbo.begin();
        ofClear(0);
    paintFbo.end();
}
void ofApp::clearMaskFbo() {

    // clear out the mask fbo
    maskFbo.begin();
        ofClear(0);
    maskFbo.end();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // clear the mask if "c" key is pressed
    if(key == 'c') {
        clearMaskFbo();
        
    // show the mask if "m" key is pressed
    } else if (key == 'm') {
        bDrawMask = true;
        
    // toggle the HUD if "h" key is pressed
    } else if (key == 'h') {
        bShowHud = !bShowHud;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    // disable mask display
    bDrawMask = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // update paint fbo when mouse is dragged
    updatePaintFbo(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // update paint fbo when mouse is pressed
    updatePaintFbo(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // clear paint fbo when mouse is released
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
