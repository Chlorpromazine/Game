
#include "AI.h"

AI AI::AIControl;

AI::AI()
{

}

void AI::generateMovement()
{
	//for every entity, check distance from hero, if the attacking entity is close enough, move to it.
	for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
	{
		double entX = (double)CEntity::EntityList[i]->xPos;
		double entY = (double)CEntity::EntityList[i]->yPos;
		double charX = (double)character::charControl.retPosX();
		double charY = (double)character::charControl.retPosY();

		//calculate the distance from the hero to the entity
		int distFromChar = (int)sqrt((entX-charX)*(entX-charX) + (entY-charY)*(entY-charY));
		
		//if (distFromChar <= 250 && (entX - charX > heroWidth || entY - charY > heroHeight || charX - entX > CEntity::EntityList[i]->widthCol || charY - entY > CEntity::EntityList[i]->heightCol)) //if the entity is close enough to the hero
		if (distFromChar > 50 && distFromChar <= 250)
		{
			//for checking which side the entity has to face, we calculate the angle using the 2 points
			float angle = atan2(entY - charY, entX - charX); //returns in radiants
			angle = angle * 180 / PI; //convert to degrees
			CEntity::EntityList[i]->setStartFrame(i, 0);
			CEntity::EntityList[i]->setMaxFrame(i, 4);
			CEntity::EntityList[i]->OnLoop();
			entityDirection(angle,i);
			moveEntityToChar(i);
			
		}
		//if entity is close to target
		else if (distFromChar < 50)
		{
			//CEntity::EntityList[i]->setFrame(i, 0);
			attackEntity(i);
		}
	}
}


void AI::entityDirection(float degree,int i)
{
	if (degree >= -22.5 && degree < 22.5)
		CEntity::EntityList[i]->faceDirection = 0;

	else if (degree >= 22.5 && degree < 67.5)
		CEntity::EntityList[i]->faceDirection = 1;

	else if (degree >= 67.5 && degree < 112.5)
		CEntity::EntityList[i]->faceDirection = 2;

	else if (degree >= 112.5 && degree < 157.5)
		CEntity::EntityList[i]->faceDirection = 3;

	else if (degree >= 157.5 || degree < -157.5)
		CEntity::EntityList[i]->faceDirection = 4;

	else if (degree >= -157.5 && degree < -112.5)
		CEntity::EntityList[i]->faceDirection = 5;

	else if (degree > -112.5 && degree < -67.5)
		CEntity::EntityList[i]->faceDirection = 6;

	else if (degree > -67.5 && degree < -22.5)
		CEntity::EntityList[i]->faceDirection = 7;
}

void AI::moveEntityToChar(int i)
{
	//check collision between player and the entity
	character *entity = new character();
	character *player = new character();
	
	//create rectangles for the collision area
	rectangle entityCollision = entity->coordRegion((int)CEntity::EntityList[i]->heightCol, (int)CEntity::EntityList[i]->widthCol, (int)CEntity::EntityList[i]->xPos, (int)CEntity::EntityList[i]->yPos);
	rectangle characterCollision = player->coordRegion(heroHeight, heroWidth, character::charControl.retPosX(), character::charControl.retPosY());

	vector<bool> collOtherEnt;
	
	//if the entity isn't in collision with the player
	if(!collision::cC.isCollided(entityCollision,characterCollision) )
	{
		//check collision between entity and other entity, return sides collided if any.
		collOtherEnt = collision::cC.collisionEntityCheck(i);
		
		//if it isn't collided on the right side
		if(character::charControl.retPosX() > CEntity::EntityList[i]->xPos && !collOtherEnt[2]  )
		{
			if (!collision::cC.collisionTile(3, (int)CEntity::EntityList[i]->xPos, (int)CEntity::EntityList[i]->yPos, CEntity::EntityList[i]->widthCol, CEntity::EntityList[i]->heightCol))
			{
				CEntity::EntityList[i]->moveX(mSpeedA);//move right
				
			}
		}

		//if it isn't collided on the left side
		if(character::charControl.retPosX() < CEntity::EntityList[i]->xPos && !collOtherEnt[3]  )
		{
			if (!collision::cC.collisionTile(2, (int)CEntity::EntityList[i]->xPos, (int)CEntity::EntityList[i]->yPos, CEntity::EntityList[i]->widthCol, CEntity::EntityList[i]->heightCol))
			{
				CEntity::EntityList[i]->moveX(-mSpeedA);//move left
				
			}
		}

		//if it isn't collided on the bottom side
		if(character::charControl.retPosY() > CEntity::EntityList[i]->yPos && !collOtherEnt[0] )
		{
			if (!collision::cC.collisionTile(1, (int)CEntity::EntityList[i]->xPos, (int)CEntity::EntityList[i]->yPos, CEntity::EntityList[i]->widthCol, CEntity::EntityList[i]->heightCol))
			{
				CEntity::EntityList[i]->moveY(mSpeedA);//move down
				
			}
		}

		//if it isn't collided on the top side
		if(character::charControl.retPosY() < CEntity::EntityList[i]->yPos && !collOtherEnt[1] )
		{
			if (!collision::cC.collisionTile(0, (int)CEntity::EntityList[i]->xPos, (int)CEntity::EntityList[i]->yPos, CEntity::EntityList[i]->widthCol, CEntity::EntityList[i]->heightCol))
			{
				CEntity::EntityList[i]->moveY(-mSpeedA);//move up
				
			}
		}
	}

	delete entity;
	delete player;
		
}

