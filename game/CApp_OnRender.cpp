
#include "Main.h"

void error(string s)
{
	cout << "Error: " << s << endl;
	system("pause");
	exit(0);
}

void CApp::updatePhysics()
{
	int frameChar = 0;

	if(moveLeft)
	{ 
		facingSide = 1;
			
		if(!cC.collisionTile(2,charControl.retPosX(),charControl.retPosY(),heroWidth,heroHeight))
		{
			Camera::CameraControl.OnMove(charMoveSpeed, 0);
			
			charControl.changePosX(-charMoveSpeed);
			for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
			{
				CEntity::EntityList[i]->xDraw += charMoveSpeed;
			}
			
		}

		animMainChar.OnAnimate();
		frameChar =  animMainChar.GetCurrentFrame();
	}

	if(moveRight)
	{
		facingSide = 2;

		if(!cC.collisionTile(3,charControl.retPosX(),charControl.retPosY(),heroWidth,heroHeight))
		{
			Camera::CameraControl.OnMove(-charMoveSpeed, 0);
			charControl.changePosX(charMoveSpeed);
			for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
			{
				CEntity::EntityList[i]->xDraw -= charMoveSpeed;
			}
			
		}

		animMainChar.OnAnimate();
		frameChar = animMainChar.GetCurrentFrame();
	}

	if(moveUp)
	{
		facingSide = 3;

		if(!cC.collisionTile(0,charControl.retPosX(),charControl.retPosY(),heroWidth,heroHeight))
		{
			Camera::CameraControl.OnMove(0, charMoveSpeed);
			charControl.changePosY(-charMoveSpeed);
			for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
			{
				CEntity::EntityList[i]->yDraw += charMoveSpeed;
		
			}
		}

		animMainChar.OnAnimate();
		frameChar = animMainChar.GetCurrentFrame();
	}

	if(moveDown)
	{
		facingSide = 0;

		if(!cC.collisionTile(1,charControl.retPosX(),charControl.retPosY(),heroWidth,heroHeight))
		{
			Camera::CameraControl.OnMove(0, -charMoveSpeed);
			charControl.changePosY(charMoveSpeed);
			for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
			{
				CEntity::EntityList[i]->yDraw -= charMoveSpeed;
			}
		}

		animMainChar.OnAnimate();
		frameChar = animMainChar.GetCurrentFrame();
	
	}
		
	//draw char
	CSurface::OnDraw(Surf_Display, Surf_Char, locationOfHeroX , locationOfHeroY, 32*frameChar,facingSide*48,32,48); //change 32/48 to changable values

	//check collision for spells
	spell::spells.spellCollision();

	//draw spells
	vector<vector<int>> spellDisplay = spell::spells.drawSpells();
		
	for(unsigned int i = 0 ; i < spellDisplay.size() ; i++){
		
		//				 surfaces					positionX of image based off map and not screen		 positionY 
		CSurface::OnDraw(Surf_Display, Surf_Spells,spellDisplay[i][0]-charControl.retPosX()+locationOfHeroX,spellDisplay[i][1]-charControl.retPosY()+locationOfHeroY, 
						 spellDisplay[i][2], spellDisplay[i][3], spellDisplay[i][4], spellDisplay[i][5]);
		//				spell type			  frame				 size of image x     size of image y
	}
		
	spellDisplay.clear();
	vector<vector<int>>().swap(spellDisplay);

	//draw all entities
	for(unsigned int i = 0 ; i < CEntity::EntityList.size() ; i++)
		CEntity::EntityList[i]->OnRender(Surf_Display);
		
	
	
	//ai movement
	AI::AIControl.generateMovement();

	
	SDL_Flip(Surf_Display);

	//draw a black screen
	for(int x = 0 ; x < screenSizeX/16 ; x++)
	{
		for(int y = 0 ; y < screenSizeY/16 ; y++)
		{
			CSurface::OnDraw(Surf_Display, Surf_Spells,x*16,y*16,16,0,16,16);
		}
	}

	//draw map
	Area::AreaControl.OnRender(Surf_Display, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
	
}


void CApp::OnRender()
{
	//Todo: put main menu here that includes map editor and game.
	double thisUpdate = SDL_GetTicks() ;
	double secFromLast = thisUpdate - lastUpdate;
	
	accumulator += secFromLast;

	while( accumulator >= 0) {
	
		switch (choosenMenu)
		{
		case 0://main menu
			if (!loadedMenu)
			{
				menu::Menu.clearScreen(Surf_Display);
				menu::Menu.loadTextMainMenu(Surf_Display, font);
				loadedMenu = 1;
			}
			
			menu::Menu.loadMenu(Surf_Display);

			if (mouseLeftClicked)
			{
				//clicked on play game
				if (mLocX < screenSizeX / 2 + 55 && mLocX > screenSizeX / 2 - 55 &&
					mLocY < screenSizeY / 2 + 29 + 125 && mLocY > screenSizeY / 2  + 125)
					choosenMenu = 1;
				//clicked on options
				else if (mLocX < screenSizeX / 2 + 55 && mLocX > screenSizeX / 2 - 55 &&
					mLocY < screenSizeY / 2 + 29 + 175 && mLocY > screenSizeY / 2 + 175)
				{
					choosenMenu = 2;
					loadedMenu = 0;
				}

				//clicked on map editor
				else if (mLocX < screenSizeX / 2 + 55 && mLocX > screenSizeX / 2 - 55 &&
					mLocY < screenSizeY / 2 + 29 + 225 && mLocY > screenSizeY / 2 + 225)
				{
					choosenMenu = 3;
					loadedMenu = 0;
				}

				mouseLeftClicked = 0;
			}
			
			break;

		case 1://game
			if (areaNum != newAreaNum)
			{
				Camera::CameraControl.SetPos(0, 0);
				//load map of this area
				collisionMapInfo();
				//getMap();

				areaNum = newAreaNum;

				//load entities of current area
				Area::AreaControl.loadEntities();
				
				
			}

			//cast current spell on rightclick
			if (spell::spells.mouseRightClicked)
			{
				spell::spells.castSpellLocation(mLocX, mLocY, spell::spells.allSpells[spell::spells.spellChosen], 0); //offset bugged
				spell::spells.mouseRightClicked = 0;
			}

			//movement
			if (mouseLeftClicked)
			{
				if (intervalClick > intervalClickMax)
				{

					SDL_GetMouseState(&mLocX, &mLocY);

					string route = pathFind(charControl.retPosX() / 16, charControl.retPosY() / 16, charControl.retPosX() / 16 + mLocX / 16 - mapWidth / 2 + heroWidth / 16 - 1, charControl.retPosY() / 16 + mLocY / 16 - mapHeight / 2 + heroHeight / 16 - 1);
					if (route.size() > 0)
						cout << route << endl;

					//generate movement
					AI::AIControl.newPath(route, 0);
					intervalClick = 0;
				}
				intervalClick++;

				//mouseLeftClicked = 0;
			}

			AI::AIControl.movementFromPath(0);

			updatePhysics();

			break; //end case 1

		case 2://options
			if (!loadedMenu)
			{
				menu::Menu.clearScreen(Surf_Display);
				menu::Menu.loadTextOptionMenu(Surf_Display, font);
				loadedMenu = 1;
			}

			menu::Menu.loadMenu(Surf_Display);
			
			if (mouseLeftClicked)
			{
				//clicked to go back in main menu
				if (mLocX < screenSizeX / 2 + 55 && mLocX > screenSizeX / 2 - 55 &&
					mLocY < screenSizeY / 2 + 29 + 125 && mLocY > screenSizeY / 2 + 125)
				{
					loadedMenu = 0;
					choosenMenu = 0;
				}
				else if (mLocX < screenSizeX / 2 + 55 && mLocX > screenSizeX / 2 - 55 &&
					mLocY < screenSizeY / 2 + 29 + 125 && mLocY > screenSizeY / 2 + 175)
				{
					screenSizeX = 1200;
					screenSizeY = 1000;
				}
				
				mouseLeftClicked = 0;
			}

			break;

		case 3: //map editor
			if (!loadedMenu)//load map info
			{
				collisionMapInfo();
				loadedMenu = 1;
			}
			mapEditor::mapEditControl.drawMap(Surf_Display);
			moveMap();
			break;


		default:
			cout << "error: can't find selected menu" << endl;
			system("pause");
			exit(0);
			break;

		}
		accumulator -= timestep;
	}

	lastUpdate = thisUpdate;

	SDL_Delay(1);
    
}

