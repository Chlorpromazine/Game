#include "Area.h"
#include "centity.h"

Area Area::AreaControl;
 
Area::Area() {
    AreaSize = 0;
}
 
bool Area::OnLoad(char* File) 
{
    MapList.clear();
 
    FILE* FileHandle = fopen(File, "r");
 
    if(FileHandle == NULL)
	{
        return false;
    }
 
    char TilesetFile[255];
 
    fscanf(FileHandle, "%s\n", TilesetFile);
 
    if((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) 
	{
        fclose(FileHandle);
        return false;
    }
 
    fscanf(FileHandle, "%d\n", &AreaSize);
 
    for(int X = 0 ; X < AreaSize ; X++) 
	{
        for(int Y = 0 ; Y < AreaSize ; Y++) 
		{
            char MapFile[255];
 
            fscanf(FileHandle, "%s ", MapFile);
 
            mapClass tempMap;
            if(tempMap.readFile(MapFile) == false)
			{
                fclose(FileHandle);
                return false;
            }
 
            tempMap.Surf_Tileset = Surf_Tileset;
 
            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }
 
    fclose(FileHandle);
 
    return true;
}


void Area::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) 
{
    int MapWidth  = mapWidth * tileSizeX;
    int MapHeight = mapHeight * tileSizeY;
 
	vector<int> tileType;

    int FirstID = -CameraX / MapWidth;
        FirstID += ((-CameraY / MapHeight) * AreaSize);
 
    for(int i = 0 ; i < 4 ; i++) 
	{
		unsigned int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);
 
        if(ID < 0 || ID >= MapList.size()) 
			continue;
 
        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

		
        MapList[ID].renderMap(Surf_Display, X, Y);
    }
}

 
void Area::OnCleanup() {
    if(Surf_Tileset) 
	{
        SDL_FreeSurface(Surf_Tileset);
    }

    MapList.clear();
}

//collision

vector<mapClass>* Area::getMapCollision()
{
	return &MapList;
}


//entities
void Area::loadEntities()
{
	//loads all the entities for one area at a time
	
	char* file = "images\\monsters\\ogre.bmp";
	CEntity::EntityControl.loadEntityImages(file);
	CEntity::EntityControl.loadCurrentSurface(file);
	
	CEntity::EntityControl.newEntity(700 ,100,"MonsterA");
	CEntity::EntityControl.newEntity(50, 200, "MonsterA");
	CEntity::EntityControl.newEntity(1000, 500, "MonsterC");
	CEntity::EntityControl.newEntity(500, 1000, "MonsterB");
	
	
	
}