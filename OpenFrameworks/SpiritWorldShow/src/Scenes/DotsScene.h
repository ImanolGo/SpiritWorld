/*
 *  DotsScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 02/04/18.
 *
 */

#pragma once

#include "ofxScene.h"
#include "ImageVisual.h"


class Dot
{
    
public:
    
    //! Constructor
    Dot();
    
    //! Destructor
    ~Dot(){}
    
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
    
    ImageVisual m_dotVisual;
    
};


class DotsScene : public ofxScene {

public:

    //! Constructor
    DotsScene();
    
    //! Destructor
    ~DotsScene();
    
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
    
    
    typedef vector< Dot > DotVector;
    
    DotVector   m_particles;
    ofFbo       m_fbo;

};




