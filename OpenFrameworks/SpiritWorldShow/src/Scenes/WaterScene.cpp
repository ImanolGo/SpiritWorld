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
   this->setupShader();
}

WaterScene::~WaterScene()
{
    //Intentionally left empty
}


void WaterScene::setup() {
    ofLogNotice(getName() + "::setup");
    
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
    float timeScale = AppManager::getInstance().getGuiManager().getSpeed();
    timeScale = ofMap(timeScale, 0.0, 1.0, 0.0, 2.0, true);

    m_shader.begin();
    m_shader.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);
    m_shader.setUniform1f("iTime", ofGetElapsedTimef()*timeScale);
    
        ofRect(0, 0, width, height);
    
    m_shader.end();
    
}

void WaterScene::willFadeIn() {
     ofLogNotice("WaterScene::willFadeIn");
     AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void WaterScene::willDraw() {
    ofLogNotice("WaterScene::willDraw");
}

void WaterScene::willFadeOut() {
    ofLogNotice("WaterScene::willFadeOut");
    AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void WaterScene::willExit() {
     ofLogNotice("WaterScene::willExit");
}
