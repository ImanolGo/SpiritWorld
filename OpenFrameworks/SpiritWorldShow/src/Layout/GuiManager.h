/*
 *  GuiManager.h
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#pragma once

#include "Manager.h"
#include "ofxDatGui.h"

//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! Update the gui
    void update();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    void onSetVideoMode(bool& value);
    
    void onSetShowMode(bool& value);
    
    void onSetAudioMode(bool& value);
    
    int getWidth() {return GUI_WIDTH;}
    
    int getHeight() {return m_gui.getHeight();}
    
    ofPoint  getPosition() {return m_gui.getPosition();}
    
    void setSceneTransitionTime(float value) {m_sceneTransitionTime = value;}
    
    void onSceneChange(const string& sceneName);
    
    void onSceneChange(int sceneIndex);
    
    
    void onDropdownEvent(ofxDatGuiDropdownEvent e);

    void onColorPickerEvent(ofxDatGuiColorPickerEvent e);
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    
    void onToggleEvent(ofxDatGuiToggleEvent e);
    
    void onMatrixEvent(ofxDatGuiMatrixEvent e);
    
private:
    
    void setupGuiParameters();
    
    void setupScenesGui();
    
    void setupGuiEvents();
    
    void drawRectangle();
    

private:
    

    ofxDatGui               m_gui;
    
    ofParameterGroup        m_parameters;
    
    ofParameter<float>      m_sceneTransitionTime;
    
   
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================

