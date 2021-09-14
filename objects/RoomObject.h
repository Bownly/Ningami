#include <gb/gb.h>
#include "../enums.h"
#include "../objects/EventObject.h"

#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

typedef struct RoomObject {
    UINT8 id;
    UINT8 encounters[3U];
    UINT8 encounterRate;
    EventObject events[];
} RoomObject;

#endif