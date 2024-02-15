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
    int radius = 200;
    bool isGettingDragged = false;
    bool hasClockImage = false;
    
    
    glm::vec3 secondHand = glm::vec3(0, radius, 0);
    glm::vec3 minuteHand = glm::vec3(0, radius, 0);
    glm::vec3 hourHand = glm::vec3(0, radius / 2, 0);
    
    ofImage clockImage;
    
    glm::vec2 pos;
    
    Clock(int startingRadius) {
        radius = startingRadius;
    }
        
    Clock(glm::vec2 startingPosition, int startingRadius) {
        pos = startingPosition;
        radius = startingRadius;
    }
    
    
    void draw();
    void update();
    bool isInside(glm::vec2 p) {
        return glm::length(pos - p) <= radius;
    }
    void setImage(std::string filePath) {
        clockImage.load(filePath);
        clockImage.resize(radius * 2, radius * 2);
        hasClockImage = true;
    }
    
    void removeImage() {
        clockImage.clear();
        hasClockImage = false;
    }
};

class MatrixClock : public Clock {
public:
    ofMatrix4x4 translationMatrix;
    ofMatrix4x4 scaleMatrix;
    ofMatrix4x4 rotationMatrix;
    
    MatrixClock(ofMatrix4x4 startingMatrix, int startingRadius) : Clock (startingRadius) {
        translationMatrix = startingMatrix;
    }
    
    void draw();
    
    bool isInside(ofMatrix4x4 m) {
        m.translate(translationMatrix.getInverse().getTranslation());
        m.rotate(rotationMatrix.getInverse().getRotate());
        m.scale(glm::vec3(1,1,0) / scaleMatrix.getScale());
        return clockImage.getColor(m.getTranslation().x + radius, m.getTranslation().y + radius).a != 0;
    }
};
