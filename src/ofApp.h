#pragma once

#include "ofMain.h"
#include "ofxGui.h"
using namespace std;

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
    
    // parrot bot
    void parrotBot(string inputText);
    
    // function which takes in the user input
    void onTextChange(string& text);
    
    
    ofxGuiGroup gui;
    deque<string> messageBuffer;
    float lineHeight;
    ofParameterGroup parameters;
    ofParameter<string> textParameter;
    
    // load the image of the apartment
    ofImage apartment;
		
};
