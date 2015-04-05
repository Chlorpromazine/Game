#ifndef _DEFINE_H_
    #define _DEFINE_H_

#define uint unsigned int

static int screenSizeX = 800; //width
static int screenSizeY = 608; //height

#define heroWidth 32
#define heroHeight 48

#define locationOfHeroX (screenSizeX/2)-(heroWidth/2)
#define locationOfHeroY (screenSizeY/2)-(heroHeight/2)

//collision
 //int positionOfHeroX = 400-16;
 //int positionOfHeroY = 304-24;

//map
#define mapPerAreaX 3
#define mapPerAreaY 3

#define tileSizeX 16
#define tileSizeY 16

#define mapWidth 50
#define mapHeight 38

#define moveMapSpeed 5
//ai
#define charMoveSpeed 2

#define mSpeedA 1
#define PI 3.14159265359

//mouse click
#define mouseHoldLInterval 30

#endif