void AI::newPath(string path, int entityNumber)
{
	currentPaths[entityNumber].fullPath = path;
	//todo: calculate next time based on position of entity on current tile.
	currentPaths[entityNumber].timeNext = 0;
}

void AI::resizeVector(int i)
{
	currentPaths.resize(currentPaths.size() + i);
}

void AI::movementFromPath(int entityNumber)
{
	
	try //if entity is not created
	{
		currentPaths.at(entityNumber); 
	}
	catch (const out_of_range& oor) 
	{
		cout << "Error, entity number not found for path" << endl;
		system("pause");
		exit(0);
	}

	if (currentPaths[entityNumber].fullPath.size() < 1) //don't do anything if there's no current movement for the entity
		return;

	string path = currentPaths[entityNumber].fullPath;	

	//take the first direction from the path and move there
	switch (path[0])
	{
	case '0':
		moveEntity(-1, 0);
		break;
	case '1':
		moveEntity(-1, -1);
		break;
	case '2':
		moveEntity(0, -1);
		break;
	case '3':
		moveEntity(1, -1);
		break;
	case '4':
		moveEntity(1, 0);
		break;
	case '5':
		moveEntity(1, 1);
		break;
	case '6':
		moveEntity(0, 1);
		break;
	case '7':
		moveEntity(-1, 1);
		break;
	default:
		cout << "error: invalid movement" << endl;
		break;
	}
	float distMax = 0; //distance from next tile
	int dist; //distance from next pixel
	if ((int)path[0] % 2 == 0) //if pair, distance is 15-1 pixel (-1 so start-end doesn't use same pixel), straight line
	{
		distMax = 14;
		dist = 1;
	}
	else //odd, distance is 28 (14*2), diagonally
	{
		distMax = 28;
		dist = 2;
	}

	if (currentPaths[entityNumber].timeNext > distMax)//arrived at next tile
	{
		currentPaths[entityNumber].fullPath.erase(0, 1);
		currentPaths[entityNumber].timeNext = 0;
	}
	else
		currentPaths[entityNumber].timeNext += dist;

}

//todo: change function to work with every entity, not just the main character
void AI::moveEntity(int x,int y)
{
	Camera::CameraControl.OnMove(x, y);

	character::charControl.changePosX(-x);
	character::charControl.changePosY(-y);

	for (unsigned int i = 0; i < CEntity::EntityList.size(); i++)
	{
		CEntity::EntityList[i]->xDraw += x;
		CEntity::EntityList[i]->yDraw += y;
	}

}

void AI::attackEntity(int i)
{
	CEntity::EntityList[i]->setMaxFrame(i, 2);
	CEntity::EntityList[i]->setStartFrame(i, 3);
	CEntity::EntityList[i]->OnLoop();
}