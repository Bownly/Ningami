#include <gb/gb.h>

#include "../enums.h"

#include "../maps/room1Map.c"
#include "../maps/room2Map.c"

#include "../objects/EventObject.h"
#include "../objects/RoomObject.h"


const EventObject room1Events[] = {
    { .x =  5U, .y =  5U, .type = EV_DIALOG,   .value = 2U },
    { .x = 10U, .y = 10U, .type = EV_DIALOG,   .value = 3U },
    { .x = 25U, .y =  9U, .type = EV_LOADROOM, .value = 1U }
};

const EventObject room2Events[] = {
    { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value = 3U },
    { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value = 2U },
    { .x =  4U, .y = 18U, .type = EV_DIALOG,   .value = 1U },
    { .x =  0U, .y = 18U, .type = EV_LOADROOM, .value = 0U }
};

const UINT8 spawnLocations[][3] = {
    // Room num; x coord; y coord
    { 1U, 24U,  9U},
    { 2U,  1U, 18U}
};

const RoomObject roomDict[] = {
    {.id = 0U, .w = room1MapWidth, .h = room1MapHeight, .encounterRate = 10U, .roomMap = room1Map, .events = room1Events,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TSURU}},
    {.id = 0U, .w = room1MapWidth, .h = room1MapHeight, .encounterRate = 0U, .roomMap = room1Map, .events = room1Events,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TSURU}},
    {.id = 0U, .w = room2MapWidth, .h = room2MapHeight, .encounterRate =  0U, .roomMap = room2Map, .events = room2Events,
        .encounterSet = {ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU}}
    // {.id = 0U, .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TSURU}, .encounterRate = 5U, .events = *room1Events}
};
