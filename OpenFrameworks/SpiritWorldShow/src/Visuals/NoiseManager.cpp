/*
 *  NoiseManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */

#include "ofMain.h"

#include "NoiseManager.h"
#include "AppManager.h"


NoiseManager::NoiseManager(): Manager(), m_noiseIncrement1(0), m_noiseIncrement2(0),m_mapMin(0), m_mapMax(1)
{
	//Intentionally left empty
}


NoiseManager::~NoiseManager()
{
    ofLogNotice() <<"NoiseManager::Destructor" ;
}


void NoiseManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupPlane();
    this->setupFbo();
    this->setupShader();
    this->setupParameters();
    
    ofLogNotice() <<"NoiseManager::initialized" ;
    
}

void NoiseManager::setupPlane()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_plane.set(width,height, 2, 2);
    m_plane.setPosition(0, 0, 0);
    
}

void NoiseManager::setupFbo()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    m_fbo.allocate(width, height, GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();

    m_texture.allocate(width, height, GL_RGB);
}


void NoiseManager::setupShader()
{
    m_noiseShader.load("shaders/shadersGL3/Noise3D.vert", "shaders/shadersGL3/Noise3D.frag");
}

void NoiseManager::setupParameters()
{
    m_noiseStep = ofVec2f(0,0);
    m_noiseScale.x = 0.05;
    m_noiseScale.y = 0.05;
    m_noiseIncrement1 = 0.02;
    m_mapMin = 0;
    m_mapMax = 1;
}



void NoiseManager::update()
{
    this->updateNoise();
    this->updateFbo();
}

void NoiseManager::updateNoise()
{
    m_noiseStep.x += m_noiseIncrement1;
    m_noiseStep.y += m_noiseIncrement2;
}


void NoiseManager::updateFbo()
{
   m_fbo.begin();
        //ofClear(0, 0, 0);
        m_noiseShader.begin();
        m_noiseShader.setUniform2f("scale", m_noiseScale.x, m_noiseScale.y);
        m_noiseShader.setUniform2f("steps", m_noiseStep);
        m_noiseShader.setUniform2f("map", m_mapMin, m_mapMax);
        m_noiseShader.setUniform1i("bSmooth", 0);
    
        m_texture.draw(0,0);
        m_noiseShader.end();
    m_fbo.end();
}


void NoiseManager::draw()
{
    m_fbo.draw(0,0);
}


void NoiseManager::draw(float x, float y, float w, float h)
{
    m_fbo.draw(x,y,w,h);
}



void NoiseManager::onScaleChange(float value)
{
    m_noiseScale.x = value;
    m_noiseScale.y = value;
}



