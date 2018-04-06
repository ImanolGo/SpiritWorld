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

#include "BasicVisual.h"
#include "VisualEffects.h"

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
    static const string PRESETS_PREFIX;
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
    
    void savePresetsValues(const string& sceneName);
    
    void loadPresetsValues(const string& sceneName);
    
    float getSpeed(){return m_speed;}
    
    float getSize(){return m_size;}
    
    float getHue(){return m_hue;}
    
    float getAlpha(){return m_alpha;}
    
    float getBrightness(){return m_brightness;}
    
    float getValue(){return m_value;}
    
    float getSaturation(){return m_saturation;}
    
    float getContrast(){return m_contrast;}
    
    void addSpeedEffect(float targetSpeed, double duration);
    
    void addSizeEffect(float targetSize, double duration);
    
    void setHue(float value) {m_hue = value;}
    
    void setSaturation(float value) {m_saturation = value;}
    
    void setValue(float value) {m_value = value;}
    
    void setSpeed(float value) {m_speed = value;}
    
    void setSize(float value) {m_size = value;}
    
    void setContrast(float value) {m_contrast = value;}
    
    void setAudioPower(float value) {m_audioPower = value;}
    
    void onChangeViolin(bool value);
    
    void onChangeAudio(bool value);
    
private:
    
    void setupGuiParameters();
    
    void setupScenesGui();
    
    void setupPresetsGui();
    
    void setupCommunicationsGui();
    
    void setupAudioGui();
    
    void setupGuiEvents();
    
    void drawRectangle();
    
    void setupEffects();
    
    void updateEffects();
    

private:
    

    ofxDatGui               m_gui;
    
    ofParameterGroup        m_parameters;
    ofParameterGroup        m_presets;
    
    ofParameter<float>      m_sceneTransitionTime;
    ofParameter<float>      m_speed;
    ofParameter<float>      m_size;
    ofParameter<float>      m_value;
    ofParameter<float>      m_brightness;
    ofParameter<float>      m_saturation;
    ofParameter<float>      m_hue;
    ofParameter<float>      m_contrast;
    ofParameter<float>      m_alpha;
    
    ofParameter<float>      m_audioDecay;
    ofParameter<float>      m_audioVolume;
    ofParameter<float>      m_audioPower;
    ofParameter<int>        m_audioNumPeaks;
    
    ofPtr<BasicVisual>      m_speedVisual;
    ofPtr<MoveVisual>       m_speedEffect;
    ofPtr<BasicVisual>      m_sizeVisual;
    ofPtr<MoveVisual>       m_sizeEffect;
    
    
   
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


