#include "ofApp.h"

glm::vec2 vec;

Clock myClock = Clock(glm::vec2(ofWindowSettings().getWidth()/2, ofWindowSettings().getHeight()/2), 200);

MatrixClock mClock = MatrixClock(ofMatrix4x4(), 200);

bool matrixClockIsActive;

//--------------------------------------------------------------
void ofApp::setup(){
    matrixClockIsActive = false;
    mClock.translationMatrix.translate(ofWindowSettings().getWidth()/2, ofWindowSettings().getHeight()/2, 0);
    
    myClock.setImage("./images/DiscordProfile.png");
    mClock.setImage("./images/DiscordProfile.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    if (matrixClockIsActive) mClock.update();
    else myClock.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (matrixClockIsActive) mClock.draw();
    else myClock.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (matrixClockIsActive) {
        if (key == 113) mClock.rotationMatrix.rotate(-15, 0, 0, mClock.radius);     // rotate counter clock wise by pressing Q
        if (key == 101) mClock.rotationMatrix.rotate(15, 0, 0, mClock.radius);      // rotate clock wise by pressing E
        if (key == 57357) mClock.rotationMatrix.rotate(15, mClock.radius,0 , 0);    // rotate up by pressing up arrow
        if (key == 57359) mClock.rotationMatrix.rotate(-15, mClock.radius,0 , 0);   // rotate down by pressing down arrow
        if (key == 57356) mClock.rotationMatrix.rotate(-15, 0, mClock.radius , 0);  // rotate left by pressing left arrow
        if (key == 57358) mClock.rotationMatrix.rotate(15, 0, mClock.radius, 0);    // rotate right by pressing right arrow
        
        if (key == 119) mClock.translationMatrix.translate(0, -15, 0);  // go up by pressing W
        if (key == 97) mClock.translationMatrix.translate(-15, 0, 0);   // go left by pressing A
        if (key == 115) mClock.translationMatrix.translate(0, 15, 0);   // go down by pressind S
        if (key == 100) mClock.translationMatrix.translate(15, 0, 0);   // go right by pressing D
        
        if (key == 45) mClock.scaleMatrix.scale(.9, .9, 0); // zoom out with -
        if (key == 61) mClock.scaleMatrix.scale(1.1, 1.1, 0); // zoom in with +
    }
    
    // switch which clock is active
    if (key == 13) matrixClockIsActive = !matrixClockIsActive;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    if (myClock.isGettingDragged) {
        myClock.pos.x = x + vec.x;
        myClock.pos.y = y + vec.y;
    }
    else if (mClock.isGettingDragged) {
        mClock.translationMatrix.translate(ofVec3f(x - mClock.translationMatrix.getTranslation().x + vec.x, y - mClock.translationMatrix.getTranslation().y + vec.y, 0));
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    glm::vec2 clickedPosition = glm::vec2(x, y);
    if (matrixClockIsActive) {
        ofMatrix4x4 clickedPositionMatrix;
        clickedPositionMatrix.translate(clickedPosition);
        
        if (mClock.isInside(clickedPositionMatrix)) {
            vec = glm::vec3(mClock.translationMatrix.getTranslation().x - x, mClock.translationMatrix.getTranslation().y - y, 0);
            mClock.isGettingDragged = true;
        }
    }
    else {
        if (myClock.isInside(clickedPosition)) {
            vec = glm::vec2(myClock.pos.x - x, myClock.pos.y - y);
            myClock.isGettingDragged = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    myClock.isGettingDragged = false;
    mClock.isGettingDragged = false;
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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

void Clock::update() {
    int seconds = ofGetSeconds();
    float secondsInRadians = (seconds * 6 * M_PI) / 180;
    
    int minutes = ofGetMinutes();
    float minutesInRadians = (minutes * 6 * M_PI) / 180 + secondsInRadians / 60;
    
    int hours = ofGetHours();
    float hoursInRadians = (hours * 30 * M_PI) / 180 + minutesInRadians / 60;
    
    secondHand = glm::vec3(radius * sin(secondsInRadians), radius * cos(secondsInRadians) * -1, 0);
    minuteHand = glm::vec3(radius * sin(minutesInRadians), radius * cos(minutesInRadians) * -1, 0);
    hourHand = glm::vec3(radius / 2 * sin(hoursInRadians), radius / 2 * cos(hoursInRadians) * -1, 0);
    

}

void Clock::draw() {
    ofFill();
    
    // draw outer casing as a black circle
    ofDrawCircle(pos.x, pos.y, radius + 15);
    
    // draw white background for clock
    ofSetColor(255, 255, 255);
    ofDrawCircle(pos.x, pos.y, radius);
    
    if (hasClockImage) clockImage.draw(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
    
    // set second hand color to red and draw line
    ofSetLineWidth(2);
    ofSetColor(255, 0, 0);
    ofDrawLine(pos, secondHand + pos);
    
    // draw minute and hour hand lines as black
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5);
    ofDrawLine(pos,minuteHand + pos);
    
    ofSetLineWidth(10);
    ofDrawLine(pos,hourHand + pos);
    
    // draw a small circle in the center to hide weird edges of clock hands
    ofDrawCircle(pos.x, pos.y, 10);
    
    // draw outer casing circle not filled in to hide weird edges of clock hands
    ofNoFill();
    ofSetLineWidth(60);
    ofDrawCircle(pos.x, pos.y, radius);
}

void MatrixClock::draw() {
    glm::mat4 i = scaleMatrix * rotationMatrix * translationMatrix;
    
    ofPushMatrix();
    
    ofMultMatrix(i);
    
    ofSetColor(255, 255, 255);
    if (hasClockImage) clockImage.draw(- radius, - radius, radius * 2, radius * 2);
    
    // set second hand color to red and draw line
    ofSetLineWidth(2);
    ofSetColor(255, 0, 0);
    ofDrawLine(glm::vec3(0,0,0), secondHand);
    
    // draw minute and hour hand lines as black
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5);
    
    ofDrawLine(glm::vec3(0,0,0), minuteHand);
    
    ofSetLineWidth(10);
    ofDrawLine(glm::vec3(0,0,0), hourHand);
    
    // draw a small circle in the center to hide weird edges of clock hands
    ofFill();
    ofDrawCircle(0, 0, 10);
    
    ofPopMatrix();
}
