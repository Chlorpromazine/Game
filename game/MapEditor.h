#ifndef _MAPEDITOR_H_
#define _MAPEDITOR_H_

#include "main.h"
#include "map.h"
#include "area.h"
#include "Camera.h"

using namespace std;

class mapEditor{
private:
	int tile; //color of tile
	int tileType; //collision or other functions in a tile
	
public:

	mapEditor::mapEditor();

	int mLocX;
	int mLocY;

	static mapEditor mapEditControl;

	void drawMap(SDL_Surface* surface);
	
	void editTile();

	void changeTile(int type);
	void changeTileType(int type);

	void writeMap();

};


#endif