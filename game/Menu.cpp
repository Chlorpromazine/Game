
#include "Menu.h"

menu menu::Menu;

//loads the text for the menu
void menu::loadTextMainMenu(SDL_Surface* screen, TTF_Font* fontType)
{
	
	surface = font::Font.drawtext(fontType, 255, 255, 255, 70, 0, 0, 0, 0, "Play Game", solid);
	
	CSurface::OnDraw(screen, surface, screenSizeX / 2 - surface->w/2, screenSizeY / 2 + 125);

	surface = font::Font.drawtext(fontType, 255, 255, 255, 70, 0, 0, 0, 0, "Options", solid);

	CSurface::OnDraw(screen, surface, screenSizeX / 2 - surface->w / 2, screenSizeY / 2 + 175);

	surface = font::Font.drawtext(fontType, 255, 255, 255, 70, 0, 0, 0, 0, "Map editor", solid);

	CSurface::OnDraw(screen, surface, screenSizeX / 2 - surface->w / 2, screenSizeY / 2 + 225);
	
}

void menu::loadTextOptionMenu(SDL_Surface* screen, TTF_Font* fontType)
{
	surface = font::Font.drawtext(fontType, 255, 255, 255, 70, 0, 0, 0, 0, "Back", solid);

	CSurface::OnDraw(screen, surface, screenSizeX / 2 - surface->w / 2, screenSizeY / 2 + 125);

	surface = font::Font.drawtext(fontType, 255, 255, 255, 70, 0, 0, 0, 0, "Test", solid);

	CSurface::OnDraw(screen, surface, screenSizeX / 2 - surface->w / 2, screenSizeY / 2 + 175);
}

//refreshes the screen of the menu
void menu::loadMenu(SDL_Surface* screen)
{
	SDL_Flip(screen);
}

void menu::clearScreen(SDL_Surface* screen)
{
	SDL_FillRect(screen, NULL, 0x000000);
}