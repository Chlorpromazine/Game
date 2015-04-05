#include "Main.h"

CApp::CApp() {
	//surfaces
    Surf_Display = NULL;
	Surf_Char = NULL;
	Surf_WeapSword1 = NULL;
	Surf_Spells = NULL;
	Running = true;
	
	//fps
	timestep = 15;
	accumulator = 0.0;
	lastUpdate = SDL_GetTicks() ;

	//movement of main character
   
	facingSide = 0;

	moveLeft = 0;
	moveRight = 0;
	moveUp = 0;
	moveDown = 0;
    
	//mouse location
	mLocX = 0;
	mLocY = 0;

	//mouse click
	mouseLeftClicked = 0;
	intervalClick = mouseHoldLInterval;

	//map
	areaNum = 0;
	newAreaNum = 1;
	
	//menu
	choosenMenu = 0;
	loadedMenu = 0;
	//animate char
	animMainChar.Oscillate = false;
	animMainChar.MaxFrames = 4;
}

CApp::~CApp()
{
	
}

int CApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }
 
    SDL_Event Event;
 
    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }
 
        OnLoop();
        OnRender();
    }
 
    OnCleanup();
 
    return 0;
}
 
int main(int argc, char* argv[]) {

	
    CApp theApp;
	//VLDReportLeaks();
    return theApp.OnExecute();
}


