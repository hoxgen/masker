#pragma once

#include "ofMain.h"
#include "ofxLayerMask.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
        ofxLayerMask masker;
        int width, height;
        int layer1, layer2;
    
        // Function for drawing images
        void drawImage(ofImage image, int x, int y, int w);
		
    
        // we will have a dynaimic number of images, based on the content of a directory:
        int  nImages;
//        ofImage * images;
        ofDirectory DIR;
        vector<ofImage> images;
        int currentImage;
    
        // and masks
        int  nMasks;
        vector<ofImage> masks;
        ofDirectory DIR_mask;
        int currentMask;
    
        //images
        ofImage pix, image, mask;
    
        //FBO
        ofFbo fbo;
        ofPixels savepix;
    
};
