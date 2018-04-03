/*
 *  GuiManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "GuiManager.h"
#include "GuiTheme.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "SHOW";
const string GuiManager::PRESETS_PREFIX = "xmls/Presets_";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
    //! Intentionally left empty
}

GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;
    
    Manager::setup();

    this->setupGuiParameters();
    this->setupScenesGui();
    this->setupPresetsGui();
    this->setupGuiEvents();
    this->loadGuiValues();
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{

    ofxDatGuiLog::quiet();
    m_gui.setPosition(ofxDatGuiAnchor::TOP_LEFT);
    m_gui.setAssetPath(ofToDataPath("fonts/"));
    //m_gui.setAssetPath("../Resources/data/fonts/");
    m_gui.setTheme(new GuiTheme());
    

    int margin =  LayoutManager::MARGIN;
    m_gui.setAutoDraw(false);
    auto pos = m_gui.getPosition();
    m_gui.setPosition(pos.x + margin, pos.y + margin);
    m_gui.addHeader(GUI_SETTINGS_NAME, true);
    
    // add some components //
    //m_gui.addLabel("PrimaveraSound GUI");
    
    m_gui.addFRM();
    m_gui.addToggle("Fullscreen");
    auto toggle = m_gui.getToggle("Fullscreen");
    toggle->setChecked(true);
    m_gui.addButton("* Save GUI");
    
    m_gui.addBreak();
    
}

void GuiManager::setupPresetsGui()
{
    auto layoutManager = &AppManager::getInstance().getLayoutManager();
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    
    m_sceneTransitionTime.set("TransitionTime", 0.5, 0.0, 3.0);
    m_sceneTransitionTime.addListener(sceneManager, &SceneManager::onTransitionTimeChange);
    m_parameters.add(m_sceneTransitionTime);
    
    m_speed.set("Speed", 0.5, 0.0, 4.0);
    m_presets.add(m_speed);
    
    m_size.set("Size", 0.5, 0.0, 1.0);
    m_presets.add(m_size);
    
    m_hue.set("Hue", 0.0, 0.0, 255.0);
    m_presets.add(m_hue);
    
    m_saturation.set("Saturation", 0.0, 0.0, 255.0);
    m_presets.add(m_saturation);
    
    m_value.set("Value", 255.0, 0.0, 255.0);
    m_presets.add(m_value);
    
    m_brightness.set("Brightness", 1.0, 0.0, 1.0);
    m_presets.add(m_brightness);
    
    m_contrast.set("Contrast", 1.0, 0.0, 2.0);
    m_presets.add(m_contrast);
    
    m_alpha.set("Alpha", 1.0, 0.0, 1.0);
    m_presets.add(m_alpha);
    
    
    ofxDatGuiFolder* folder = m_gui.addFolder("GENERAL", ofColor::purple);
    folder->addSlider(m_sceneTransitionTime);
    folder->addSlider(m_speed);
    folder->addSlider(m_size);
    folder->addSlider(m_hue);
    folder->addSlider(m_saturation);
    folder->addSlider(m_value);
    folder->addSlider(m_brightness);
    folder->addSlider(m_contrast);
    //folder->addSlider(m_alpha);
    folder->expand();
    m_gui.addBreak();
}


void GuiManager::setupScenesGui()
{
    auto sceneManager = &AppManager::getInstance().getSceneManager();
    vector<string> opts;
    
    for(int i = 0; i < sceneManager->getNumberScenes(); i++)
    {
        opts.push_back(sceneManager->getSceneName(i));
    }
    
    string label = "SCENES";
    
    m_gui.addDropdown(label, opts);
    auto menu = m_gui.getDropdown(label);
    //menu->expand(); //let's have it open by default
    menu->setStripeColor(ofColor::pink);
    for (int i=0; i<menu->size(); i++) menu->getChildAt(i)->setStripeColor(ofColor::pink);
    m_gui.addBreak();

}


void GuiManager::setupGuiEvents()
{
    m_gui.onDropdownEvent(this, &GuiManager::onDropdownEvent);
    m_gui.onColorPickerEvent(this, &GuiManager::onColorPickerEvent);
    m_gui.onButtonEvent(this, &GuiManager::onButtonEvent);
    m_gui.onToggleEvent(this, &GuiManager::onToggleEvent);
    m_gui.onMatrixEvent(this, &GuiManager::onMatrixEvent);
}

void GuiManager::update()
{
    m_gui.update();
}

void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    
    ofEnableSmoothing();
    ofEnableAlphaBlending();
        m_gui.draw();
    ofDisableAlphaBlending();
    ofDisableSmoothing();
    
}


void GuiManager::saveGuiValues()
{
    ofXml xml;
    xml.serialize(m_parameters);
    xml.save(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    ofXml xml(GUI_SETTINGS_FILE_NAME);
    xml.deserialize(m_parameters);
}

void GuiManager::savePresetsValues(const string& sceneName)
{
    ofXml xml;
    xml.serialize(m_presets);
    string xmlName = PRESETS_PREFIX + sceneName +".xml";
    xml.save(xmlName);
    
    ofLogNotice() <<"GuiManager::savePresetsValues -> " << xmlName;
}

void GuiManager::loadPresetsValues(const string& sceneName)
{
    ofXml xml;
    string xmlName = PRESETS_PREFIX + sceneName +".xml";
    xml.load(xmlName);
    xml.deserialize(m_presets);
    
    ofLogNotice() <<"GuiManager::loadPresetsValues -> " << xmlName;
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    int margin =  LayoutManager::MARGIN;
    ofPushStyle();
    ofSetColor(15);
    ofDrawRectangle( m_gui.getPosition().x - margin, 0, m_gui.getWidth() + 2*margin, ofGetHeight());
    ofPopStyle();
}



void GuiManager::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    cout << "onDropdownEvent: " << e.target->getName() << " Selected" << endl;
    
    if(e.target->getName() == "SCENES")
    {
        AppManager::getInstance().getSceneManager().changeScene(e.child);
        //m_gui.getDropdown(e.target->getName())->expand();
        m_gui.getDropdown(e.target->getName())->setLabel("SCENES:" + e.target->getLabel());
    }
    
    
}

void GuiManager::onColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
    cout << "onColorPickerEvent: " << e.target->getName() << " Selected" << endl;
    
    if (e.target->getName() == "COLOR MODE"){
        
    }
    
}

void GuiManager::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "onButtonEvent: " << e.target->getName() << " Selected" << endl;
    
    
}


void GuiManager::onToggleEvent(ofxDatGuiToggleEvent e)
{
    cout << "onToggleEvent: " << e.target->getName() << " Selected" << endl;
    
    if (e.target->getName() == "Fullscreen"){
        AppManager::getInstance().getLayoutManager().onFullScreenChange( e.target->getChecked());
    }
    
    
   
   
}

void GuiManager::onMatrixEvent(ofxDatGuiMatrixEvent e)
{
    //cout << "onMatrixEvent " << e.child << " : " << e.enabled << endl;
    
}



void GuiManager::onSceneChange(const string &sceneName)
{
    int index = AppManager::getInstance().getSceneManager().getIndex(sceneName);
    this->onSceneChange(index);
}

void GuiManager::onSceneChange(int sceneIndex)
{
    string dropBoxName = "SCENES";
    auto menu = m_gui.getDropdown(dropBoxName);
    menu->select(sceneIndex);
    string label =  menu->getChildAt(sceneIndex)->getLabel();
    menu->setLabel(dropBoxName + ":" + label);
    AppManager::getInstance().getSceneManager().changeScene(sceneIndex);
}


