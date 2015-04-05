#ifndef _SPELLS_H_
    #define _SPELLS_H_
 
#include <vector>
#include <SDL.h>
#include <iostream>
#include "Define.h"
#include "Character.h"
#include "Collision.h"

using namespace std;

class spell: protected character{
private:
	
	struct spellInfo
	{
		int locX; 
		int locY;
		int height;
		int width;
		int imgLocX;
		double cX;
		double cY;
		int spellType; 
		unsigned int framesLeft;
		int radius; //cast range in pixels (circular distance)
		double accelX;
		double accelY;
		double distance;
		double distPar;
	};

	

	struct currentSpellInfo
	{
			unsigned int currentSpell;
			unsigned int frames;
			unsigned int height;
			unsigned int width;
			unsigned int radius;
			unsigned int imgLocX;
	};
	
	
public:
	//funcs
	spell();
	static spell spells;
	
	std::vector<vector<int>>  drawSpells();
	void castSpellLocation(int mX,int mY,currentSpellInfo spellType, int offset);
	bool castRange(int range, int x, int y,int offset);
	

public:
	//vars
	bool mouseRightClicked;
	vector<currentSpellInfo> allSpells;
	unsigned int spellChosen;
	currentSpellInfo curSpell;
	std::vector<spellInfo> spellList;

	void spellCollision();
	
};

#endif