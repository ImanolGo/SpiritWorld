/*
 *  LayoutManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"


#include "LayoutManager.h"



#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"


#include "LayoutManager.h"


const int LayoutManager::MARGIN = 20;
const int LayoutManager::FRAME_MARGIN = 2;
const string LayoutManager::LAYOUT_FONT =  "fonts/open-sans/OpenSans-Semibold.ttf";
const string LayoutManager::LAYOUT_FONT_LIGHT =  "fonts/open-sans/OpenSans-Light.ttf";

LayoutManager::LayoutManager(): Manager(), m_drawMode(0)
{
    //Intentionally left empty
}


LayoutManager::~LayoutManager()
{
    ofLogNotice() <<"LayoutManager::Destructor";
}


void LayoutManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    this->setupFbo();
    this->setupWindowFrames();
    this->setupSyphon();
    this->setupShader();
    
    this->createTextVisuals();
    this->createSvgVisuals();
    this->createImageVisuals();
    //this->addVisuals();
    
    ofLogNotice() <<"LayoutManager::initialized";
    
}


void LayoutManager::setupFbo()
{
    int margin = MARGIN;
    
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    
    m_fbo.allocate(width, height, GL_RGBA);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
    m_fboColor.allocate(width, height, GL_RGBA);
    m_fboColor.begin(); ofClear(0); m_fboColor.end();
    
    m_previewFbo.allocate(width, height, GL_RGBA);
    m_previewFbo.begin(); ofClear(0); m_previewFbo.end();
    
}

void LayoutManager::setupSyphon()
{
    string name = AppManager::getInstance().getSettingsManager().getSyphonName();
    m_syphonServer.setName(name);
    
    ofLogNotice() <<"VideoOutputManager::setupSyphon << Setting up Syphon server: " << name;
}

void LayoutManager::setupShader()
{
    if(ofIsGLProgrammableRenderer()){
        m_shader.load("shaders/shadersGL3/BrightnessContrast");
    }
    else{
        m_shader.load("shaders/shadersGL2/BrightnessContrast");
    }
}


void LayoutManager::resetWindowRects()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height  = AppManager::getInstance().getSettingsManager().getAppHeight();
    float ratio = width/ height;
    float frame_width = ofGetWidth() - AppManager::getInstance().getGuiManager().getWidth() - 2*MARGIN;
    
    if(frame_width >= ofGetHeight())
    {
        m_windowRect.height =  height - 2*MARGIN;
        m_windowRect.width  = m_windowRect.height*ratio;
        
        if(m_windowRect.width*2 + 4*MARGIN > frame_width){
            m_windowRect.width  = frame_width/2 - 2*MARGIN;
            m_windowRect.height = m_windowRect.width/ratio;
        }
        
        m_previewWindowRect.width = m_windowRect.width;
        m_previewWindowRect.height = m_windowRect.height;
        
        
        
        m_windowRect.x = AppManager::getInstance().getGuiManager().getWidth() +  frame_width/2 - m_previewWindowRect.width + MARGIN;
        m_windowRect.y = ofGetHeight()*0.5 - m_windowRect.height/2;
        
        m_previewWindowRect.x = AppManager::getInstance().getGuiManager().getWidth() +  frame_width/2  + 2*MARGIN;
        m_previewWindowRect.y =  ofGetHeight()*0.5 - m_previewWindowRect.height/2;
    }
    else
    {
        m_windowRect.height = ofGetHeight()/2 - 2*MARGIN; ;
        m_windowRect.width = m_windowRect.height*ratio;
        
        if(m_windowRect.width + 2*MARGIN > frame_width){
            m_windowRect.width  = frame_width - 2*MARGIN;
            m_windowRect.height = m_windowRect.width/ratio;
        }
        
        m_previewWindowRect.width = m_windowRect.width;
        m_previewWindowRect.height =  m_windowRect.height;
        
        m_windowRect.x =  AppManager::getInstance().getGuiManager().getWidth() +  frame_width/2 - m_previewWindowRect.width/2 + 2*MARGIN;
        m_previewWindowRect.x = m_windowRect.x;
        m_windowRect.y = ofGetHeight()/2 -  m_previewWindowRect.height - MARGIN;
        m_previewWindowRect.y = ofGetHeight()/2 + MARGIN;
        
        //m_windowRect.y + m_windowRect.height + 2*MARGIN  + m_textVisuals["Preview"]->getHeight();
    }

}

void LayoutManager::setupWindowFrames()
{
    this->resetWindowRects();
    this->resetWindowFrames();
    
    float width = ofGetScreenWidth();
    float height = ofGetScreenHeight()/80;
    
    
    ofColor color = AppManager::getInstance().getSettingsManager().getColor("FrameRectangle");
    m_windowFrame.setColor(color);
    m_previewWindowFrame.setColor(color);
}


void LayoutManager::resetWindowFrames()
{
    m_windowFrame.setPosition(ofPoint( m_windowRect.x - FRAME_MARGIN, m_windowRect.y - FRAME_MARGIN, 0));
    m_windowFrame.setWidth(m_windowRect.width + 2*FRAME_MARGIN); m_windowFrame.setHeight(m_windowRect.height + 2*FRAME_MARGIN);
    
    m_previewWindowFrame.setPosition(ofPoint( m_previewWindowRect.x - FRAME_MARGIN, m_previewWindowRect.y - FRAME_MARGIN, 0));
    m_previewWindowFrame.setWidth(m_previewWindowRect.width + 2*FRAME_MARGIN); m_previewWindowFrame.setHeight(m_previewWindowRect.height + 2*FRAME_MARGIN);
}


void LayoutManager::update()
{
    if(!m_initialized)
        return;
    
    this->updateFbos();
    this->updateSyphon();
    
}

void LayoutManager::updateFbos()
{
    this->updateOutputFbo();
    this->updatePreviewFbo();
}

void LayoutManager::updateOutputFbo()
{
    auto hue = AppManager::getInstance().getGuiManager().getHue();
    auto saturation = AppManager::getInstance().getGuiManager().getSaturation();
    auto value = AppManager::getInstance().getGuiManager().getValue();
    ofColor color; color.setHsb(hue, saturation, value);
    
    auto brightness = AppManager::getInstance().getGuiManager().getBrightness();
    auto contrast = AppManager::getInstance().getGuiManager().getContrast();
    
    
    ofEnableAlphaBlending();
    
    m_fboColor.begin();
    ofClear(0);
    ofSetColor(color);
    AppManager::getInstance().getSceneManager().draw();
    m_fboColor.end();
    
    m_fbo.begin();
    ofClear(0, 0, 0);
    
   
    m_shader.begin();
    m_shader.setUniform1f("brightness", brightness);
    m_shader.setUniform1f("contrast", contrast);
    
    //ofSetColor(color);
    m_fboColor.draw(0,0);
    
    m_shader.end();
    m_fbo.end();
    ofDisableAlphaBlending();
    
}

void LayoutManager::updatePreviewFbo()
{
    ofEnableAlphaBlending();
    m_previewFbo.begin();
    ofClear(0, 0, 0);
    
    
    m_previewFbo.end();
    ofDisableAlphaBlending();
    
}

void LayoutManager::updateSyphon()
{
    m_syphonServer.publishTexture(&m_fbo.getTexture());
}


void LayoutManager::createTextVisuals()
{
    float size = 20;
    float w = size*50;
    float h = size;
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y - h - 2*MARGIN;
    ofPoint pos = ofPoint(x, y);
    string text = "Output";
    string fontName = LAYOUT_FONT_LIGHT;
    
    
    auto textVisual = ofPtr<TextVisual>(new TextVisual(pos,w,h,true));
    textVisual->setText(text, fontName, size, ofColor::white);
    m_textVisuals[text] = textVisual;
    
    
    x =  m_previewWindowRect.x + m_previewWindowRect.getWidth()*0.5;
    y =  m_previewWindowRect.y - h - 2*MARGIN;
    text = "Preview";
    textVisual = ofPtr<TextVisual>(new TextVisual(pos,w,h,true));
    textVisual->setText(text, fontName, size, ofColor::white);
    m_textVisuals["Preview"] = textVisual;
    
}

void LayoutManager::resetWindowTitles()
{
    float x =  m_windowRect.x + m_windowRect.getWidth()*0.5;
    float y =  m_windowRect.y -  m_textVisuals["Output"]->getHeight()*0.5 + MARGIN;
    ofPoint pos = ofPoint(x, y);
    m_textVisuals["Output"]->setPosition(pos);
    
    
    pos.x =  m_previewWindowRect.x + m_previewWindowRect.getWidth()*0.5;
    pos.y =  m_previewWindowRect.y - m_textVisuals["Preview"]->getHeight()*0.5  + MARGIN;
    m_textVisuals["Preview"]->setPosition(pos);
}


void LayoutManager::createSvgVisuals()
{
    ///To implement in case we have text visuals
}


void LayoutManager::createImageVisuals()
{
    //this->createBackground();
}

void LayoutManager::createBackground()
{
}

void LayoutManager::addVisuals()
{
    int depthLevel = -1;
    for(SvgMap::iterator it = m_svgVisuals.begin(); it!= m_svgVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(TextMap::iterator it = m_textVisuals.begin(); it!= m_textVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
    
    for(ImageMap::iterator it = m_imageVisuals.begin(); it!= m_imageVisuals.end(); ++it){
        AppManager::getInstance().getViewManager().addOverlay(it->second,depthLevel);
    }
}


void LayoutManager::onFullScreenChange(bool value)
{
    if(value){
        ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
    }
    else{
        
        float width = 4*MARGIN + 2*AppManager::getInstance().getGuiManager().getWidth();
        float height = AppManager::getInstance().getGuiManager().getHeight() + 2*MARGIN;
        ofSetWindowShape(width,height);
    }
}

void LayoutManager::draw()
{
    if(!m_initialized)
        return;
    
    switch (m_drawMode)
    {
        case DRAW_NORMAL:  this->drawNormal(); break;
        case DRAW_OUTPUT:  this->drawOutput(); break;
        case DRAW_PREVIEW:  this->drawPreview(); break;
        default: this->drawNormal(); break;
    }
    
}


void LayoutManager::drawOutput()
{
    m_fbo.draw(0,0, ofGetWidth(), ofGetHeight());
}

void LayoutManager::drawPreview()
{
    m_previewFbo.draw(0,0, ofGetWidth(), ofGetHeight());
}

void LayoutManager::drawNormal()
{
    this->drawFbos();
    this->drawText();
}


void LayoutManager::drawText()
{
    for(auto textVisual: m_textVisuals){
        textVisual.second->draw();
    }
}

void LayoutManager::drawFbos()
{
    this->drawOutputFbo();
    this->drawPreviewFbo();
}


void LayoutManager::drawOutputFbo()
{
    m_windowFrame.draw();
    m_fbo.draw(m_windowRect.x,m_windowRect.y,m_windowRect.width,m_windowRect.height);
}

void LayoutManager::drawPreviewFbo()
{
    
    m_previewWindowFrame.draw();
    m_previewFbo.draw(m_previewWindowRect.x,m_previewWindowRect.y,m_previewWindowRect.width,m_previewWindowRect.height);
}

void LayoutManager::windowResized(int w, int h)
{
    if(!m_initialized){
        return;
    }
    
    this->resetWindowRects();
    this->resetWindowFrames();
    this->resetWindowTitles();
}

void LayoutManager::setFullScreen()
{
    ofSetWindowPosition(0,0);
    ofSetWindowShape(ofGetScreenWidth(),ofGetScreenHeight());
}

void LayoutManager::toggleDrawMode()
{
    if(m_drawMode == 0)
    {
        m_drawMode = 1;
    }
    else{
        m_drawMode = 0;
    }
    
}


