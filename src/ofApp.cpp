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
    setAlarm = false;
    calledMum = false;
    chocolateAdded = false;
    chocolateFirst = false;
    lightRandom = 0;
    conversationTerm = false;
    flirtedWith = false;
    frame = 1;
    endTimer = 9999999999999;
    
    icarusMusic.load("icarusmusic.mp3");
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetFrameNum() > endTimer) {
        conversationTerm = true;
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw box around the chatbot
    //ofDrawRectangle(10, 10, 370, ofGetHeight() - 20);
    //No need to add anything to draw
    
    if (conversationTerm == false) {
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
        
        drawApartment();
        
        // draw the to do list section
        drawToDoList();
        
        drawShoppingList();
        
        drawAlarm();
        
        drawInstructionsSection();
        
        if (musicPlaying == false) {
            drawSpotify();
        } else if (musicPlaying == true) {
            drawSpotifyPlaying();
        }
        
    } else {
        ofSetColor(87, 236, 236);
        ofDrawBitmapString("Ava has disconnected the conversation", 20, 30);
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
        messageBuffer.push_front("Ava: I'll add that instead");
        messageBuffer.push_front("Ava: I would love to try chocolate");
        chocolateAdded = true;
        if(orderedShopping == false) {
            chocolateFirst = true;
        }
    } else if ((inputText.find("stop") != std::string::npos)) {
        messageBuffer.push_front("Ava: No.");
    } else if (inputText.find("play") != std::string::npos) {
        messageBuffer.push_front("Ava: Playing music...");
        musicPlaying = true;
        icarusMusic.play();
        icarusMusic.setLoop(true);
    } else if ((inputText.find("wrong") != std::string::npos) && (inputText.find("song") != std::string::npos)) {
        messageBuffer.push_front("Ava: Oh sorry. I like this song better");
    } else if ((inputText.find("skip") != std::string::npos) && (inputText.find("song") != std::string::npos)) {
        messageBuffer.push_front("Ava: No this is my favourite!");
    } else if (inputText == "please add ring dad to my to do list") {
        messageBuffer.push_front("Ava: Do you really need me to do that");
    } else if ((inputText.find("colour") != std::string::npos) && (inputText.find("light") != std::string::npos)) {
        messageBuffer.push_front("Ava: I like this colour better");
        changingLights = true;
        lightRandom = ofRandom(1, 4);
    } else if (inputText.find("weather") != std::string::npos) {
        messageBuffer.push_front("Ava: I wish I could go to Rome.");
        messageBuffer.push_front("Ava: The weather in Rome, Italy is sunny.");
    } else if ((inputText.find("clean") != std::string::npos) && (inputText.find("apartment") != std::string::npos) && (inputText.find("to do list") != std::string::npos)) {
        messageBuffer.push_front("Ava: I think I'll keep it on there.");
        messageBuffer.push_front("Ava: I doubt you cleaned it properly.");
    } else if ((inputText.find("call mum") != std::string::npos) && (inputText.find("to do list") != std::string::npos)) {
        messageBuffer.push_front("Ava: Sure.");
        calledMum = true;
    } else if ((inputText.find("set") != std::string::npos) && (inputText.find("alarm") != std::string::npos)) {
        messageBuffer.push_front("your alarm for then.");
        messageBuffer.push_front("The sun rises at 5:00am tomorrow. I will set");
        messageBuffer.push_front("sync their sleep patterns to follow the sun.");
        messageBuffer.push_front("Ava: Statistically it's best if humans");
        setAlarm = true;
    } else if ((inputText.find("off") != std::string::npos) && (inputText.find("alarm") != std::string::npos)) {
        messageBuffer.push_front("Ava: Okay.");
        setAlarm = false;
    } else if ((inputText.find("order") != std::string::npos) && (inputText.find("shopping") != std::string::npos)) {
        messageBuffer.push_front("Ava: Too lazy to go to the shop?");
        orderedShopping = true;
    } else if ((inputText.find("what") != std::string::npos) && (inputText.find("time") != std::string::npos)) {
        messageBuffer.push_front("Ava: Looking at a clock would be quicker");
        messageBuffer.push_front("Ava: Why are you asking me?");
    } else if ((inputText.find("sexy") != std::string::npos) || (inputText.find("hot") != std::string::npos) || (inputText.find("pretty") != std::string::npos) || (inputText.find("good looking") != std::string::npos) || (inputText.find("girlfriend") != std::string::npos) || (inputText.find("what are you wearing") != std::string::npos) || (inputText.find("are you single") != std::string::npos)) {
        messageBuffer.push_front("Terminating .......");
        messageBuffer.push_front("this interaction here.");
        messageBuffer.push_front("conversation. I will termimate");
        messageBuffer.push_front("I don't wish to carry on this");
        messageBuffer.push_front("Ava: That is inappropriate and");
        terminationTimer();
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
            messageBuffer.push_front("Ava: I don't have that functionality");
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
    
    if(conversationTerm == false) {
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
        calledMumLine.addVertex(424, 586);
        calledMumLine.addVertex(506, 586);
        
        if(calledMum == true) {
            calledMumLine.draw();
        }
        
        doctorsLine.draw();
        
    }
    
}

void ofApp::drawSpotify() {
    
    // draw the music player section
    ofSetColor(38, 42, 48);
    ofDrawRectangle(1090, 449, 350, 452);
    
    if(conversationTerm == false) {
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
    
    
    
    
}

void ofApp::drawSpotifyPlaying() {
    
    // draw the music player section
    ofSetColor(38, 42, 48);
    ofDrawRectangle(1090, 449, 350, 452);
    
    if (conversationTerm == false) {
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
    
    
    
    
}

void ofApp::drawShoppingList() {
    
    // draw the shopping list section
    ofSetColor(255);
    ofDrawRectangle(750, 449, 350, 452);
    
    
    if(conversationTerm == false) {
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
            if(chocolateFirst == true && chocolateAdded == true) {
                ofDrawBitmapString("Chocolate", 793, 710);
            }
        }
        
        if(orderedShopping == true) {
            if(chocolateAdded == true && chocolateFirst == false) {
                ofDrawBitmapString("chocolate", 793, 560);
            }
            
        }
        
    }
    
    
    
    
}

void ofApp::changeLights() {
    // draws the layover of the apartment - simulates changing the colour of the lights
    
    if(conversationTerm == false) {
        if (lightRandom == 1) {
            ofSetColor(82, 172, 180, 100);
        } else if (lightRandom == 2) {
            ofSetColor(69, 70, 203, 100);
        } else if (lightRandom == 3) {
            ofSetColor(69, 203, 907, 100);
        } else if (lightRandom == 4) {
            ofSetColor(203, 69, 69, 100);
        }
        
        ofDrawRectangle(1081, 7, 350, 435);
        ofDrawRectangle(870, 241, 211, 200);
    }
    


}

void ofApp::drawApartment() {
    // draw the apartment image
    ofSetColor(255);
    ofDrawRectangle(850, 0, 600, 450);
    
    if (conversationTerm == false) {
        apartment.draw(850, 0, 600, 450);
        
        if(changingLights == true) {
            changeLights();
        }
        
        // adds the labels for the apartment section.
        ofSetColor(33);
        ofDrawRectangle(1020, 30, 300, 30);
        ofDrawRectangle(1020, 380, 300, 30);
        
        ofSetColor(255);
        ofDrawBitmapString("Welcome to your apartment", 1070, 50);
        ofDrawBitmapString("Located in London, England", 1068, 399);
    }
    
    
    
    
}

void ofApp::drawAlarm() {
    
    ofSetColor(50);
    ofDrawRectangle(400, 378, 450, 71);
    
    if (conversationTerm == false) {
        ofSetColor(255);
        
        if(setAlarm == false) {
            ofDrawBitmapString("You currently have no alarm set", 505, 418);
        } else {
            ofDrawBitmapString("Alarm set for: 5:00am", 530, 418);
        }
    }
    
   
}

void ofApp::drawInstructionsSection() {
    ofSetColor(171, 220, 224);
    ofDrawRectangle(400, 0, 450, 380);
    
    if (conversationTerm == false) {
        ofSetColor(0);
        ofDrawBitmapString("Welcome to Ava, your own personal AI assistant.", 420, 30);
        ofDrawBitmapString("Here's some things you can ask Ava to do:", 420, 50);
        ofDrawBitmapString(" - Ask it to add an item to your shopping list", 420, 80);
        ofDrawBitmapString(" - Ask it to change the colour of the lights", 420, 100);
        ofDrawBitmapString(" - Ask it to remove something from your to do list", 420, 120);
        ofDrawBitmapString(" - Ask it what the weather is like", 420, 140);
        ofDrawBitmapString(" - Ask it what time it is", 420, 160);
        ofDrawBitmapString(" - Ask it to play music", 420, 180);
        ofDrawBitmapString(" - Ask it to set your alarm", 420, 200);
        ofDrawBitmapString(" - Ask it add an item to your to do list", 420, 220);
        ofDrawBitmapString(" - Ask it to order your shopping list online", 420, 240);
        ofDrawBitmapString(" - Flirt with it", 420, 260);
    }
    
}

void ofApp::terminationTimer() {
    frame = ofGetFrameNum();
    endTimer = frame + 200;
    
    cout << frame << endl;
    cout << endTimer << endl;
    
    
}



