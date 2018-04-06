/*
 *  VideoScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "VideoScene.h"
#include "AppManager.h"

VideoScene::VideoScene(std::string name): ofxScene(name)
{
   this->setupVideo();
}

VideoScene::~VideoScene()
{
    //Intentionally left empty
}


void VideoScene::setup() {
    ofLogNotice(getName() + "::setup");
    this->setupVideo();
}

void VideoScene::setupVideo()
{
    auto& videoPaths = AppManager::getInstance().getSettingsManager().getVideoResourcesPath();
    
    if(videoPaths.find(getName())!=videoPaths.end())
    {
        string path = videoPaths.at(getName());
        m_videoPlayer.load(path);
        m_videoPlayer.setLoopState(OF_LOOP_NORMAL);
       // m_videoPlayer.play();
        m_videoPlayer.stop();

    }
    else{
        ofLogNotice() << getName() + "::setupVideo-> Cannot find " << getName();
    }
}


void VideoScene::update()
{
    this->updateVideo();
}

void VideoScene::updateVideo()
{

    if(m_videoPlayer.isInitialized() && m_videoPlayer.isLoaded())
    {
        auto speed = AppManager::getInstance().getGuiManager().getSpeed();
        m_videoPlayer.setSpeed(speed);
        m_videoPlayer.update();
    }
}

void VideoScene::draw()
{
    ofBackground(0,0,0);
    this->drawVideo();
}

void VideoScene::drawVideo()
{
    if(m_videoPlayer.isInitialized() && m_videoPlayer.isLoaded())
    {
        
        float width = AppManager::getInstance().getSettingsManager().getAppWidth();
        float height = AppManager::getInstance().getSettingsManager().getAppHeight();
        
        m_videoPlayer.draw(0,0,width,height);
    }
    
}

void VideoScene::willFadeIn() {
     ofLogNotice("VideoScene::willFadeIn");
    
    //AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
    
    if(m_videoPlayer.isInitialized() && m_videoPlayer.isLoaded())
    {
        m_videoPlayer.play();
    }
    
    m_videoPlayer.play();
}

void VideoScene::willDraw() {
    ofLogNotice("VideoScene::willDraw");
}

void VideoScene::willFadeOut() {
    ofLogNotice("VideoScene::willFadeOut");
     //AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void VideoScene::willExit() {
    if(m_videoPlayer.isInitialized() && m_videoPlayer.isLoaded())
    {
        m_videoPlayer.stop();
    }
    
     m_videoPlayer.stop();
     m_videoPlayer.close();
}
