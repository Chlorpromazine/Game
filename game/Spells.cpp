#include "Spells.h"


spell spell:: spells;

spell::spell()
{
	mouseRightClicked = 0;

	spellChosen = 0;

	//todo: put this data in file and read from it when spell is loaded
	//to add a spell
	curSpell.currentSpell = 0;
	curSpell.frames = 0;
	curSpell.radius = 300;
	curSpell.width = 16;
	curSpell.height = 16;
	curSpell.imgLocX = 0;
	
	
	allSpells.push_back(curSpell);

	curSpell.currentSpell = 1;
	curSpell.frames = 0;
	curSpell.radius = 400;
	curSpell.width = 16;
	curSpell.height = 16;
	curSpell.imgLocX = 16;
	
	allSpells.push_back(curSpell);

}

std::vector<vector<int>> spell::drawSpells()
{
	vector<vector<int>> allSpells;
	vector<int> values;
	
	for(unsigned int i = 0 ; i < spellList.size() ; i++)
		{
			if(spellList[i].spellType == 0)
			{
				spellList[i].cX += spellList[i].accelX;
				spellList[i].cY += spellList[i].accelY;
				//location of spell in game
				values.push_back((int)spellList[i].cX);
				values.push_back((int)spellList[i].cY);
				//location of image
				values.push_back(spellList[i].imgLocX);
				values.push_back(spellList[i].framesLeft*spellList[i].height);
				
				//size of spell
				values.push_back(spellList[i].height);
				values.push_back(spellList[i].width);

				//calculate travel distance
				spellList[i].distPar += spellList[i].accelX*spellList[i].accelX + spellList[i].accelY*spellList[i].accelY;

				//if it went to it's location, delete the spell
				if( spellList[i].distPar >= abs(spellList[i].distance))
				{
					spellList.erase(spellList.begin()+i);
				}
			}
			else if(spellList[i].spellType == 1)
			{
				spellList[i].cX += spellList[i].accelX;
				spellList[i].cY += spellList[i].accelY;
				//location of spell in game
				values.push_back((int)spellList[i].cX);
				values.push_back((int)spellList[i].cY);
				//location of image
				values.push_back(spellList[i].imgLocX);
				values.push_back(spellList[i].framesLeft*spellList[i].height);
				
				//size of spell
				values.push_back(spellList[i].height);
				values.push_back(spellList[i].width);

				//calculate travel distance
				spellList[i].distPar += spellList[i].accelX*spellList[i].accelX + spellList[i].accelY*spellList[i].accelY;

				//if it went to it's location, delete the spell
				if( spellList[i].distPar >= abs(spellList[i].distance))
				{
					spellList.erase(spellList.begin()+i);
				}
			}
			else {cout << "Error: spelltype not found" << endl; system("pause"); exit(0);}

			allSpells.push_back(values);
			values.clear();
		}
	
	return allSpells;
}

bool spell::castRange(int range, int x, int y,int offset)
{
	//only in a circle around the hero
	//offset is to find the middle of the hero
	int dx = x-locationOfHeroX;
	int dy = y-locationOfHeroY;
	
	if ( (dx*dx + dy*dy) <= (range*range) )
		return 1;

	return 0;
}


void spell::castSpellLocation(int mX,int mY,currentSpellInfo spellType, int offset)
{
	//if it's in range, calculate and cast the spell
	if(castRange(spellType.radius, mX, mY,offset)) 
	{
		double accelX;
		double accelY;

		//mouse position - the center of the location of the hero
		double xd = mX - (int)((locationOfHeroX)+(spellType.width/2)); 
		double yd = mY - (int)((locationOfHeroY)+(spellType.height/2));   // Get the side lengths 
        
		double d = sqrt(xd * xd + yd * yd);     // Calculate the hypotenuse 
	
		//todo: try/catch because of double
		if(d == 0) //if dividing by 0
		{
			accelX = 0;
			accelY = 0;
		}
		else
		{
			accelX = xd/ d;
			accelY = yd/ d; 
		}

	

		spellInfo curSpellInit = 
		{
			mX+charControl.retPosX()-(int)((locationOfHeroX)+(spellType.width/2)),
			mY+charControl.retPosY()-(int)((locationOfHeroY)+(spellType.height/2)),
			spellType.height,
			spellType.width, 
			spellType.imgLocX,
			charControl.retPosX(), 
			charControl.retPosY(), 
			spellType.currentSpell,
			spellType.frames, 
			spellType.radius, 
			accelX,  
			accelY, 
			d,
			0
		};

		spellList.push_back(curSpellInit);
		
	}
}

void spell::spellCollision()
{
	//for all spells
	for(int i = 0 ; i < spellList.size() ; i++)
	{	//make rectangle for the spell
		rectangle rectSpell = rectangle(spellList[i].height,spellList[i].width,spellList[i].cX,spellList[i].cY);
	
		//for all entities
		for(int j = 0 ; j < CEntity::EntityList.size(); j++)
		{
			//make rectangle for the entity
			rectangle rectEntity = rectangle(CEntity::EntityList[j]->heightCol,CEntity::EntityList[j]->widthCol,CEntity::EntityList[j]->xPos,CEntity::EntityList[j]->yPos);

			//if it's collided, delete the spell and do the effect of the spell or do damage.
			if(collision::cC.isCollided(rectSpell,rectEntity))
			{
				//todo: put check in substract
				CEntity::EntityControl.substractHP(10,j);
				CEntity::EntityControl.checkIfDead(j);
				spellList.erase(spellList.begin()+i);
				break;
			}
			
		}
		//check collision with other entities
		//collision::cC.isCollided(
	}
}