/*
 *  WaterScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */

#pragma once

#include "ofxScene.h"

class WaterScene : public ofxScene {

public:

    //! Constructor
    WaterScene();
    
    //! Destructor
    ~WaterScene();
    
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
    

    void setupShader();
    
    void updateShader();
    
    void drawShader();
    
private:
    
    
    ofShader 	m_shader;

};




