#include <gb/gb.h>
#include "../enums.h"
#include "../objects/EventObject.h"

#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

typedef struct RoomObject {
    UINT8 id;
    UINT8 w;
    UINT8 h;
    UINT8 encounterRate;
    const unsigned char *roomMap;
    EventObject *events;
    EventObject *aEvents;
    ENEMYTYPE encounterSet[4U];
} RoomObject;

#endif