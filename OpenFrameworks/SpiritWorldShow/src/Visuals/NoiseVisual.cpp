/*
 *  NoiseVisual.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */

#include "AppManager.h"
#include "ResourceManager.h"

#include "NoiseVisual.h"


NoiseVisual::NoiseVisual(): BasicVisual(), m_centred(false)
{
    //Intentionally left empty
}


NoiseVisual::NoiseVisual(const ofVec3f& pos, float width, float height, bool centred):
    BasicVisual(pos, width, height),  m_centred(centred)
{
    //Intentionally left empty
}

NoiseVisual::~NoiseVisual()
{
    //Intentionally left empty
}


void NoiseVisual::draw()
{

    ofPushMatrix();
    ofPushStyle();
    
        ofSetColor(m_color);

        ofTranslate(m_position);
    

        if(m_centred){
            ofSetRectMode(OF_RECTMODE_CENTER);
        }
        else{
            ofSetRectMode(OF_RECTMODE_CORNER);
        }

        ofRotateX(m_rotation.x);
        ofRotateY(m_rotation.y);
        ofRotateZ(m_rotation.z);
    
        ofScale(m_scale.x, m_scale.y);
    
        //AppManager::getInstance().getNoiseManager().draw(0,0, m_width, m_height);
        //AppManager::getInstance().getNoiseManager().draw();

    ofPopStyle();
    ofPopMatrix();
}


