

#include "Map.h"

mapClass::mapClass() {
    Surf_Tileset = NULL;
}

bool mapClass::readFile(char* File)
{
	
	TileList.clear();
 
    FILE* FileHandle = fopen(File, "r");
 
    if(FileHandle == NULL) {
        return false;
    }
 
    for(int Y = 0;Y < mapWidth;Y++) {
        for(int X = 0;X < mapHeight ;X++) {
            Tile tempTile;
 
            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);
 
            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }
 
    fclose(FileHandle);
 
    return true;
}

void mapClass::renderMap(SDL_Surface* mapSurface, int mapX, int mapY)
{
	if(Surf_Tileset == NULL) return;
 
    int TilesetWidth  = Surf_Tileset->w / tileSizeX;
    int TilesetHeight = Surf_Tileset->h / tileSizeY;
 
    int ID = 0;
 
    for(int Y = 0;Y < mapHeight;Y++)
	{
        for(int X = 0;X < mapWidth;X++) 
		{
            if(TileList[ID].TypeID == TILE_TYPE_NONE) 
			{
                ID++;
                continue;
            }
 
            int tX = mapX + (X * tileSizeX);
            int tY = mapY + (Y * tileSizeY);
 
            int TilesetX = (TileList[ID].TileID % TilesetWidth) * tileSizeX;
            int TilesetY = (TileList[ID].TileID / TilesetWidth) * tileSizeY;
 
            CSurface::OnDraw(mapSurface, Surf_Tileset, tX, tY, TilesetX, TilesetY, tileSizeX, tileSizeY);
 
            ID++;
        }
    }

}


int mapClass::getTypeID(int ID)
{
	return TileList[ID].TypeID;
}

int mapClass::getTileID(int ID)
{
	return TileList[ID].TileID;
}

unsigned int mapClass::size()
{
	return TileList.size();
}

void mapClass::modifyTileList(int ID, int tile,int tileType)
{
	TileList[ID].TileID = tile;
	TileList[ID].TypeID = tileType;
}