#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    // Load directory with images
    DIR.listDir("images");
    DIR.allowExt("jpg");
    DIR.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    //allocate the vector to have as many ofImages as files
    if( DIR.size() ){
        images.assign(DIR.size(), ofImage());
    }
    nImages = (int)DIR.size();
    currentImage = 0;
    image.load(DIR.getPath(0));
    DIR.sort();
    for (int i = 0; i < nImages; i++){
        cout << "images: ";
        cout << ofToString(i) << '/' << ofToString(DIR.getPath(i)) << '\n';
    }
    width = image.getWidth();
    height = image.getHeight();
    
    // Load directory with masks
    DIR_mask.listDir("mask");
    DIR_mask.allowExt("png");
    DIR_mask.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    //allocate the vector to have as many ofImages as files
    if( DIR_mask.size() ){
        masks.assign(DIR_mask.size(), ofImage());
    }
    nMasks = (int)DIR_mask.size();
    currentMask = 0;
    mask.load(DIR_mask.getPath(0));
    DIR_mask.sort();
    
    //Alpha
    ofEnableAlphaBlending();
    ofSetVerticalSync( true );
    
    //FBO
    fbo.allocate(width, height, GL_RGBA);
    savepix.allocate(width,height,GL_RGBA);
//    savepix.allocate(width,height,OF_IMAGE_COLOR_ALPHA);

    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    //Init a new layer / mask combo
    layer1 = masker.newLayer();
    layer2 = masker.newLayer();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    //  ofBackground(0);
        ofClear(ofColor(0,0,0,0));
//        image.draw(0,0,width,height);
    //    masker.beginLayer(layer1);
    //    {
    //
    //    }
    //    masker.endLayer(layer1);

        // předělat layery pro jejich překrytí ?
        for (int i = 0; i < nImages; i++){
            //Draw the layer
            masker.beginLayer(layer2);
            {
                image.load(DIR.getPath(i));
                ofClear(0, 0, 0, 255);
                image.draw(0,0,width,height);
                image.clear();
            }
            masker.endLayer(layer2);
            
            //Draw the mask
            masker.beginMask(layer2);
            {
                mask.load(DIR_mask.getPath(i));
                ofClear(0, 0, 0, 255);
                mask.draw(0,0,width,height);
                mask.clear();
            }
            masker.endMask(layer2);

            cout << "processing: ";
            cout << ofToString(i+1) << '/' << ofToString(nImages) << '\n';
            
            //Draw the combined result
            masker.draw();
        }
    
        fbo.readToPixels(savepix);
        ofSaveImage(savepix, "export/chain"+ofToString(int(ofRandom(0, 10000))) + ".png", OF_IMAGE_QUALITY_BEST);
    fbo.end();
    fbo.draw(0,0);
    ofExit() ;
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

// Functions

// Draws an image with fixed aspect ratio
void ofApp::drawImage(ofImage image, int x, int y, int w){
    float h = floor(w*(image.getHeight()/image.getWidth()));
    image.draw(x,y,w,h);
}
