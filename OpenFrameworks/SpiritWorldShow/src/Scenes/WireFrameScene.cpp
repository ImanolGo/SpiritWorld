/*
 *  WireFrameScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 01/04/18.
 *
 */


#include "WireFrameScene.h"
#include "AppManager.h"

Particle::Particle()
{
    this->setup();
}

void Particle::setup()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_position.x = ofRandom(width);
    m_position.y = ofRandom(height);
    
    m_speed.x = ofRandom(-1,1);
    m_speed.y = ofRandom(-1,1);
}

void Particle::update()
{   
//    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
//    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
//
//    m_position.x = ofRandom(width);
//    m_position.y = ofRandom(height);
//
        m_position.x += m_speed.x;
        m_position.y += m_speed.y;
    
        this->stayOnScreen();
}

void Particle::stayOnScreen()
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


void Particle::draw()
{
//    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
//    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
//
//    m_position.x = ofRandom(width);
//    m_position.y = ofRandom(height);
    
    ofPushStyle();
    ofSetColor(ofColor::white);
        ofFill();
        ofDrawCircle(m_position, 2);
    ofPopStyle();
}



WireFrameScene::WireFrameScene(): ofxScene("WIREFRAME"), m_radius(100), m_velocity(0.3), m_distanceThreshold(10)
{
    //Intentionally left empty
}

WireFrameScene::~WireFrameScene()
{
    //Intentionally left empty
}


void WireFrameScene::setup() {
    ofLogNotice(getName() + "::setup");
    this->setupFbo();
    this->setupParticles();
}

void WireFrameScene::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fbo.allocate(width, height);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
}

void WireFrameScene::setupParticles()
{
    int numParticles = 12;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_radius = width;
    m_distanceThreshold = 2*width;
    
    for (int i = 0; i < numParticles; i++)
    {
        Particle particle;
        m_particles.push_back(particle);
    }
    
    m_particles[0].m_position.x = 0;  m_particles[0].m_position.y = 0;
    m_particles[1].m_position.x = width;  m_particles[1].m_position.y = 0;
    m_particles[2].m_position.x = 0;  m_particles[2].m_position.y = height;
    m_particles[3].m_position.x = width;  m_particles[3].m_position.y = height;
}


void WireFrameScene::update()
{
    this->updateParticles();
    this->updateFbo();
}

void WireFrameScene::updateParticles()
{
    double dt = ofGetLastFrameTime();
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    for (int i = 4; i < m_particles.size(); i++)
    {
        m_particles[i].update();
    }
    
}

void WireFrameScene::updateFbo()
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


void WireFrameScene::draw()
{
    ofEnableAlphaBlending();
    ofBackground(0,0,0);
    m_fbo.draw(0,0);
     //this->drawParticles();
}

void WireFrameScene::drawParticles()
{
    ofPushStyle();
    ofSetColor(255);
    ofSetLineWidth(2);
    
    for (int j=0; j < m_particles.size(); j++)
    {
        m_particles[j].draw();
        
        for (int k= j + 1; k < m_particles.size(); k++)
        {
            if (m_particles[j].m_position.distance(m_particles[k].m_position) < m_distanceThreshold)
            {
                ofDrawLine( m_particles[j].m_position, m_particles[k].m_position );
            }
        }
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void WireFrameScene::willFadeIn() {
     ofLogNotice("WireFrameScene::willFadeIn");
}

void WireFrameScene::willDraw() {
    ofLogNotice("WireFrameScene::willDraw");
}

void WireFrameScene::willFadeOut() {
    ofLogNotice("WireFrameScene::willFadeOut");
}

void WireFrameScene::willExit() {
     ofLogNotice("WireFrameScene::willExit");
}
