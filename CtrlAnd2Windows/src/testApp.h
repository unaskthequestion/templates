#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxSimpleGuiToo.h"

#define WIDTH 640
#define HEIGHT 480

#define NUM_MODULES 3

// Una classe de finestra que rep i pinta FBOs
class imageWindow: public ofxFensterListener {
public:
	~imageWindow() {
		cout << "Image Listener destroyed" << endl;
	}
	void setup() {
        fbo.allocate(WIDTH, HEIGHT);
        
	}
	void draw() {
		fbo.draw(0,0);
        
	}

    void setFbo(ofFbo & f){
        fbo = f;
    }
    
	ofFbo fbo;
};

class testApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
    
    // setup
    void setupFensters();
    void setupGUI();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseMoved(int x, int y, ofxFenster* win);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void mouseMovedEvent(ofMouseEventArgs &args);

	ofVec2f mousePos;
	imageWindow publicWin, privateWin; // les finestres pœblica i privada
    
    ofVideoGrabber  vidGrabber;
    ofFbo           publicFbo, privateFbo; // per enviar a les finestres
    
    // GUI
    float framerate;
};
