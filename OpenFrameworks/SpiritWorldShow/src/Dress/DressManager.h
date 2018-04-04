/*
 *  DressManager.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 04/04/18.
 *
 */


#pragma once

#include "Manager.h"
#include "ImageVisual.h"

//========================== class DressManager ==============================
//============================================================================
/** \class DressManager DressManager.h
 *	\brief Class managing the dress visuals
 *	\details it creates and updates the dress visuals
 */


class DressManager: public Manager
{
    
    public:

        //! Constructor
        DressManager();

        //! Destructor
        ~DressManager();

        //! Setup the Dress Manager
        void setup();

        //! Update the Dress Manager
        void update();
    
        //! Draw the Dress Manager
        void draw();
    
        float getWidth() const {return m_costumeImage->getOriginalWidth();}
    
        float getHeight() const {return m_costumeImage->getOriginalHeight();}
    
        void pressedAlt(bool isAltPressed) {m_isAltPressed = isAltPressed;}
    
        void pressedCtrl(bool value) {m_isCtrlpressed = value;}
    
    
        void pressedBackSpace();
    
        void pressedMouse(ofMouseEventArgs &e);
    
        void toggleShowChannels();
    
    private:
    
        void setupImage();
    
        void drawCostumeLeds();
    
    
        ofPtr<ImageVisual>  m_costumeImage;
    
        bool                m_isAltPressed;
        bool                m_isCtrlpressed;
        bool                m_showChannels;
    
};



