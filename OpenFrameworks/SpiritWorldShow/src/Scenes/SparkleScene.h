/*
 *  SparkleScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 02/04/18.
 *
 */

#pragma once

#include "ofxScene.h"
#include "ImageVisual.h"


class Sparkle
{
    
public:
    
    //! Constructor
    Sparkle();
    
    //! Destructor
    ~Sparkle(){}
    
    void setup();
    
    void update();
    
    void draw();
    
private:
    
    void setupImage();
    
    void stayOnScreen();
    
    
public:
    
    ofPoint m_position;
    ofPoint m_speed;
    
private:
    
    ImageVisual m_sparkleVisual;
    
};


class SparkleScene : public ofxScene {

public:

    //! Constructor
    SparkleScene();
    
    //! Destructor
    ~SparkleScene();
    
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
    
    
    typedef vector< Sparkle > SparkleVector;
    
    SparkleVector   m_particles;
    ofFbo       m_fbo;

};




