/*
 *  WireFrameScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 01/04/18.
 *
 */

#pragma once

#include "ofxScene.h"


class Particle
{
    
public:
    
    //! Constructor
    Particle();
    
    //! Destructor
    ~Particle(){}
    
    void setup();
    
    void update();
    
    void draw();
    
private:
    
    void stayOnScreen();
    
    
public:
    
    ofPoint m_position;
    ofPoint m_speed;
    
};


class WireFrameScene : public ofxScene {

public:

    //! Constructor
    WireFrameScene();
    
    //! Destructor
    ~WireFrameScene();
    
    //! Set up the scene
    void setup();

    //! Update the scene
    void update();

    //! Draw the scene
    void draw();
    
    //! Called when fading in
    void willFadeIn();

    //! Called when to start drawing
    void willDraw();

    //! Called fading out
    void willFadeOut();

    //! Called when exit
    void willExit();
    
    
private:
    

    void setupParticles();
    
    void setupFbo();
    
    void updateParticles();
    
    void updateFbo();
    
    void drawParticles();

    void setParameters(float radius, float velocity);
    
private:
    
    
    typedef vector< Particle > Particles;
    
    Particles   m_particles;
    
    ofFbo       m_fbo;
    
    float       m_radius;
    float       m_velocity;
    float       m_distanceThreshold;

};




