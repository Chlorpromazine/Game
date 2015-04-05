#ifndef _MENU_H_
#define _MENU_H_

#include "font.h"

class menu{
private:
	SDL_Surface* surface;
public:
	
	static menu Menu;
	void loadTextMainMenu(SDL_Surface* screen, TTF_Font* fontType);
	void loadTextOptionMenu(SDL_Surface* screen, TTF_Font* fontType);
	void loadMenu(SDL_Surface* screen);
	void clearScreen(SDL_Surface* screen);
};

#endif