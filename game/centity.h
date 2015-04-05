#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>
 
#include "CAnimation.h"
#include "CSurface.h"
#include "AI.h"
#include <string>
#include <unordered_map> //for surface list of entities
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

class CEntity {

	
    public:
		//check if you're using the same entity, if so, don't reload the images or information.
		 static struct commonEntities{
			SDL_Surface* Surface;
			int startX;
			int height;
			int width;
			int heightCollision;
			int widthCollision;
			int frames; //animation
			int entityNumber;
			string path;
			string entityName;


			bool operator==(const commonEntities &other) const
			  { 
				  return (entityNumber == other.entityNumber);
			  }

		};


        static std::vector<CEntity*> EntityList;
		static std::unordered_map<std::string, commonEntities> surfEntityList; //So we don't need to reload the images every time  for the same entity.

    protected:
        CAnimation      Anim_Control;
 
        SDL_Surface*    Surf_Entity;
 
    public:
		
		//position to draw on the screen
        float           xDraw;//if off screen, don't draw
        float           yDraw;
 
		//actual position on the map
		float			xPos;
		float			yPos;

		int startX;

        int             Width;
        int             Height;
 
        int             AnimState;

		//combat variables
		int currentHP;
		int maxHP;

		//collision size
		int heightCol;
		int widthCol;

		//facing direction
		int faceDirection;

 
		static CEntity EntityControl;
    public:
        CEntity();
 
        virtual ~CEntity();
 
    public:
        virtual bool OnLoad(char* ,int ,int ,int ,int,int locX);
 
        virtual void OnLoop();
 
        virtual void OnRender(SDL_Surface* Surf_Display);
 
        virtual void OnCleanup();

		//movement
		virtual void moveX(float);
		virtual void moveY(float);

		//create new entity
		virtual void newEntity(int x,int y,std::string entityName);
		virtual void loadCurrentSurface(char* file);
		virtual void loadEntityImages(char* file);
		
		//combat
		virtual void checkIfDead(int entityNumber);
		virtual void substractHP(float value,int entityNumber);

		void setFrame(int i,int frame);
		void setMaxFrame(int i, int max);
		void setStartFrame(int i, int frame);
};

#endif