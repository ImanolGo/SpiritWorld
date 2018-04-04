/*
 *  DotsScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 02/04/18.
 *
 */


#include "DotsScene.h"
#include "AppManager.h"

Dot::Dot()
{
    this->setup();
}

void Dot::setup()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_position.x = ofRandom(width);
    m_position.y = ofRandom(height);
    
    m_speed.x = ofRandom(-1,1);
    m_speed.y = ofRandom(-1,1);
    
    this->setupImage();
}

void Dot::setupImage()
{
    m_dotVisual.setResource("Brush");
    m_dotVisual.setCentred(true);
    int size = 500;
    m_dotVisual.setWidth(size, true);
    
    m_dotVisual.setPosition(m_position);
    m_dotVisual.setColor(ofColor::white);
//    m_dotVisual.setColor(ofColor(5, 5,255));
//    if(ofRandom(1.0) < 0.2){
//        m_dotVisual.setColor(ofColor::white);
//    }
}

void Dot::update()
{
    float timeScale = AppManager::getInstance().getGuiManager().getSpeed();
    timeScale = ofMap(timeScale, 0.0, 1.0, 0.0, 5.0);
    
    m_position.x += m_speed.x*timeScale;
    m_position.y += m_speed.y*timeScale;

    this->stayOnScreen();
    m_dotVisual.setPosition(m_position);
    
    
    float scale = AppManager::getInstance().getGuiManager().getSize();
     m_dotVisual.setScale(ofVec3f(scale));
}

void Dot::stayOnScreen()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    if((m_position.x < 0) || (m_position.x > width)){
        m_speed.x *= -1;
    }
    if((m_position.y < 0) || (m_position.y > height)){
        m_speed.y *= -1;
    }
    
}


void Dot::draw()
{
    m_dotVisual.draw();
}



DotsScene::DotsScene(): ofxScene("DOTS")
{
    this->setupFbo();
    this->setupParticles();
}

DotsScene::~DotsScene()
{
    //Intentionally left empty
}


void DotsScene::setup() {
    ofLogNotice(getName() + "::setup");
   
}

void DotsScene::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}

void DotsScene::setupParticles()
{
    int numParticles = 200;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    for (int i = 0; i < numParticles; i++)
    {
        Dot particle;
        m_particles.push_back(particle);
    }
}


void DotsScene::update()
{
    this->updateParticles();
    this->updateFbo();
}

void DotsScene::updateParticles()
{
    double dt = ofGetLastFrameTime();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    for (int i = 0; i < m_particles.size(); i++)
    {
        m_particles[i].update();
    }
    
}

void DotsScene::updateFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    ofEnableAlphaBlending();
    m_fbo.begin();
        ofSetColor(0, 0, 0, 5);
        ofDrawRectangle(0, 0, width, height);
        ofSetColor(255);
         this->drawParticles();
    m_fbo.end();
    ofDisableAlphaBlending();
}


void DotsScene::draw()
{
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    m_fbo.draw(0,0);
     //this->drawParticles();
}

void DotsScene::drawParticles()
{
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i=0; i < m_particles.size(); i++)
    {
        m_particles[i].draw();
    }
    ofDisableBlendMode();
    
}

void DotsScene::willFadeIn() {
    ofLogNotice("DotsScene::willFadeIn");
    //AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void DotsScene::willDraw() {
    ofLogNotice("DotsScene::willDraw");
}

void DotsScene::willFadeOut() {
    ofLogNotice("DotsScene::willFadeOut");
    //AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void DotsScene::willExit() {
     ofLogNotice("DotsScene::willExit");
}
