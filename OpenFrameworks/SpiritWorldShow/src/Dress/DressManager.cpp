/*
 *  DressManager.cpp
 *  UDP Pixels
 *
 *  Created by Imanol Gomez on 15/02/17.
 *
 */



#include "ofMain.h"

#include "DressManager.h"
#include "AppManager.h"


DressManager::DressManager(): Manager(), m_isAltPressed(false), m_showChannels(false), m_isCtrlpressed(false)
{
	//Intentionally left empty
}


DressManager::~DressManager()
{
    ofLogNotice() <<"DressManager::Destructor" ;
}


void DressManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupImage();
    
    ofLogNotice() <<"DressManager::initialized" ;
    
}


void DressManager::setupImage()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();

    string resourceName = "DressLayout";
    ofPoint position;
    m_costumeImage =  ofPtr<ImageVisual> (new ImageVisual(position,resourceName));
    m_costumeImage->setHeight(height);
    m_costumeImage->setWidth(width);
}

void DressManager::update()
{
    //
}


void DressManager::draw()
{
    ofEnableAlphaBlending();
        m_costumeImage->draw();
        this->drawCostumeLeds();
    ofDisableAlphaBlending();
}

void DressManager::drawCostumeLeds()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    AppManager::getInstance().getLedsManager().draw(width,height);
}


void DressManager::pressedMouse(ofMouseEventArgs &e)
{
    ofLogNotice() <<"DressManager::pressedMouse" ;
    //ofLogNotice() <<"DressManager::Shift " <<  m_isCtrlpressed;
    
    ofPoint pos(e.x,e.y,0.0);
    
    if(m_isAltPressed){
        AppManager::getInstance().getLedsManager().addLed(pos,0);
    }
    if (m_isCtrlpressed){
        AppManager::getInstance().getLedsManager().addLed(pos,1);
    }
    
    
}


void DressManager::pressedBackSpace()
{
    if(m_isAltPressed){
        AppManager::getInstance().getLedsManager().deleteLastLed(0);
    }
    if (m_isCtrlpressed){
         AppManager::getInstance().getLedsManager().deleteLastLed(1);
    }
    
}

void DressManager::toggleShowChannels()
{
    m_showChannels = !m_showChannels;
    
    AppManager::getInstance().getLedsManager().showChannels(m_showChannels);
    
}



