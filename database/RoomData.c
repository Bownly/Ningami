#include <gb/gb.h>

#include "../enums.h"

#include "../maps/rooms/room0Map.c"
#include "../maps/rooms/room1Map.c"
#include "../maps/rooms/room2Map.c"

#include "../objects/EventObject.h"
#include "../objects/RoomObject.h"


const EventObject room0Events[] = {
    { .x =  4U, .y =  0U, .type = EV_LOADROOM, .value = 1U }
};

const EventObject room0AEvents[] = {
    { .x =  3U, .y = 11U, .type = EV_DIALOG,    .value = 1U },
    { .x =  3U, .y = 11U, .type = EV_DIALOG,    .value = 0U },
    { .x =  5U, .y =  8U, .type = EV_DIALOG,    .value = 3U },
    { .x =  5U, .y =  8U, .type = EV_DIALOG,    .value = 2U },
    { .x =  3U, .y =  4U, .type = EV_DIALOG,    .value = 5U },
    { .x =  3U, .y =  4U, .type = EV_DIALOG,    .value = 4U },
    { .x =  7U, .y =  5U, .type = EV_DIALOG,    .value = 7U },
    { .x =  7U, .y =  5U, .type = EV_DIALOG,    .value = 6U },
    { .x =  2U, .y =  4U, .type = EV_OPEN_SHOP, .value = 0U },
    { .x =  8U, .y =  5U, .type = EV_SAVE,      .value = 0U }
};

const EventObject room1Events[] = {
    { .x =  9U, .y =  9U, .type = EV_DIALOG,   .value = 2U },
    { .x =  9U, .y =  9U, .type = EV_DIALOG,   .value = 6U },
    { .x =  4U, .y = 17U, .type = EV_LOADROOM, .value = 0U },
    { .x = 25U, .y =  9U, .type = EV_LOADROOM, .value = 3U }
};

const EventObject room1AEvents[] = {
    { .x = 17U, .y =  2U, .type = EV_DIALOG,   .value = 6U },
    { .x = 17U, .y =  2U, .type = EV_DIALOG,   .value = 5U },
    { .x = 17U, .y =  2U, .type = EV_DIALOG,   .value = 4U },
    { .x = 25U, .y =  9U, .type = EV_LOADROOM, .value = 0U }
};

const EventObject room2Events[] = {
    { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value = 3U },
    { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value = 2U },
    { .x =  4U, .y = 18U, .type = EV_DIALOG,   .value = 1U },
    { .x =  0U, .y = 18U, .type = EV_LOADROOM, .value = 2U }
};

const EventObject room2AEvents[] = {
    { .x = 17U, .y =  3U, .type = EV_DIALOG,    .value = 6U },
    { .x = 14U, .y =  2U, .type = EV_OPEN_SHOP, .value = 0U },
    { .x = 17U, .y =  2U, .type = EV_OPEN_SHOP, .value = 1U },
    { .x =  9U, .y =  6U, .type = EV_OPEN_SHOP, .value = 2U }
};


const UINT8 spawnLocations[][4] = {
    // Room num; x coord; y coord; dir
    { 0U,  4U,  0U, S},
    { 1U,  4U, 17U, N},
    { 1U, 24U,  9U, W},
    { 2U,  1U, 18U, E}
};

const RoomObject roomDict[] = {
    {.id = 0U, .w = room0MapWidth, .h = room0MapHeight, .encounterRate =  0U, .roomMap = room0Map, 
        .eventsLen = 1U, .aEventsLen = 10U, .events = room0Events, .aEvents = room0AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TSURU}},

    {.id = 0U, .w = room1MapWidth, .h = room1MapHeight, .encounterRate = 20U, .roomMap = room1Map, .events = room1Events,
        .eventsLen = 4U, .aEventsLen = 4U, .events = room1Events, .aEvents = room1AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TSURU}},

    {.id = 0U, .w = room2MapWidth, .h = room2MapHeight, .encounterRate =  0U, .roomMap = room2Map, .events = room2Events,
        .eventsLen = 4U, .aEventsLen = 4U, .events = room2Events, .aEvents = room2AEvents,
        .encounterSet = {ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU}}
};
