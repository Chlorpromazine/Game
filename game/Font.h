#ifndef _FONT_H_
#define _FONT_H_

#include "Main.h"

enum textquality { solid, shaded, blended };
class font{
public:
	static font Font;
	
	TTF_Font* loadfont(char* file, int ptsize);

	SDL_Surface *drawtext(TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA,
						  char bgR, char bgG, char bgB, char bgA, char text[], textquality quality);

};



#endif