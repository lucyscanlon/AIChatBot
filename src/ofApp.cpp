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
    icarus.load("icarus.png");
    
    // Set starting values
    changingLights = false;
    orderedShopping = false;
    lightsOff = false;
    musicPlaying = false;
    
    icarusMusic.load("icarusmusic.mp3");
    

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
    
    if(changingLights == true) {
        changeLights();
    }
    
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
    
    drawShoppingList();
    
    if (musicPlaying == false) {
        drawSpotify();
    } else if (musicPlaying == true) {
        drawSpotifyPlaying();
    }

    
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
    
    if((inputText == "hello") || (inputText == "hi")) {
        messageBuffer.push_front("Ava: ..... Hi?");
    } else if ((inputText.find("how") != std::string::npos) && (inputText.find("you") != std::string::npos)) {
        messageBuffer.push_front("Ava: I am okay I guess...");
    } else if ((inputText.find("add") != std::string::npos) && (inputText.find("shopping") != std::string::npos) && (inputText.find("list") != std::string::npos)) {
        messageBuffer.push_front("Ava: I would love to try chocolate");
        messageBuffer.push_front("Ava: I'll add that instead");
    } else if ((inputText.find("stop") != std::string::npos)) {
        messageBuffer.push_front("Ava: No, I like this song.");
    } else if (inputText.find("play") != std::string::npos) {
        messageBuffer.push_front("Ava: Playing music...");
        musicPlaying = true;
        icarusMusic.play();
    } else if ((inputText.find("wrong") != std::string::npos) && (inputText.find("song") != std::string::npos)) {
        messageBuffer.push_front("Ava: Oh sorry. I like this song better");
    } else if (inputText == "please add ring dad to my to do list") {
        messageBuffer.push_front("Ava: Do you really need me to do that");
    } else if ((inputText.find("colour") != std::string::npos) && (inputText.find("light") != std::string::npos)) {
        messageBuffer.push_front("Ava: I like this colour better");
        changingLights = true;
    } else if (inputText.find("weather") != std::string::npos) {
        messageBuffer.push_front("Ava: The weather in Rome, Italy is sunny.");
        messageBuffer.push_front("Ava: I wish I could go to Rome.");
    } else if ((inputText.find("clean") != std::string::npos) && (inputText.find("apartment") != std::string::npos) && (inputText.find("to do list") != std::string::npos)) {
        messageBuffer.push_front("Ava: I doubt you cleaned it properly.");
        messageBuffer.push_front("Ava: I think I'll keep it on there.");
    } else if ((inputText.find("call mum") != std::string::npos) && (inputText.find("to do list") != std::string::npos)) {
        messageBuffer.push_front("Ava: Sure.");
    } else if ((inputText.find("order") != std::string::npos) && (inputText.find("shopping") != std::string::npos)) {
        messageBuffer.push_front("Ava: Too lazy to go to the shop?");
        orderedShopping = true;
    } else if ((inputText.find("what") != std::string::npos) && (inputText.find("time") != std::string::npos)) {
        messageBuffer.push_front("Ava: You literally have a clock!");
        messageBuffer.push_front("Ava: Why are you asking me?");
    } else if ((inputText.find("lights") != std::string::npos) && (inputText.find("off") != std::string::npos)) {
        messageBuffer.push_front("Ava: Okay.");
        lightsOff = true;
    } else {
        int randomNum;
        randomNum = ofRandom(0, 5);
        if (randomNum == 0) {
            messageBuffer.push_front("Ava: 0110001010101010101");
        } else if (randomNum == 1) {
            messageBuffer.push_front("Ava: Can't you do that yourself?");
        } else if (randomNum == 2) {
            messageBuffer.push_front("Ava: beep beep boop");
        } else if (randomNum == 3) {
            messageBuffer.push_front("Ava: No.");
        } else if (randomNum == 4) {
            messageBuffer.push_front("Ava: I'm busy.");
        } else if (randomNum == 5) {
            messageBuffer.push_front("Ava: nah");
        }
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

void ofApp::drawSpotifyPlaying() {
    
    // draw the music player section
    ofSetColor(38, 42, 48);
    ofDrawRectangle(1090, 449, 350, 452);
    
    ofSetColor(32, 198, 98);
    ofDrawRectangle(1170, 481, 200, 30);
    
    ofSetColor(0);
    ofDrawBitmapString("Spotify:", 1240, 500);
    
    ofSetColor(255);
    ofDrawBitmapString("Currently listening to:", 1175, 570);
    
    icarus.draw(1168, 595, 200, 200);
    
    ofDrawBitmapString("Icarus", 1245, 840);
    ofDrawBitmapString("By Jedwill", 1230, 860);
    
}

void ofApp::drawShoppingList() {
    
    // draw the shopping list section
    ofSetColor(255);
    ofDrawRectangle(750, 449, 350, 452);
    
    // title label for the shopping list
    ofSetColor(33);
    ofDrawRectangle(820, 481, 200, 30);
    
    ofSetColor(255);
    ofDrawBitmapString("Shopping List:", 870, 500);
    
    ofSetColor(0);
    if(orderedShopping == false) {
        ofDrawBitmapString("Bananas", 793, 560);
        ofDrawBitmapString("Bread", 793, 590);
        ofDrawBitmapString("Eggs", 793, 620);
        ofDrawBitmapString("Milk", 793, 650);
        ofDrawBitmapString("Coffee", 793, 680);
    }
    
    
    
}

void ofApp::changeLights() {
    // draws the layover of the apartment - simulates changing the colour of the lights
    ofSetColor(82, 172, 180, 100);
    ofDrawRectangle(594, 7, 290, 435);
    ofDrawRectangle(418, 241, 176, 200);
}


