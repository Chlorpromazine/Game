#ifndef _MAP_H_
    #define _MAP_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Define.h"
#include "Tile.h"
#include "sdl.h"
#include "CSurface.h"

using namespace std;



class mapClass{
private:
	std::vector<Tile> TileList;
	
public:
	mapClass();

	SDL_Surface* Surf_Tileset;

	struct infoOnMap{
			uint numOfTile;
			uint tileType;
			uint tileOption;
		};

	bool readFile(char*);
	void renderMap(SDL_Surface*,int,int);
	int getTypeID(int ID);
	int getTileID(int ID);
	unsigned int size();

	void modifyTileList(int ID, int tile, int tileType);
};

#endif