#ifndef _COLLISION_H_
    #define _COLLISION_H_

#include <iostream>
#include "Character.h"
#include <vector>
#include <algorithm> 
#include "centity.h"
#include "Area.h"

using namespace std;

class collision{

public:

	static collision cC;
	collision();

	vector<int> mapInfoCollision;

public:
	unsigned int entityCount;
	bool isCollided(rectangle ,rectangle );
	int collisionSide(rectangle ,rectangle );
	
	//map
	bool collisionTile(int,int,int,int,int);
	void collisionMapInfo();

	//entities
	vector<bool> collisionEntityCheck(int);
	
};



#endif