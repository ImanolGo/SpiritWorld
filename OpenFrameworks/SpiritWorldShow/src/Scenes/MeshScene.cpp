/*
 *  MeshScene.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 01/04/18.
 *
 */


#include "MeshScene.h"
#include "AppManager.h"

MeshScene::MeshScene(): ofxScene("MESH"), m_meshWidth(8) ,m_meshHeight(14)
{
     this->setupMesh();
}

MeshScene::~MeshScene()
{
    //Intentionally left empty
}


void MeshScene::setup() {
    ofLogNotice(getName() + "::setup");
   
}

void MeshScene::setupMesh()
{
    //ofColor color = ofColor::white;
    auto color = AppManager::getInstance().getSettingsManager().getColor("GOLD");
    
    int meshSize = 100;
    int W = m_meshWidth;
    int H = m_meshHeight;
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();
    
    //Set up vertices
    for (int y=0; y<H; y++) {
        for (int x=0; x<W; x++) {
            m_mesh.addVertex(ofPoint((x - W/2) * meshSize, (y - H/2) * meshSize, 0 )); // adding texure coordinates allows us to bind textures to it later // --> this could be made into a function so that textures can be swapped / updated
            m_mesh.addTexCoord(ofPoint(x * (width / W), y * (height / H)));
            m_mesh.addColor(ofColor::white);
        }
    }
    
    //Set up triangles' indices
    for (int y=0; y<H-1; y++) {
        for (int x=0; x<W-1; x++) {
            int i1 = x + W * y;
            int i2 = x+1 + W * y;
            int i3 = x + W * (y+1);
            int i4 = x+1 + W * (y+1);
            m_mesh.addTriangle( i1, i2, i3 );
            m_mesh.addTriangle( i2, i4, i3 );
        }
    }
}


void MeshScene::update()
{
    this->updateMesh();
}

void MeshScene::updateMesh()
{
  // auto color = AppManager::getInstance().getSettingsManager().getColor("GOLD");
    
    float timeScale = AppManager::getInstance().getGuiManager().getSpeed();
    float size = AppManager::getInstance().getGuiManager().getSize();
    size = ofMap(size, 0.0, 1.0, 0.0, 300);
    
    //Change vertices
    for (int y=0; y< m_meshHeight; y++) {
        for (int x=0; x< m_meshWidth; x++) {
            
            //Vertex index
            int i = x + m_meshWidth * y;
            ofPoint p = m_mesh.getVertex( i );
            
            //Change z-coordinate of vertex
            float noise =  ofNoise(x * 0.5, y * 0.5, ofGetElapsedTimef() * timeScale);
            p.z = ofMap(noise, 0.0, 1.0, 0.0, size);
            m_mesh.setVertex( i, p );
            float brightness = ofMap(noise, 0.3, 1.0, 0, 255,true);
            //auto color = AppManager::getInstance().getSettingsManager().getColor("GOLD");
            //color.setHsb(26, 121, 100);
            ofColor c = ofColor::white;
           // auto color = m_mesh.getColor(i);
            c.setBrightness(brightness);
            m_mesh.setColor(i ,c);
            
//            float brighntness = p.z;
//            //Change color of vertex
//            auto col = m_mesh.getColor(i);
//            col.setBrightness(brighntness);
//            m_mesh.setColor(i , col);
        }
    }
}

void MeshScene::draw()
{
    ofBackground(0,0,0);
    this->drawMesh();
}

void MeshScene::drawMesh()
{
    float width = AppManager::getInstance().getSettingsManager().getAppWidth();
    float height = AppManager::getInstance().getSettingsManager().getAppHeight();

    ofSetLineWidth(20);
    ofPushMatrix();
    //Move the coordinate center to screen's center
    ofTranslate( width/2, height/2, 0 );
    m_mesh.draw();
    m_mesh.drawWireframe();
    ofPopMatrix();
    
}

void MeshScene::willFadeIn() {
     ofLogNotice("MeshScene::willFadeIn");
     AppManager::getInstance().getGuiManager().loadPresetsValues(getName());
}

void MeshScene::willDraw() {
    ofLogNotice("MeshScene::willDraw");
}

void MeshScene::willFadeOut() {
    ofLogNotice("MeshScene::willFadeOut");
    AppManager::getInstance().getGuiManager().savePresetsValues(getName());
}

void MeshScene::willExit() {
     ofLogNotice("MeshScene::willExit");
}
