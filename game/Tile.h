#ifndef _CTILE_H_
    #define _CTILE_H_
 
#include "Define.h"
 
enum {
    TILE_TYPE_NORMAL = 0,
    TILE_TYPE_BLOCK,
	TILE_TYPE_NONE 
};
 
class Tile {
    public:
        int     TileID;
        int     TypeID;
 
    public:
        Tile();
};
 
#endif