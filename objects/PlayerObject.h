#include <gb/gb.h>

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
 
typedef struct PlayerObject {
    UINT8 x;
    UINT8 y;
    UINT8 xTile;
    UINT8 yTile;
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 mpMax;
    UINT8 mpCur;
    UINT8 shieldCount;
    UINT8 atk;
    UINT8 def;
    UINT8 paper;
} PlayerObject;

#endif