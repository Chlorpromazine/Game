#include "Main.h"
 
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}
 
void CApp::OnExit() {
    Running = false;
}

/*
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	
	switch(sym) {

		//movement
    case SDLK_w: 
		moveUp = true;
		moveDown = false;
		break;
	case SDLK_d: 
		moveRight = true;
		moveLeft = false;
		break;
	case SDLK_s: 
		moveDown = true;
		moveUp = false;
		break;
	case SDLK_a: 
		moveLeft = true;
		moveRight = false;
		break;
		//spells
	case SDLK_1: 
		spellChosen = 0;
		break;
	case SDLK_2: 
		spellChosen = 1;
		break;
	
	}
}
*/
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	
	if (choosenMenu == 1)
	{
		switch (sym) 
		{
		//movement
		case SDLK_w:
			moveUp = false;
			break;

		case SDLK_d:
			moveRight = false;
			break;

		case SDLK_s:
			moveDown = false;
			break;

		case SDLK_a:
			moveLeft = false;
			break;
		}
	}
	else if (choosenMenu == 3)
	{
		switch (sym)
		{
		case SDLK_UP:
			moveUp = false;
			break;

		case SDLK_DOWN:
			moveDown = false;
			break;

		case SDLK_LEFT:
			moveLeft = false;
			break;

		case SDLK_RIGHT:
			moveRight = false;
			break;

		}

	}

}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
   
	if (choosenMenu == 1)
	{
		switch (sym) {

			//movement
		case SDLK_w:
			moveUp = true;
			moveDown = false;
			break;
		case SDLK_s:
			moveDown = true;
			moveUp = false;
			break;
		case SDLK_a:
			moveLeft = true;
			moveRight = false;
			break;
		case SDLK_d:
			moveRight = true;
			moveLeft = false;
			break;

			//spells
		case SDLK_1:
			spell::spells.spellChosen = 0;
			break;
		case SDLK_2:
			spell::spells.spellChosen = 1;
			break;

		default: {
			}
		}
    }
	else if (choosenMenu == 3) //map editor
	{
		//move map around
		switch (sym)
		{
		case SDLK_ESCAPE:
			choosenMenu = 0;
			loadedMenu = 0;
		break;
		case SDLK_UP:
			moveUp = true;
			moveDown = false;
			break;
		case SDLK_DOWN:
			moveDown = true;
			moveUp = false;
			break;
		case SDLK_LEFT:
			moveLeft = true;
			moveRight = false;
			break;
		case SDLK_RIGHT:
			moveRight = true;
			moveLeft = false;
			break;

		//tile type
		case SDLK_1:
			mapEditor::mapEditControl.changeTile(0);
			break;
		case SDLK_2:
			mapEditor::mapEditControl.changeTile(1);
			break;
		case SDLK_3:
			mapEditor::mapEditControl.changeTile(2);
			break;
		case SDLK_4:
			mapEditor::mapEditControl.changeTile(3);
			break;
		case SDLK_5:
			mapEditor::mapEditControl.changeTile(4);
			break;
		case SDLK_6:
			mapEditor::mapEditControl.changeTile(5);
			break;
		case SDLK_w:
			mapEditor::mapEditControl.changeTileType(0);
			break;
		case SDLK_s:
			mapEditor::mapEditControl.changeTileType(1);
			break;
			

		}
	}
}
void CApp::OnRButtonDown(int mX, int mY){
	
	mLocX = mX;
	mLocY = mY;
	
	if (choosenMenu == 1)
		spell::spells.mouseRightClicked = 1;
}

void CApp::OnLButtonDown(int mX, int mY){

	mLocX = mX;
	mLocY = mY;

	mouseLeftClicked = 1;

	if (choosenMenu == 1)
	{
		intervalClick = mouseHoldLInterval;
	}
	else if (choosenMenu == 3)
	{
		mapEditor::mapEditControl.mLocX = mX;
		mapEditor::mapEditControl.mLocY = mY;
		mapEditor::mapEditControl.editTile();
	}
}

void CApp::OnLButtonUp(int mX, int mY){

	mouseLeftClicked = 0;
}