#include "Collision.h"

collision collision:: cC;

collision::collision(){
	entityCount = 0;
}

bool collision::isCollided(rectangle obj1, rectangle obj2)
{
	if(obj1.x < obj2.x+obj2.w && obj1.x+obj1.w > obj2.x && obj1.y < obj2.y+obj2.h && obj1.y+obj1.h > obj2.y)
		return true; //collision
		
	return false; //no collision
}

int collision::collisionSide(rectangle obj1, rectangle obj2)
{
	float ojb1Bottom = (float)(obj1.y + obj1.h);
	float ojb2Bottom = (float)(obj2.y + obj2.h);
	float ojb1Right = (float)(obj1.x + obj1.w);
	float ojb2Right = (float)(obj2.x + obj2.w);

	float botCollision = ojb2Bottom - obj1.y;
	float topCollision = ojb1Bottom - obj2.y;
	float leftCollision = ojb1Right - obj2.x;
	float rightCollision = ojb2Right - obj1.x;

	if (topCollision < botCollision && topCollision < leftCollision && topCollision < rightCollision )
	{                           
		return 0; //top
	}
	if (botCollision < topCollision && botCollision < leftCollision && botCollision < rightCollision)                        
	{
		return 1; //bot
	}
	if (leftCollision < rightCollision && leftCollision < topCollision && leftCollision < botCollision)
	{
		return 2; //left
	}
	if (rightCollision < leftCollision && rightCollision < topCollision && rightCollision < botCollision )
	{
		return 3; //right
	}
	return -1; //same size and position
}


void collision::collisionMapInfo()
{	
	/*change vector from |----|----|----| to |------------------|
						 |----|----|----|    |------------------|
						 |----|----|----|    |------------------| 

	So the collision can read it from line to line from all maps instead of going through all a map at once.
	*/

	for(int y = 0 ; y < mapPerAreaY ; ++y) //number of maps on y
	{
		for(int j = 0 ; j < screenSizeY/16 ; ++j)
		{
			for(int x = 0 ; x < mapPerAreaX ; ++x) //number of maps on x
			{
				for(int p = 0 ; p < screenSizeX/16 ; ++p)
				{
					cC.mapInfoCollision.push_back(Area::AreaControl.MapList[x+y*mapPerAreaY].getTypeID((j*screenSizeX/16)+p));
					//cC.mapInfoCollision.push_back(Area::AreaControl.MapList[x + y*mapPerAreaY].getTileID((j*screenSizeX / 16) + p));

				}
			}
		}	
	}
	
}



