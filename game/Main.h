#ifndef _CAPP_H_
    #define _CAPP_H_
 
//main sdl include
#include <SDL.h>
//sdl fonts
#include <SDL_ttf.h>

//#include <vld.h> //leak detector

#include "CEvent.h"
#include "CSurface.h"
#include "CAnimation.h"
#include "CEntity.h"
#include <iostream>
#include <string>
#include "aStar.h"

//for menu
#include "Menu.h"

//for spells
#include "Spells.h"

//for collision
#include "Collision.h"

#include "Define.h"

//for maps
#include "Map.h"
#include "Area.h"
#include "Camera.h"

//for editor
#include "mapEditor.h"

using namespace std;


class CApp : public CEvent /*, protected node*/ , protected character,protected collision {
    private:
		
        bool Running;
		//surfaces
        SDL_Surface* Surf_Display;
 
        SDL_Surface* Surf_Test;

		SDL_Surface* Surf_Char;

		SDL_Surface* Surf_WeapSword1;

		SDL_Surface* Surf_Spells;

		//fps
		double timestep ;
		double accumulator;
		double lastUpdate ;

		//movement of main character
		int facingSide;
	

		bool moveLeft;
		bool moveRight;
		bool moveUp;
		bool moveDown;


		//inventory screen
		bool inventoryOpened;
		
		int tempOldLocation;
		
		
		//mouse location
		int mLocX;
		int mLocY;

		//mouse click
		bool mouseLeftClicked;
		int intervalClick;
		const int intervalClickMax = mouseHoldLInterval;

		//map
		long areaNum;
		long newAreaNum;
		
		//menu
		uint choosenMenu;
		uint loadedMenu;

		//font
		TTF_Font* font;

	public:
		mapClass maps;

	private:
		//animate char
		CAnimation animMainChar;

    public:
        CApp();
		~CApp();
        int OnExecute();
 
    public:
		
		//keypress
		void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
		void OnRButtonDown(int mX, int mY);
		void OnLButtonDown(int mX, int mY);
		void OnLButtonUp(int mX, int mY);

		//pathfind
		string pathFind(const int & xStart, const int & yStart, const int & xFinish, const int & yFinish );

		//sdl
		bool OnInit();
		void OnEvent(SDL_Event* Event);
        void OnExit();
        void OnLoop();
        void OnRender();
        void OnCleanup();
		void updatePhysics();
		//end sdl

		//movement
		string updateCharMovement();
		
		//change map format
		void getMap();
		
		//move map in editor
		void moveMap();
		
		
};
 
#endif