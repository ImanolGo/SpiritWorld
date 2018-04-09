/*
 *  ColorScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "ColorScene.h"
#include "AppManager.h"

ColorScene::ColorScene(): ofxScene("COLOR"){}

void ColorScene::setup() {
    ofLogNotice("ColorScene::setup");
}

void ColorScene::update() {
    
}

void ColorScene::draw() {
    ofBackground(255,255,255);
    
}

void ColorScene::willFadeIn() {
     ofLogNotice("ColorScene::willFadeIn");
    // AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void ColorScene::willDraw() {
    ofLogNotice("ColorScene::willDraw");
}

void ColorScene::willFadeOut() {
    ofLogNotice("ColorScene::willFadeOut");
     //AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void ColorScene::willExit() {
    ofLogNotice("ColorScene::willExit");
}
