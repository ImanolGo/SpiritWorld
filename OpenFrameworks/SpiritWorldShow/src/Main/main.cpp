#include "ofMain.h"
#include "SpiritWorldShowApp.h"

//========================================================================
int main( ){

    ofSetupOpenGL(1024,768, OF_WINDOW);            // <-------- setup the GL context

	ofRunApp( new SpiritWorldShowApp());

}