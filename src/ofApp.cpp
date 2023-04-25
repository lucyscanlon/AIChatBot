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
    lineHeight = 25;
    
    ofSetColor(87, 236, 236);
    // starting message for Ava the chatbot
    messageBuffer.push_front("Ava: Hello. What do you want?");
    
    // load the image of the apartment
    apartment.load("apartment.jpeg");
    
    spotifyNotPlaying.load("nomusic.png");
    

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
    
    ofSetColor(87, 236, 236);
    for(int i = 0; i < messageBuffer.size(); i++){
        ofDrawBitmapString(messageBuffer[i], 20, 80 + lineHeight * i);
    }
        
        //pop back messages once there are more than can be displayed
    float messagePxHeight = messageBuffer.size() * lineHeight + 70;
    if(messagePxHeight > ofGetHeight()){
        messageBuffer.pop_back();
    }
    
    // rectangle
    //ofDrawRectangle(100, 100, 100, 100);
    
    // draw the apartment image
    ofSetColor(255);
    ofDrawRectangle(400, 0, ofGetWidth() - 400, ofGetHeight());
    apartment.draw(400, 0, 500, 450);
    
    // draws the layover of the apartment - simulates changing the colour of the lights
    ofSetColor(87, 209, 236, 100);
    ofDrawRectangle(594, 7, 290, 435);
    ofDrawRectangle(418, 241, 176, 200);
    
    // adds the labels for the apartment section.
    ofSetColor(33);
    ofDrawRectangle(500, 30, 300, 30);
    ofDrawRectangle(500, 380, 300, 30);
    
    ofSetColor(255);
    ofDrawBitmapString("Welcome to your apartment", 550, 50);
    ofDrawBitmapString("Located in London, England", 550, 399);
    
    
    // draw the example questions box
    ofSetColor(105, 170, 178);
    ofDrawRectangle(0, 600, 400, 300);
    
    ofSetColor(0);
    ofDrawBitmapString("Questions to ask Ava:", 16, 623);
    
    // draw the to do list section
    drawToDoList();
    
    // draw the shopping list section
    ofSetColor(255);
    ofDrawRectangle(750, 449, 350, 452);
    
    // title label for the shopping list
    ofSetColor(33);
    ofDrawRectangle(820, 481, 200, 30);
    
    ofSetColor(255);
    ofDrawBitmapString("Shopping List:", 870, 500);
    
    drawSpotify();
    
    
    // displays the position of the mouse
    string pixelCoords = "("+to_string(mouseX)+", "+to_string(mouseY)+")";  // creates a string with pixel position
    ofSetColor(255,0,255);     // set text color
    ofDrawBitmapString(pixelCoords, mouseX, mouseY); // write text with pixel position following the mouse
    


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
        
        ofSetColor(87, 236, 236);
        //get a response from your bot
        parrotBot(text);
        
        //clear the text input field so the UX feels nicer
        textParameter.set("");
    }
}

void ofApp::drawToDoList() {
    
    // function to draw the to do list
    ofSetColor(40);
    ofDrawRectangle(400, 449, 350, 452);
    
    // title label for the to do list
    ofSetColor(255);
    ofDrawRectangle(476, 481, 200, 30);
    ofSetColor(0);
    ofDrawBitmapString("To Do List:", 538, 500);
    
    ofSetColor(255);
    ofDrawBitmapString("Clean the apartment", 433, 560);
    ofDrawBitmapString("Call mum", 433, 590);
    ofDrawBitmapString("Book doctors appointment", 433, 620);
    
    doctorsLine.addVertex(425, 616);
    doctorsLine.addVertex(630, 616);
    
    doctorsLine.draw();
}

void ofApp::drawSpotify() {
    
    // draw the music player section
    ofSetColor(38, 42, 48);
    ofDrawRectangle(1090, 449, 350, 452);
    
    ofSetColor(32, 198, 98);
    ofDrawRectangle(1170, 481, 200, 30);
    
    ofSetColor(0);
    ofDrawBitmapString("Spotify:", 1240, 500);
    
    ofSetColor(255);
    ofDrawBitmapString("Currently listening to:", 1175, 570);
    
    spotifyNotPlaying.draw(1168, 595, 200, 200);
    
    ofDrawBitmapString("You are currently not listening", 1150, 840);
    ofDrawBitmapString("to any music", 1220, 860);
    
    
}
