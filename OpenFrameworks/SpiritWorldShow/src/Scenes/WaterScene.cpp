/*
 *  WaterScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "WaterScene.h"
#include "AppManager.h"

WaterScene::WaterScene(): ofxScene("WATER")
{
    //Intentionally left empty
}

WaterScene::~WaterScene()
{
    //Intentionally left empty
}


void WaterScene::setup() {
    ofLogNotice(getName() + "::setup");
    this->setupShader();
}

void WaterScene::setupShader()
{
   m_shader.load("shader/shadertoy");

   if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/Water");
    }
    else{
        m_shader.load("shaders/shadersGL2/Water");
    }
}


void WaterScene::update()
{
    this->updateShader();
}

void WaterScene::updateShader()
{
}

void WaterScene::draw()
{
    ofBackground(0,0,0);
    this->drawShader();
}

void WaterScene::drawShader()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();

    m_shader.begin();
    m_shader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);
    m_shader.setUniform1f("iTime", ofGetElapsedTimef());
    
        ofRect(0, 0, width, height);
    
    m_shader.end();
    
}

void WaterScene::willFadeIn() {
     ofLogNotice("WaterScene::willFadeIn");
}

void WaterScene::willDraw() {
    ofLogNotice("WaterScene::willDraw");
}

void WaterScene::willFadeOut() {
    ofLogNotice("WaterScene::willFadeOut");
}

void WaterScene::willExit() {
     ofLogNotice("WaterScene::willExit");
}
