/*
 *  OscManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */



#include "OscManager.h"
#include "SettingsManager.h"
#include "AppManager.h"


const string OscManager::OSC_PARENT_ADDRESS = "/SpiritWorld";

OscManager::OscManager(): Manager()
{
    //Intentionally left empty
}

OscManager::~OscManager()
{
   ofLogNotice() << "OscManager::destructor";
}


//--------------------------------------------------------------

void OscManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupOscReceiver();
    this->setupOscSender();
    
    ofLogNotice() <<"OscManager::initialized" ;
}

void OscManager::setupOscReceiver()
{
    int portReceive = AppManager::getInstance().getSettingsManager().getOscPortReceive();
    ofLogNotice() <<"OscManager::setupOscReceiver -> listening for osc messages on port  " << portReceive;
    m_oscReceiver.setup(portReceive);
   
    
}

void OscManager::setupOscSender()
{
    int portSend = AppManager::getInstance().getSettingsManager().getOscPortSend();
    string host = AppManager::getInstance().getSettingsManager().getIpAddress();
    m_oscSender.setup(host, portSend);
    ofLogNotice() <<"OscManager::setupOscSender -> open osc connection " << host << ":" << portSend;
    
}


void OscManager::update()
{
    // check for waiting messages
    while(m_oscReceiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        m_oscReceiver.getNextMessage(m);
        
        if(m.getAddress() == OSC_PARENT_ADDRESS + "/Scene")
        {
            string sceneName = m.getArgAsString(0);
            AppManager::getInstance().getGuiManager().onSceneChange(sceneName);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/Hue")
        {
            auto value = m.getArgAsString(0);
            float fValue = ofToFloat(value);
            AppManager::getInstance().getGuiManager().setHue(fValue);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/Saturation")
        {
            auto value = m.getArgAsString(0);
            float fValue = ofToFloat(value);
            AppManager::getInstance().getGuiManager().setSaturation(fValue);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/Value")
        {
            auto value = m.getArgAsString(0);
            float fValue = ofToFloat(value);
            AppManager::getInstance().getGuiManager().setValue(fValue);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/Speed")
        {
            auto value = m.getArgAsString(0);
            float fValue = ofToFloat(value);
            AppManager::getInstance().getGuiManager().setSpeed(fValue);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/Size")
        {
            auto value = m.getArgAsString(0);
            float fValue = ofToFloat(value);
            AppManager::getInstance().getGuiManager().setSize(fValue);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/SpeedAnimation")
        {
            auto speed = m.getArgAsString(0);
            float fSpeed = ofToFloat(speed);
            auto time = m.getArgAsString(1);
            float fTime = ofToFloat(time);
            AppManager::getInstance().getGuiManager().addSpeedEffect(fSpeed, fTime);
        }
        
        else if(m.getAddress() == OSC_PARENT_ADDRESS + "/SizeAnimation")
        {
            auto size = m.getArgAsString(0);
            float fSize = ofToFloat(size);
            auto time = m.getArgAsString(1);
            float fTime = ofToFloat(time);
            AppManager::getInstance().getGuiManager().addSizeEffect(fSize, fTime);
        }
        
          ofLogNotice() <<"OscManager::received -> " << this->getMessageAsString(m);
    }
}


string OscManager::getMessageAsString(const ofxOscMessage& m) const
{
    string msg_string;
    msg_string = m.getAddress();
    for(int i = 0; i < m.getNumArgs(); i++){
        // get the argument type
        msg_string += " ";
        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msg_string += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msg_string += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msg_string += m.getArgAsString(i);
        }
        else{
            msg_string += "unknown";
        }
    }
    
    return msg_string;
}









