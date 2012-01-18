#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{		
	ofSetFrameRate(60);
    ofSetVerticalSync(true);

	ofBackground(0,0,128);
    
    vidGrabber.initGrabber(WIDTH,HEIGHT);
    publicFbo.allocate(ofGetWidth(), ofGetHeight());
    privateFbo.allocate(ofGetWidth(), ofGetHeight());

	int winW=300;
    
    setupFensters();
    setupGUI();
}

    
void testApp::setupFensters(){
	//setup of fensterListener does not get called automatically yet
	publicWin.setup();
	privateWin.setup();

	//IF the following code is uncommented, all the following windows should be created on the second display, if there is one available
	/*ofxDisplayList displays = ofxDisplayManager::get()->getDisplays();
	ofxDisplay* disp = displays[0];
	if(displays.size() > 1)
		disp = displays[1];
	ofxFensterManager::get()->setActiveDisplay(disp);*/

    ofxFenster* win;
    
    // public window
    win = ofxFensterManager::get()->createFenster(ofGetScreenWidth()-WIDTH, 0, WIDTH, HEIGHT, OF_WINDOW);
    ofAddListener(win->events.mouseMoved, this, &testApp::mouseMovedEvent);
    win->addListener(&publicWin);
    win->setWindowTitle("public render");
	win->setBorder(false);
    
    // private window
    win = ofxFensterManager::get()->createFenster(ofGetScreenWidth()-WIDTH, HEIGHT, WIDTH, HEIGHT, OF_WINDOW);
    ofAddListener(win->events.mouseMoved, this, &testApp::mouseMovedEvent);
    win->addListener(&privateWin);
    win->setWindowTitle("private render");
//	win->setBorder(true);
    
    // Pot ser que aix˜ peti en windows
	ofImage icon;
	icon.loadImage("icon.png");
	ofxFensterManager::get()->setIcon(icon.getPixelsRef());
}

void testApp::setupGUI(){
    // GUI
    gui.addTitle("General");
    gui.addContent("Camera feed", vidGrabber);  
    
    //gui.loadFromXML();
    gui.show();
    
    
}


//--------------------------------------------------------------
void testApp::update()
{
    vidGrabber.grabFrame();
    
    // GUI
    framerate = ofGetFrameRate();
}

//--------------------------------------------------------------
void testApp::draw()
{
    // public render
    publicFbo.begin();
    // pinta el que vulguis a la finestra pœblica
    vidGrabber.draw(0,0);
    // ---
    publicFbo.end();
    publicWin.setFbo(publicFbo);
    
    // private render
    privateFbo.begin();
    // pinta el que vulguis a la finestra privada
    vidGrabber.draw(0,0);
    ofDrawBitmapString("QUE NO HO VEGI NINGU!", 20,20);
    // ---
    privateFbo.end();
    privateWin.setFbo(privateFbo);
    
    // GUI
	gui.draw();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
	//cout << (0x0400) << endl;
	//cout << (101 | OF_KEY_MODIFIER) << " " << key << endl;
	if(key=='f')
		ofxFensterManager::get()->getPrimaryWindow()->toggleFullscreen();
	if(key==' ')
//		ofxFensterManager::get()->createFenster(0, 0, 400, 300, OF_WINDOW)->addListener(&imgWin);
	if(key == 'c')
		cout << "CLIPBOARD DATA: " << ofxFensterManager::get()->getClipboard() << endl;
}

//this only works if testApp is extending ofxFensterListener and not ofBaseApp
void testApp::mouseMoved(int x, int y, ofxFenster* win)
{
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	mousePos.set(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	cout << "PRESSED" << endl;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	cout << "RELEASED" << endl;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
	cout << "GOT SOME FILES: "<<endl;
	std::vector<string>::iterator it = dragInfo.files.begin();
	while(it != dragInfo.files.end()){
		cout << *it << endl;
		++it;
	}
}

void testApp::mouseMovedEvent(ofMouseEventArgs &args)
{
	//cout << "MOUSE WAS MOVED" << endl;
}
