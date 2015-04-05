#ifndef _CAREA_H_
    #define _CAREA_H_
 
#include "Map.h"
 
class Area {
    public:
        static Area            AreaControl;

        std::vector<mapClass>       MapList;
		
 
    private:
        int                     AreaSize;
 
        SDL_Surface*        Surf_Tileset;

 
    public:
        Area();
 
        bool OnLoad(char* File);
 
        void OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);
 
		void loadEntities();

        void OnCleanup();
	
		vector<mapClass>* getMapCollision();

};
 
#endif