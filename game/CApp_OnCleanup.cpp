#include "Main.h"
 
void CApp::OnCleanup() {
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
	Area::AreaControl.OnCleanup();

    SDL_Quit();
}