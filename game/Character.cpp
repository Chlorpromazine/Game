#include "Character.h"

character character::charControl;

character::character()
{
	posX = 400-16;
	posY = 304-24;
}

rectangle character::coordRegion(int h, int w, int posX,int posY)
{
	return rectangle(h,w,posX,posY);
}

void character::changePosX(int X)
{
	posX += X;
}

void character::changePosY(int Y)
{
	posY += Y;
}

//returns the current position X of the character on the map
int character::retPosX()
{
	return posX;
}

//returns the current position Y of the character on the map
int character::retPosY()
{
	return posY;
}

//pathing
