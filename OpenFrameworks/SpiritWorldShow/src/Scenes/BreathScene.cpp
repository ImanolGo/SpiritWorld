/*
 *  BreathScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 06/04/18.
 *
 */


#include "BreathScene.h"
#include "AppManager.h"

BreathScene::BreathScene(): ofxScene("BREATH"), m_elapsedTime(0){}

void BreathScene::setup() {
    ofLogNotice("BreathScene::setup");
    m_color = ofColor::white;
    m_elapsedTime = 0;
}

void BreathScene::update() {
    this->updateColor();
}

void BreathScene::updateColor() {
    
    float value = AppManager::getInstance().getGuiManager().getValue();
    float speed = AppManager::getInstance().getGuiManager().getSpeed();
    //float angle = sin(4*speed*ofGetElapsedTimef());
    m_elapsedTime = m_elapsedTime + ofGetLastFrameTime();
    float angle = sin(speed*m_elapsedTime);
    float brightness = ofMap(angle, -1, 1, 0, value);
    m_color.setBrightness(brightness);
}


void BreathScene::draw() {
    ofBackground(m_color);
}

void BreathScene::willFadeIn() {
     ofLogNotice("BreathScene::willFadeIn");
    // AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void BreathScene::willDraw() {
    ofLogNotice("BreathScene::willDraw");
}

void BreathScene::willFadeOut() {
    ofLogNotice("BreathScene::willFadeOut");
     //AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void BreathScene::willExit() {
    ofLogNotice("BreathScene::willExit");
}