bool collision::collisionTile(int orientation,int posX, int posY,int entW, int entH)
{
	//get length and height of the map
	int areaLength = screenSizeX*mapPerAreaX;
	int areaHeight = screenSizeY*mapPerAreaY;

	int tileX = posX/tileSizeX; //each tile is 16 pixels
	int tileY = posY/tileSizeY;

	int numTileX = entW/tileSizeX;
	int numTileY = entH/tileSizeY;
	
	//get the tile that the entity is on
	int tileNumber = tileX + tileY*(areaLength/16); //2d
	
	//check if the entity is out of the map, this shouldn't happen, if it does, don't apply collision so he can re-enter
	//going out the map does not crash the game and won't have much benefits.
	bool outOfMap = posY < 16 || posY > screenSizeY*mapPerAreaY-(entH+1) ||  posX < 16 ||  posX > screenSizeX*mapPerAreaX-(entW) ;
	
	rectangle tileCollision;

	bool condition = 0;

	//up, check if any of the 2 tiles above the entity are non-walkable
	if(orientation == 0 && !outOfMap )
	{
		int i = 0;
		for(; i < numTileX ; i++)
		{
			if(cC.mapInfoCollision[tileNumber-(areaLength/16)+i] == 1) 
			{
				condition = 1; 
				break;
			}
		}
		
		//if the entity standing right at the start of a tile, we must add a third condition to check another tile
		int lastCondUP = 0;

		if( posX%16 != 0)
			lastCondUP =  cC.mapInfoCollision[tileNumber-(areaLength/16)+i];
			
		if(condition || lastCondUP == 1)
		{
			//check collision between the hero and these tiles
			rectangle hero = character::charControl.coordRegion(entH, entW, posX, posY - charMoveSpeed); //collision of hero

			//collision only of first tile
			tileCollision = character::charControl.coordRegion(16,16,posX,((posY/16)-1)*16);

			bool col = isCollided(hero, tileCollision); //1 collided, 0 not collided
			
			return col; 
			
		}
	}	
	

	//down, check if any of the 2 tiles below the entity are non-walkable
	if(orientation == 1 && !outOfMap ) 
	{
		int i = 0;
		for(; i < numTileX ; i++)
		{	
			if(cC.mapInfoCollision[tileNumber+(numTileY*(areaLength/16))+i] == 1) 
			{
				condition = 1; 
				break;
			}
		}
		//if the entity standing right at the start of a tile, we must add a third condition to check another tile
		int lastCondDOWN = 0;
		if( posX%16 != 0)
			lastCondDOWN =  cC.mapInfoCollision[tileNumber+(numTileY*(areaLength/16))+i];
	
		
		if(condition || lastCondDOWN == 1)
		{//check collision between the hero and these tiles
			
			rectangle hero = character::charControl.coordRegion(entH, entW, posX, posY + charMoveSpeed); //collision of hero
			
			tileCollision = character::charControl.coordRegion(16, 16, posX, ((posY / 16) + 1) * 16);

			bool col = isCollided(hero, tileCollision); //1 collided, 0 not collided
			
			return col; 
		}
	}
	
	//left, check if any of the 4 tiles on the left of the entity are non-walkable
	if(orientation == 2 && !outOfMap ) 
	{
		int i = 0;
		for( ; i < numTileY ; i++)
		{
			if(cC.mapInfoCollision[tileNumber-1+i*(areaLength/16)] == 1) 
			{
				condition = 1; 
				break;
			}
		}
		//if the entity standing right at the start of a tile, we must add a fourth condition to check another tile
		int lastCondLEFT = 0;
		if( posY%16 != 0)
			lastCondLEFT =  cC.mapInfoCollision[tileNumber-1+i*(areaLength/16)];
		

		if(condition || lastCondLEFT)
		{//check collision between the hero and these tiles

			rectangle hero = character::charControl.coordRegion(entH, entW, posX - charMoveSpeed, posY); //collision of hero
			
			tileCollision = character::charControl.coordRegion(16, 16, ((posX / 16) - 1) * 16, posY);

			bool col = isCollided(hero, tileCollision); //1 collided, 0 not collided
			
			return col; 
		}
	}

	//right, check if any of the 4 tiles on the right of the entity are non-walkable
	if(orientation == 3 && !outOfMap ) 
	{

		int i = 0;
		for( ; i < numTileY; i++)
		{
			if(cC.mapInfoCollision[tileNumber+numTileX+i*(areaLength/16)] == 1) 
			{
				condition = 1; 
				break;
			}
		}

		//if the entity standing right at the start of a tile, we must add a fourth condition to check another tile
		int lastCondRIGHT = 0;
		if( posY%16 != 0)
			lastCondRIGHT = cC.mapInfoCollision[tileNumber+numTileX+i*(areaLength/16)];

		//get the 3 tiles on top
		
		if(condition || lastCondRIGHT)
		{	
			rectangle hero = character::charControl.coordRegion(entH, entW, posX + charMoveSpeed, posY); //collision of hero
			
			tileCollision = character::charControl.coordRegion(16, 16, ((posX / 16) + 1) * 16, posY);

			bool col = isCollided(hero, tileCollision); //1 collided, 0 not collided
			
			return col; 
		}
	}
	
	return 0;
}


//to find the id of the entity in the vector of X and Y coords.
vector<bool> collision::collisionEntityCheck(int i)
{
	//TODO: move entities away from eachother if they're in collision
	//Only search entities close to eachother

	//check collided side
	vector<bool> colSide ;
	for(int k = 0 ; k < 4 ; k++) colSide.push_back(0);
	int side ;

	//function O(n^2)
	rectangle compareEnt1 = rectangle(CEntity::EntityList[i]->heightCol + 2, CEntity::EntityList[i]->widthCol + 2, (int)CEntity::EntityList[i]->xPos - 1, (int)CEntity::EntityList[i]->yPos - 1);
		
	//for this entity, check if it is in collision with every other entity
	for(unsigned int j = 0 ; j < CEntity::EntityList.size() ; j++)
	{	
		if(j == i) continue;

		rectangle compareEnt2 = rectangle(CEntity::EntityList[j]->heightCol, CEntity::EntityList[j]->widthCol, (int)CEntity::EntityList[j]->xPos, (int)CEntity::EntityList[j]->yPos);
			
		if(isCollided(compareEnt1,compareEnt2))
		{
			//if it's collided, check side(s)
			side = collisionSide(compareEnt1,compareEnt2);
			if(side == 0)	   colSide[0] = 1;
			else if(side == 1) colSide[1] = 1;
			else if(side == 2) colSide[2] = 1;
			else if(side == 3) colSide[3] = 1;
		}
	}
	
   return colSide;
}