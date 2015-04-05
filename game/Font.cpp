#include "Font.h"

font font::Font;

// Loads a font, nothing fancy.
// Put sensible error handling code in. If you pass the NULL in later on,
// SDL_ttf dies pretty horribly.
TTF_Font* font::loadfont(char* file, int ptsize)
{
	TTF_Font* tmpfont;
	tmpfont = TTF_OpenFont(file, ptsize);
	if (tmpfont == NULL) {
		printf("Unable to load font: %s %s \n", file, TTF_GetError());
		// Handle the error here.
	}
	return tmpfont;
}

// SDL_ttf has a few modes you can draw with, check its documentation.
SDL_Surface* font::drawtext(TTF_Font* fonttodraw, char fgR, char fgG, char fgB, char fgA,
	char bgR, char bgG, char bgB, char bgA, char text[], textquality quality)
{
	SDL_Color tmpfontcolor = { fgR, fgG, fgB, fgA };
	SDL_Color tmpfontbgcolor = { bgR, bgG, bgB, bgA };
	SDL_Surface* resulting_text;

	if (quality == solid) {
		resulting_text = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
	}
	else if (quality == shaded) {
		resulting_text = TTF_RenderText_Shaded(fonttodraw, text, tmpfontcolor, tmpfontbgcolor);
	}
	else if (quality == blended) {
		resulting_text = TTF_RenderText_Blended(fonttodraw, text, tmpfontcolor);
	}

	return resulting_text;
}
