/*
 *  EndScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 02/04/18.
 *
 */


#include "EndScene.h"
#include "AppManager.h"

ParticleEnd::ParticleEnd()
{
    this->setup();
}

void ParticleEnd::setup()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_position.x = ofRandom(width);
    m_position.y = ofRandom(height);
    
    m_speed.x = ofRandom(-1,1);
    m_speed.y = ofRandom(-1,1);
    
    this->setupImage();
}

void ParticleEnd::setupImage()
{
    m_dotVisual.setResource("Circle");
    m_dotVisual.setCentred(true);
    int size = 500;
    m_dotVisual.setWidth(size, true);
    
    m_dotVisual.setPosition(m_position);
    m_dotVisual.setColor(ofColor::chocolate);
    if(ofRandom(1.0) < 0.5){
        m_dotVisual.setColor(ofColor::white);
    }
}

void ParticleEnd::update()
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

void ParticleEnd::stayOnScreen()
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


void ParticleEnd::draw()
{
    m_dotVisual.draw();
}



EndScene::EndScene(): ofxScene("END")
{
    this->setupFbo();
    this->setupParticles();
}

EndScene::~EndScene()
{
    //Intentionally left empty
}


void EndScene::setup() {
    ofLogNotice(getName() + "::setup");
   
}

void EndScene::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}

void EndScene::setupParticles()
{
    int numParticles = 200;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    for (int i = 0; i < numParticles; i++)
    {
        ParticleEnd particle;
        m_particles.push_back(particle);
    }
}


void EndScene::update()
{
    this->updateParticles();
    this->updateFbo();
}

void EndScene::updateParticles()
{
    double dt = ofGetLastFrameTime();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    for (int i = 0; i < m_particles.size(); i++)
    {
        m_particles[i].update();
    }
    
}

void EndScene::updateFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    ofEnableAlphaBlending();
    m_fbo.begin();
//        ofSetColor(0, 0, 0, 5);
//        ofDrawRectangle(0, 0, width, height);
//        ofSetColor(255);
     ofClear(0);
         this->drawParticles();
    m_fbo.end();
    ofDisableAlphaBlending();
}


void EndScene::draw()
{
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    m_fbo.draw(0,0);
     //this->drawParticles();
}

void EndScene::drawParticles()
{
    //ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i=0; i < m_particles.size(); i++)
    {
        m_particles[i].draw();
    }
   // ofDisableBlendMode();
    
}

void EndScene::willFadeIn() {
    ofLogNotice("EndScene::willFadeIn");
    AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void EndScene::willDraw() {
    ofLogNotice("EndScene::willDraw");
}

void EndScene::willFadeOut() {
    ofLogNotice("EndScene::willFadeOut");
    AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void EndScene::willExit() {
     ofLogNotice("EndScene::willExit");
}
