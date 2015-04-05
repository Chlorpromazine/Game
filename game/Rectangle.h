#ifndef _RECTANGLE_H_
    #define _RECTANGLE_H_

class rectangle{ 
public:        
	int h;   
	int w; 
	int x;
	int y;

public:        
	rectangle(){}
	//static rectangle tileCollision;
	rectangle(int height, int width,int coordX, int coordY) {  
		h = height; //of object
		w = width; 
		x = coordX; //position
		y = coordY;
	} 
};

#endif
  