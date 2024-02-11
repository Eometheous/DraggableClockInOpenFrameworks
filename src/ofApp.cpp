#include "ofApp.h"

glm::vec2 vec;

Clock myClock = Clock(glm::vec2(ofWindowSettings().getWidth()/2, ofWindowSettings().getHeight()/2), 200);

MatrixClock mClock = MatrixClock(ofMatrix4x4(), 200);


//--------------------------------------------------------------
void ofApp::setup(){
    mClock.matrix.translate(ofWindowSettings().getWidth()/2, ofWindowSettings().getHeight()/2, 0);
    
    myClock.setImage("./images/DiscordProfile.png");
    mClock.setImage("./images/DiscordProfile.png");
}

//--------------------------------------------------------------
void ofApp::update(){
//    myClock.update();
    mClock.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    myClock.draw();
    mClock.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 113) {
        mClock.matrix.rotate(15, mClock.matrix.getTranslation().x, mClock.matrix.getTranslation().y, 0);
    }
    if (key == 101) {
        mClock.matrix.rotate(-15, mClock.matrix.getTranslation().x, mClock.matrix.getTranslation().y, 0);
    }
    if (key == 119) mClock.matrix.translate(0, -15, 0);
    if (key == 97) mClock.matrix.translate(-15, 0, 0);
    if (key == 115) mClock.matrix.translate(0, 15, 0);
    if (key == 100) mClock.matrix.translate(15, 0, 0);
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    glm::vec2 clickedPosition = glm::vec2(x, y);
    
    if (myClock.isInside(clickedPosition)) {
        vec = glm::vec2(myClock.pos.x - x, myClock.pos.y - y);
        myClock.isGettingDragged = true;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    myClock.isGettingDragged = false;
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
    secondsInRadians = (seconds * 6 * M_PI) / 180;
    
    int minutes = ofGetMinutes();
    minutesInRadians = (minutes * 6 * M_PI) / 180 + secondsInRadians / 60;
    
    int hours = ofGetHours();
    hoursInRadians = (hours * 30 * M_PI) / 180 + minutesInRadians / 60;

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
    ofDrawLine(pos.x, pos.y, pos.x + radius * sin(secondsInRadians), pos.y + radius * cos(secondsInRadians) * -1);
    
    // draw minute and hour hand lines as black
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5);
    ofDrawLine(pos.x, pos.y, pos.x + radius * sin(minutesInRadians), pos.y + radius * cos(minutesInRadians) * -1);
    
    ofSetLineWidth(10);
    ofDrawLine(pos.x, pos.y, pos.x + radius / 2 * sin(hoursInRadians), pos.y + radius / 2 * cos(hoursInRadians) * -1);
    
    // draw a small circle in the center to hide weird edges of clock hands
    ofDrawCircle(pos.x, pos.y, 10);
    
    // draw outer casing circle not filled in to hide weird edges of clock hands
    ofNoFill();
    ofSetLineWidth(60);
    ofDrawCircle(pos.x, pos.y, radius);
}

void MatrixClock::draw() {
    ofSetColor(255, 255, 255);
    if (hasClockImage) clockImage.draw(matrix.getTranslation().x - radius, matrix.getTranslation().y - radius, radius * 2, radius * 2);
    
    // set second hand color to red and draw line
    ofSetLineWidth(2);
    ofSetColor(255, 0, 0);
    ofDrawLine(matrix.getTranslation().x, matrix.getTranslation().y, matrix.getTranslation().x + radius * sin(secondsInRadians), matrix.getTranslation().y + radius * cos(secondsInRadians) * -1);
    
    // draw minute and hour hand lines as black
    ofSetColor(0, 0, 0);
    ofSetLineWidth(5);
    
    ofDrawLine(matrix.getTranslation().x, matrix.getTranslation().y, matrix.getTranslation().x + radius * sin(minutesInRadians), matrix.getTranslation().y + radius * cos(minutesInRadians) * -1);
    
    ofSetLineWidth(10);
    ofDrawLine(matrix.getTranslation().x, matrix.getTranslation().y, matrix.getTranslation().x + radius / 2 * sin(hoursInRadians), matrix.getTranslation().y + radius / 2 * cos(hoursInRadians) * -1);
    
    // draw a small circle in the center to hide weird edges of clock hands
    ofDrawCircle(matrix.getTranslation(), 10);
}
