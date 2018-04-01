/*
 *  SpiritWorldShowApp.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "AppManager.h"

#include "SpiritWorldShowApp.h"

//--------------------------------------------------------------
void SpiritWorldShowApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void SpiritWorldShowApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void SpiritWorldShowApp::draw(){
    AppManager::getInstance().draw();
}

void SpiritWorldShowApp::exit()
{
    ofLogNotice() <<"SpiritWorldShowApp::exit";
    AppManager::getInstance().exit();
}


//--------------------------------------------------------------
void SpiritWorldShowApp::keyPressed(int key){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::keyReleased(int key){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::windowResized(int w, int h)
{
    AppManager::getInstance().getLayoutManager().windowResized(w,h);
}

//--------------------------------------------------------------
void SpiritWorldShowApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void SpiritWorldShowApp::dragEvent(ofDragInfo dragInfo){

}
