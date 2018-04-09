/*
 *  AudioManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 06/04/18.
 *
 */

#include "AudioManager.h"
#include "AppManager.h"


AudioManager::AudioManager(): m_volume(0.5), m_audioMax(1.0), m_audioOn(false), m_numPeaks(5.0)
{
    //Intentionaly left empty
}


AudioManager::~AudioManager()
{
    ofLogNotice() <<"AudioManager::Destructor" ;
    //m_fft.killFFT();
    //sleep(200);
}


void AudioManager::setup()
{
    Manager::setup();
    
    ofLogNotice() <<"AudioManager::initialized" ;
    
    this->setupFFT();
}


void AudioManager::setupFFT()
{
    m_fft.setup();
    m_fft.setMirrorData(false);
    m_fft.setPeakDecay(0.915);
    m_fft.setMaxDecay(0.995);
    m_fft.setThreshold(1.0);
    //m_fft.setVolume(m_volume);
}


void AudioManager::update()
{
    if (!m_audioOn) {
        return;
    }

    m_fft.update();
    
    m_audioMax = this->getMaxSound();
    
    //    vector<float> peakData = m_fft.getFftRawData();
    //    float avrPeak = 0;
    //    for(int i=0; i<= peakData.size(); i++)
    //    {
    //        if(peakData[i]>0 && peakData[i]<=1){
    //            avrPeak+=peakData[i];
    //        }
    //
    //    }
    //    avrPeak = ofMap(avrPeak, 0.0, peakData.size(), 0, 1.0, true);
    
//    float avrPeak = m_fft.getAveragePeak();
//    avrPeak*=m_volume;
//
//    m_audioMax = ofMap(avrPeak, 0.0, 1.0, 0.0, 1.0, true);
    
    //m_audioMax = ofMap(m_fft.getAveragePeak(), 0.1, 1.0 - m_volume*0.2, 0.0, 1.0, true);
    
    
    //m_audioMax = ofMap(data[0], 0.1, 1.0 - m_volume*0.2, 0.0, 1.0, true);
    
    //ofLogNotice() <<"AudioManager::update: " << m_fft.getAveragePeak();
    //ofLogNotice() <<"AudioManager::update2: " << m_fft.getLoudBand();
    
    AppManager::getInstance().getGuiManager().setAudioPower(m_audioMax);
}

void AudioManager::draw()
{
    //m_fft.draw(340,600);
    this->drawCircle();
}

void AudioManager::drawCircle()
{
    int mainWindowIndex = 0;
    
    float radius = ofMap(m_audioMax, 0.0, 1.0, 10, 200, true);
    
    //ofColor color = AppManager::getInstance().getSettingsManager().getColor("GUI1");
    
    ofPushStyle();
    ofSetCircleResolution(100);
    ofSetColor(ofColor::white);
    ofDrawCircle(m_circlePosition, radius);
    ofPopStyle();
    
    
}


void AudioManager::onChangeVolume(float& value)
{
    m_volume = value;
    //m_fft.setVolume(m_volume);
}

void AudioManager::setAudioMax(float audioMax)
{
    if(m_audioOn){
        return;
    }
    
    m_audioMax = audioMax;
}

void AudioManager::onChangeAudioOn(bool& value)
{
    m_audioOn = value;
    if(!m_audioOn){
        m_audioMax = 1.0;
    }
    
}

void AudioManager::onChangeDecay(float& value)
{
    m_fft.setPeakDecay(value);
}

float AudioManager::getAudioMax()
{
    return m_audioMax;
}


float AudioManager::getMaxSound()
{
    
    float avrPeak = 0;
    vector<float> peakData = m_fft.getFftPeakData();
    //vector<float> peakData = m_fft.getFftRawData();
    
    
    if(peakData.size() <= m_numPeaks){
        return avrPeak;
    }
    
    for(int i=0; i<= m_numPeaks; i++)
    {
        avrPeak+=peakData[i];
    }
    
    
    avrPeak/=m_numPeaks;
    
    //float maxSound = ofMap(m_fft.getAveragePeak(), 0.0, 0.6, 0.0, 1.0, true);
    float maxSound = ofMap(avrPeak, 0.0, m_volume, 0.0, 1.0, true);
    return maxSound;
}



