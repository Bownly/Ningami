#ifndef TILEOBJECT_H
#define TILEOBJECT_H
 
#include <gb/gb.h>

typedef struct TileObject {
    UINT8 x;
    UINT8 y;
    UINT8 numAdjacent;
    UINT8 isUncovered;
    UINT8 face;
} TileObject;

#endif