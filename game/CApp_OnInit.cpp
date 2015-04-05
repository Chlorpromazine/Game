#include "Main.h"
 

bool CApp::OnInit() {
	
	//initialize fonts
	TTF_Init();
	
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
	
	font = font::Font.loadfont("C:/windows/fonts/times.ttf", 25);

	if ((Surf_Display = SDL_SetVideoMode(screenSizeX, screenSizeY, 32,0)) == NULL) {
        return false;
    }
 
    if((Surf_Test = CSurface::OnLoad("images\\tileset.bmp")) == NULL) {
        return false;
    }

	if((Surf_Char = CSurface::OnLoad("images\\char.bmp")) == NULL) {
        return false;
    }


	if((Surf_Spells = CSurface::OnLoad("images\\spells.bmp")) == NULL) {
        return false;
    }

	CSurface::Transparent(Surf_Char, 255, 255, 255);
	CSurface::Transparent(Surf_Spells, 255, 255, 255);
	animMainChar.SetFrameRate(200);

	if(Area::AreaControl.OnLoad("./map/1.area") == false) {
		return false;
	}
 
	

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
 
    return true;
}