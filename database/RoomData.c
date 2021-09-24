#include <gb/gb.h>

#include "../enums.h"

#include "../maps/rooms/room0Map.c"
#include "../maps/rooms/room1Map.c"
#include "../maps/rooms/room2Map.c"
#include "../maps/rooms/room3Map.c"

#include "../objects/EventObject.h"
#include "../objects/RoomObject.h"


const EventObject room0Events[] = {
    { .x =  4U, .y =  0U, .type = EV_LOADROOM, .value = 1U }
};

const EventObject room0AEvents[] = {
    { .x =  3U, .y = 11U, .type = EV_DIALOG,    .value =  1U },
    { .x =  3U, .y = 11U, .type = EV_DIALOG,    .value =  0U },
    { .x =  5U, .y =  8U, .type = EV_DIALOG,    .value =  3U },
    { .x =  5U, .y =  8U, .type = EV_DIALOG,    .value =  2U },
    { .x =  3U, .y =  4U, .type = EV_DIALOG,    .value =  5U },
    { .x =  3U, .y =  4U, .type = EV_DIALOG,    .value =  4U },
    { .x =  7U, .y =  5U, .type = EV_DIALOG,    .value =  7U },
    { .x =  7U, .y =  5U, .type = EV_DIALOG,    .value =  6U },
    { .x =  2U, .y =  4U, .type = EV_OPEN_SHOP, .value =  0U },
    { .x =  8U, .y =  5U, .type = EV_SAVE,      .value =  0U }
};

const EventObject room1Events[] = {
    { .x = 12U, .y = 17U, .type = EV_LOADROOM, .value =  0U },
    { .x = 13U, .y =  0U, .type = EV_LOADROOM, .value =  5U },
    { .x = 12U, .y = 17U, .type = EV_LOADROOM, .value =  2U },
    { .x = 25U, .y =  9U, .type = EV_LOADROOM, .value =  3U }
};

const EventObject room1AEvents[] = {
    { .x = 13U, .y =  8U, .type = EV_DIALOG,   .value =  9U }
};

const EventObject room2Events[] = {
    { .x = 10U, .y = 21U, .type = EV_LOADROOM, .value =  2U },
    { .x = 10U, .y =  0U, .type = EV_LOADROOM, .value =  2U },
    { .x =  9U, .y = 15U, .type = EV_LOADROOM, .value =  2U }
};

const EventObject room2AEvents[] = {
    { .x =  7U, .y =  1U, .type = EV_DIALOG,   .value = 10U },
    { .x = 14U, .y =  1U, .type = EV_DIALOG,   .value = 11U }
};


const EventObject room3Events[] = {
    { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value =  3U },
    // { .x = 14U, .y =  3U, .type = EV_DIALOG,   .value =  2U },
    // { .x =  4U, .y = 18U, .type = EV_DIALOG,   .value =  1U },
    // { .x =  0U, .y = 18U, .type = EV_LOADROOM, .value =  2U }
};

const EventObject room3AEvents[] = {
    { .x = 17U, .y =  3U, .type = EV_DIALOG,    .value =  6U },
    // { .x = 14U, .y =  2U, .type = EV_OPEN_SHOP, .value =  0U },
    // { .x = 17U, .y =  2U, .type = EV_OPEN_SHOP, .value =  1U },
    // { .x =  9U, .y =  6U, .type = EV_OPEN_SHOP, .value =  2U }
};



const UINT8 spawnLocations[][7] = {
    // Room num; x coord; y coord; dir
    { 0U,  4U,  0U, S},
    { 1U, 12U, 17U, N},
    { 1U, 13U,  0U, S},
    { 1U,  0U,  9U, E},
    { 1U, 25U,  9U, W},
    { 2U, 10U, 21U, N},  // 5
    { 3U,  1U, 18U, E}
};

const RoomObject roomDict[] = {
    {.id = 0U, .w = room0MapWidth, .h = room0MapHeight, .encounterRate =  0U, .roomMap = room0Map, 
        .eventsLen = 1U, .aEventsLen = 10U, .events = room0Events, .aEvents = room0AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}},

    {.id = 0U, .w = room1MapWidth, .h = room1MapHeight, .encounterRate = 20U, .roomMap = room1Map, .events = room1Events,
        .eventsLen = 4U, .aEventsLen = 1U, .events = room1Events, .aEvents = room1AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}},

    {.id = 0U, .w = room2MapWidth, .h = room2MapHeight, .encounterRate =  0U, .roomMap = room2Map, .events = room2Events,
        .eventsLen = 3U, .aEventsLen = 2U, .events = room2Events, .aEvents = room2AEvents,
        .encounterSet = {ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU}},

    {.id = 0U, .w = room3MapWidth, .h = room3MapHeight, .encounterRate =  0U, .roomMap = room3Map, .events = room3Events,
        .eventsLen = 0U, .aEventsLen = 0U, .events = room3Events, .aEvents = room3AEvents,
        .encounterSet = {ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU, ENEMY_TSURU}}
};
