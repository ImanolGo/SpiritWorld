/*
 *  NoiseVisual.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */

#pragma once

#include "BasicVisual.h"


//=========================== class NoiseVisual ==============================
//============================================================================
/** \class NoiseVisual NoiseVisual.h
 *	\brief Represents an noise visual
 *	\details The class uses the the NoiseManager to draw it as a visual
 */

class NoiseVisual: public BasicVisual
{

public:

    //! Constructor
    NoiseVisual();
    
    //! Constructor
    NoiseVisual(const ofVec3f& pos, float width, float height, bool centred = false);

    //! Destructor
    virtual ~NoiseVisual();

	//! Draws the image visual
	virtual void draw();
    
protected:
    
    bool     m_centred;          ///< defines if the visual should be centred or not

};


