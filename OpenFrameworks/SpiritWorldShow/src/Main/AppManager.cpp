/*
 *  AppManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): Manager(), m_debugMode(false)
{
   //Intentionally left empty
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::setup()
{
	if(m_initialized)
		return;

    
    ofLogNotice() << "AppManager::initialized";

	Manager::setup();
    
    this->setupOF();
	this->setupManagers();
    
    //setDebugMode(m_debugMode);
}

void AppManager::setupOF()
{
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);
    ofSetEscapeQuitsApp(false);
    ofDisableSmoothing();
    ofDisableAntiAliasing();
}


void AppManager::setupManagers()
{
    m_settingsManager.setup();
    m_resourceManager.setup();
    m_viewManager.setup();
    m_visualEffectsManager.setup();
    m_audioManager.setup();
    m_dressManager.setup();
    m_layoutManager.setup();
    m_keyboardManager.setup();
    m_mouseManager.setup();
    m_sceneManager.setup();
    m_ledsManager.setup();
    m_oscManager.setup();
    m_udpManager.setup();
    m_guiManager.setup();
    
}

void AppManager::update()
{
    m_audioManager.update();
    m_oscManager.update();
    m_sceneManager.update();
    m_visualEffectsManager.update();
    m_viewManager.update();
    m_layoutManager.update();
    m_ledsManager.update();
    m_udpManager.update();
    m_guiManager.update();
}


void AppManager::draw()
{
    ofBackground(50,50,50);
    m_guiManager.draw();
    m_layoutManager.draw();
}

void AppManager::toggleDebugMode()
{
    m_debugMode = !m_debugMode;
    setDebugMode(m_debugMode);
}


void AppManager::exit()
{
    m_guiManager.saveGuiValues();
}

void AppManager::setDebugMode(bool showDebug)
{
    m_debugMode = showDebug;
    
    ofLogNotice()<<"AppManager::setDebugMode-> " << m_debugMode;
    
    if(m_debugMode){
        //ofSetLogLevel(OF_LOG_VERBOSE);
    }
    else{
        ofSetLogLevel(OF_LOG_NOTICE);
    }
    

    m_guiManager.showGui(m_debugMode);
    
}



