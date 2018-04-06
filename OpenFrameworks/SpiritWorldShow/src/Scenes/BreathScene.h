/*
 *  BreathScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 06/04/18.
 *
 */

#pragma once


#include "ofxScene.h"

class BreathScene : public ofxScene {

public:

    //! Constructor
    BreathScene();
    
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
    
    void updateColor();
    
private:
    
    ofColor   m_color;

};

