#ifndef _AI_H_
    #define _AI_H_
 
#include "centity.h"
#include "Define.h"
#include "iostream"
#include "Character.h"
#include "Camera.h"

using namespace std;
 
class AI {
private:
	struct path{
		string fullPath;
		int timeNext;
	};

	vector<path> currentPaths;

public:
	//const
	AI::AI();

    static AI AIControl;
	
	void generateMovement();
    void moveEntityToChar(int i);

	//pathing
	bool isPathEmpty(int entityNumber);
	void resizeVector(int i);

	void newPath(string path, int entityNumber);
	void movementFromPath(int entityNumber);
	void moveEntity(int x,int y);

	void attackEntity(int i);

	void entityDirection(float degree,int i);

};
 
#endif