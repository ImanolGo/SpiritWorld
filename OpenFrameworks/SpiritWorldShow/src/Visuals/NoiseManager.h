/*
 *  NoiseManager.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */

#pragma once

#include "Manager.h"


//========================== class NoiseManager ==============================
//============================================================================
/** \class NoiseManager NoiseManager.h
 *	\brief Class managing the noise visuals
 *	\details it creates and updates noise visuals, as well it provides methods to change it in real time
 */


class NoiseManager: public Manager
{
    
    public:

        //! Constructor
        NoiseManager();

        //! Destructor
        ~NoiseManager();

        //! Setup the Noise Manager
        void setup();

        //! Update the Noise Manager
        void update();
    
        //! Draw the Noise Manager
        void draw();
    
        //! Draw the Noise Manager
        void draw(float x, float y, float w, float h);
    
        void onSpeedChange(float& value) {m_noiseIncrement1 = value;}
    
        void onSetColor(ofColor& color) {m_color = color;}
    
        void onScaleChange(float value);
    
        void onMinChange(float value) {m_mapMin = value;}
    
        void onMaxChange(float value) {m_mapMax = value;}
    
        
    private:
    
        void setupShader();
    
        void setupParameters();
    
        void setupPlane();
    
        void setupFbo();
    
        void updateNoise();
    
        void updateFbo();
    
    private:
  
        ofTexture             m_texture;
        ofFbo               m_fbo;    
        ofColor             m_color;
        ofShader            m_noiseShader;
        ofPlanePrimitive    m_plane;
    
        ofVec2f     m_noiseStep;
        ofVec2f     m_noiseScale;
        float       m_noiseIncrement1, m_noiseIncrement2;
        float       m_mapMin, m_mapMax;

};




