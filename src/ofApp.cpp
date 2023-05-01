#include "ofApp.h"
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // set frame rate and backround
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
    
    // load music
    icarusMusic.load("icarusmusic.mp3");
    
    // load font
    newFont.load("sans-serif.ttf", 8);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // works as a timer to trigger the termination of the conversation
    // when the chatbot is flirted with
    if(ofGetFrameNum() > endTimer) {
        conversationTerm = true;
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // check if the conversation has been terminated if not then draw the application
    if (conversationTerm == false) {
        gui.draw();
        
        // draw the chatlog
        ofSetColor(87, 236, 236);
        for(int i = 0; i < messageBuffer.size(); i++){
            ofDrawBitmapString(messageBuffer[i], 20, 80 + lineHeight * i);
        }
            
        // pop back chatlog messages when there are more then can be displayed
        float messagePxHeight = messageBuffer.size() * lineHeight + 70;
        if(messagePxHeight > ofGetHeight()){
            messageBuffer.pop_back();
        }
        

        // call functions to draw the elements of the application
        
        drawApartment();
        
        drawToDoList();
        
        drawShoppingList();
        
        drawAlarm();
        
        drawInstructionsSection();
        
        // play music the chatbot has been asked to
        if (musicPlaying == false) {
            drawSpotify();
        } else if (musicPlaying == true) {
            drawSpotifyPlaying();
        }
        
    } else {
        // if the chatbot has been flirted with and the conversation has been ended
        // then only display this message
        ofSetColor(87, 236, 236);
        ofDrawBitmapString("Ava has disconnected the conversation", 20, 30);
    }
    

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

void ofApp::chatBot(string inputText){
    
    string output = inputText;
    
    // Make the whole string lower case - to make the text box work regardless of capital and lowercase letters
    std::transform(inputText.begin(), inputText.end(), inputText.begin(), ::tolower);
    
    // Remove the question mark from the string - makes the textbox work regardless of the addition of '?'
    inputText.erase(remove(inputText.begin(), inputText.end(), '?'), inputText.end());
    
    // check the inputted text for key words to give a reponse that makes sense and is appropriate for
    // the question asked by the user
    // Trigger certain bools to control interactive elements of the application
    // replicates the user asking the AI and it interpreting and responding
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
        // if the inputted text does not match anything above
        // then respond with one of these phrases
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
        chatBot(text);
        
        //clear the text input field so the UX feels nicer
        textParameter.set("");
    }
}

void ofApp::drawToDoList() {
    
    // function to draw the to do list
    ofSetColor(40);
    ofDrawRectangle(400, 449, 350, 452);
    
    if(conversationTerm == false) {
        ofSetColor(255);
        ofDrawRectangle(476, 481, 200, 30);
        ofSetColor(0);
        newFont.drawString("To Do List:", 538, 500);
        
        ofSetColor(255);
        newFont.drawString("Clean the apartment", 433, 560);
        newFont.drawString("Call mum", 433, 590);
        newFont.drawString("Book doctors appointment", 433, 620);
        
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
        newFont.drawString("Spotify:", 1240, 500);
        
        ofSetColor(255);
        newFont.drawString("Currently listening to:", 1200, 570);
        
        spotifyNotPlaying.draw(1168, 595, 200, 200);
        
        newFont.drawString("You are currently not listening", 1180, 840);
        newFont.drawString("to any music", 1230, 860);
    }
    
    
    
    
}

void ofApp::drawSpotifyPlaying() {
    
    // draw the music player section if music is playing
    ofSetColor(38, 42, 48);
    ofDrawRectangle(1090, 449, 350, 452);
    
    if (conversationTerm == false) {
        ofSetColor(32, 198, 98);
        ofDrawRectangle(1170, 481, 200, 30);
        
        ofSetColor(0);
        newFont.drawString("Spotify:", 1240, 500);
        
        ofSetColor(255);
        newFont.drawString("Currently listening to:", 12001200, 570);
        
        icarus.draw(1168, 595, 200, 200);
        
        newFont.drawString("Icarus", 1245, 840);
        newFont.drawString("By Jedwill", 1230, 860);
    }
    
    
    
    
}

void ofApp::drawShoppingList() {
    
    // draw the shopping list section
    ofSetColor(255);
    ofDrawRectangle(750, 449, 350, 452);
    
    
    if(conversationTerm == false) {
        ofSetColor(33);
        ofDrawRectangle(820, 481, 200, 30);
        
        ofSetColor(255);
        newFont.drawString("Shopping List:", 870, 500);
        
        ofSetColor(0);
        
        // this functionality checks whether the user has asked to add something to
        // the shopping list first or whether they have asked the shopping to be ordered first
        // the order the user asks affects the display of the shopping list and therefore
        // we must check which one was asked first
        if(orderedShopping == false) {
            newFont.drawString("Bananas", 793, 560);
            newFont.drawString("Bread", 793, 590);
            newFont.drawString("Eggs", 793, 620);
            newFont.drawString("Milk", 793, 650);
            newFont.drawString("Coffee", 793, 680);
            if(chocolateFirst == true && chocolateAdded == true) {
                newFont.drawString("Chocolate", 793, 710);
            }
        }
        
        if(orderedShopping == true) {
            if(chocolateAdded == true && chocolateFirst == false) {
                newFont.drawString("chocolate", 793, 560);
            }
            
        }
        
    }
    
    
    
    
}

void ofApp::changeLights() {
    // draws the layover of the apartment - simulates changing the colour of the lights
    
    // changes the lights to one of four colour options
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
        ofDrawRectangle(1000, 30, 300, 30);
        ofDrawRectangle(1000, 380, 300, 30);
        
        ofSetColor(255);
        newFont.drawString("Welcome to your apartment", 1070, 50);
        newFont.drawString("Located in London, England", 1068, 399);
    }
    
    
    
    
}

void ofApp::drawAlarm() {
    
    // draws the alarm section
    ofSetColor(50);
    ofDrawRectangle(400, 378, 450, 71);
    
    if (conversationTerm == false) {
        ofSetColor(255);
        
        if(setAlarm == false) {
            newFont.drawString("You currently have no alarm set", 525, 418);
        } else {
            newFont.drawString("Alarm set for: 5:00am", 560, 418);
        }
    }
    
   
}

void ofApp::drawInstructionsSection() {
    
    // draws the instruction section
    ofSetColor(199, 227, 229);
    ofDrawRectangle(400, 0, 450, 380);
    
    if (conversationTerm == false) {
        ofSetColor(0);
        newFont.drawString("Welcome to Ava, your own personal AI assistant.", 420, 40);
        newFont.drawString("Here's some things you can ask Ava to do:", 420, 60);
        newFont.drawString(" - Ask it to add an item to your shopping list", 420, 90);
        newFont.drawString(" - Ask it to change the colour of the lights", 420, 115);
        newFont.drawString(" - Ask it to remove something from your to do list", 420, 140);
        newFont.drawString(" - Ask it what the weather is like", 420, 165);
        newFont.drawString(" - Ask it what time it is", 420, 190);
        newFont.drawString(" - Ask it to play music", 420, 215);
        newFont.drawString(" - Ask it to set your alarm", 420, 240);
        newFont.drawString(" - Ask it add an item to your to do list", 420, 265);
        newFont.drawString(" - Ask it to order your shopping list online", 420, 290);
        newFont.drawString(" - Flirt with it", 420, 315);
    }
    
}

void ofApp::terminationTimer() {
    frame = ofGetFrameNum();
    endTimer = frame + 300;
    
    cout << frame << endl;
    cout << endTimer << endl;
    
    
}



