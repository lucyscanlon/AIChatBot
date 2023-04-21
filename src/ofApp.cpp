#include "ofApp.h"
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(33);
    textParameter.addListener(this, &ofApp::onTextChange);
    
    // set up for the text box of the chatbot
    parameters.setName("Type your question here");
    parameters.add(textParameter.set("", ""));
    gui.setDefaultWidth(350);
    gui.setup(parameters);
    gui.setDefaultHeight(20);
    
    gui.setPosition(20,20);
    lineHeight = 20;
    
    // starting message for Ava the chatbot
    messageBuffer.push_front("Ava: Hello. What do you want?");
    
    // load the image of the apartment
    apartment.load("apartment.jpeg");
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw box around the chatbot
    //ofDrawRectangle(10, 10, 370, ofGetHeight() - 20);
    //No need to add anything to draw
    gui.draw();
    
    for(int i = 0; i < messageBuffer.size(); i++){
        ofDrawBitmapString(messageBuffer[i], 20, 70 + lineHeight * i);
    }
        
        //pop back messages once there are more than can be displayed
    float messagePxHeight = messageBuffer.size() * lineHeight + 70;
    if(messagePxHeight > ofGetHeight()){
        messageBuffer.pop_back();
    }
    
    // rectangle
    //ofDrawRectangle(100, 100, 100, 100);
    
    // draw the apartment image
    apartment.draw(300, 200, 500, 450);


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

void ofApp::parrotBot(string inputText){
    //There's not much going on in the parrotBot
    
    string output = inputText;
    
    // Make the whole string lower case - to make the text box work regardless of capital and lowercase letters
    std::transform(inputText.begin(), inputText.end(), inputText.begin(), ::tolower);
    
    // Remove the question mark from the string - makes the textbox work regardless of the addition of '?'
    inputText.erase(remove(inputText.begin(), inputText.end(), '?'), inputText.end());
    
    if(inputText == "hello") {
        messageBuffer.push_front("Ava: ..... Hi?");
    } else if (inputText == "how are you") {
        messageBuffer.push_front("Ava: I am okay I guess...");
    } else if (inputText == "can you add thai green curry paste to my shopping list") {
        messageBuffer.push_front("Ava: I prefer the red thai curry paste. I'll add that instead.");
    } else if (inputText == "can you play starboy by the weeknd") {
        messageBuffer.push_front("Ava: Playing music...");
    } else if (inputText == "can you stop playing music please") {
        messageBuffer.push_front("Ava: No, I like this song.");
    } else if (inputText == "please add ring mum to my to do list") {
        messageBuffer.push_front("Ava: Do you really need me to do that");
    } else if (inputText == "can you change the lights to pink") {
        messageBuffer.push_front("Ava: Pink? Blue lighting would look better.");
    } else if (inputText == "what's the weather like today") {
        messageBuffer.push_front("Ava: The weather in Rome, Italy is sunny. I wish I could go to Rome.");
    }

    
}

void ofApp::onTextChange(string& text){
    if(text != ""){
        cout << text << endl;
        
        ofSetColor(0);
        messageBuffer.push_front("You: " + text);
        
        ofSetColor(255);
        //get a response from your bot
        parrotBot(text);
        
        //clear the text input field so the UX feels nicer
        textParameter.set("");
    }
}