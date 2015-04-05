#ifndef _CHARACTER_H_
    #define _CHARACTER_H_

#include "Rectangle.h"
#include "Collision.h"
using namespace std;

class character{
private: 
	int posX;
	int posY;

	

public:
	static character charControl;
	character();
	rectangle coordRegion(int h, int w, int posX,int posY);
	
	void changePosX(int X);
	void changePosY(int Y);

	int retPosX();
	int retPosY();
	
	
};


#endif