#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		
};

class Clock {

public:
    const int radius = 200;
    bool isGettingDragged = false;
    bool hasClockImage = false;
    bool usingMatrix = false;
    
    double secondsInRadians, minutesInRadians, hoursInRadians;
    
    ofImage clockImage;
    
    glm::vec2 pos;
    ofMatrix4x4 matrix;
        
    Clock(glm::vec2 startingPosition) {
        pos = startingPosition;
        usingMatrix = false;
    }
    
    Clock(ofMatrix4x4 startingMatrix) {
        matrix = startingMatrix;
        usingMatrix = true;
    }
    
    void draw();
    void update();
    bool isInside(glm::vec2 p) {
        return glm::length(pos - p) <= radius;
    }
    void setImage(std::string filePath) {
        clockImage.load(filePath);
        hasClockImage = true;
    }
    
    void removeImage() {
        clockImage.clear();
        hasClockImage = false;
    }
};
