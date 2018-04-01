/*
 *  MeshScene.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 01/04/18.
 *
 */

#pragma once

#include "ofxScene.h"

class MeshScene : public ofxScene {

public:

    //! Constructor
    MeshScene();
    
    //! Destructor
    ~MeshScene();
    
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
    

    void setupMesh();
    
    void updateMesh();
    
    void drawMesh();
    
private:
    
    ofMesh  m_mesh;
    int     m_meshWidth;
    int     m_meshHeight;

};




