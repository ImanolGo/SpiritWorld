/*
 *  KeyboardManager.cpp
 *  Spirit World Show
 *
 *  Created by Imanol Gomez on 27/02/18.
 *
 */


#include "KeyboardManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
  
    if(key == 'g' || key == 'G') {
        AppManager::getInstance().getGuiManager().toggleGui();
    }
    
    if(key == 'b' || key == 'B') {
        AppManager::getInstance().getSceneManager().changeScene("BLANK");
    }
    
//    if(key == '1') {
//        AppManager::getInstance().getSceneManager().changeScene("WATER");
//    }
//
//    if(key == '2') {
//        AppManager::getInstance().getSceneManager().changeScene("DOTS");
//    }
//
//    if(key == '3') {
//        AppManager::getInstance().getSceneManager().changeScene("MESH");
//    }
//
//    if(key == '4') {
//        AppManager::getInstance().getSceneManager().changeScene("EXPLOSION");
//    }
//
//    if(key == '5') {
//        AppManager::getInstance().getSceneManager().changeScene("SPARKLES");
//    }
//
//    if(key == '6') {
//        AppManager::getInstance().getSceneManager().changeScene("SPARKLES");
//    }
//
//    if(key == '7') {
//        AppManager::getInstance().getSceneManager().changeScene("END");
//    }
//
//    if(key == 'f' || key == 'F') {
//        AppManager::getInstance().getLayoutManager().toggleDrawMode(1);
//    }
    
    
    if(key == 'p' || key == 'P') {
        AppManager::getInstance().getLayoutManager().toggleDrawMode(2);
    }
    
    if(key == 'n' || key == 'N') {
        AppManager::getInstance().getLayoutManager().toggleDrawMode(0);
    }
    
    if(key == ' ') {
        AppManager::getInstance().getLayoutManager().toggleDrawMode();
        if(AppManager::getInstance().getLayoutManager().getDrawMode() == 0){
            AppManager::getInstance().getGuiManager().showGui(true);
        }
        else{
            AppManager::getInstance().getGuiManager().showGui(false);
        }
    }

    
}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyReleased-> " + ofToString(key);
    
}










