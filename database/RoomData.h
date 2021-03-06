#include <gb/gb.h>
#include "../enums.h"

#ifndef ROOMDATA_H
#define ROOMDATA_H
 
#include "../objects/EventObject.h"
#include "../objects/RoomObject.h"

extern const EventObject room1Events[];
extern const EventObject room2Events[];
extern const UINT8 spawnLocations[][22];
extern const RoomObject roomDict[];

#endif