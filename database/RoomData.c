#include <gb/gb.h>

#include "../enums.h"

#include "../maps/rooms/room0Map.c"
#include "../maps/rooms/room1Map.c"
#include "../maps/rooms/room2Map.c"
#include "../maps/rooms/room3Map.c"
#include "../maps/rooms/room4Map.c"
#include "../maps/rooms/room5Map.c"
#include "../maps/rooms/room6Map.c"
#include "../maps/rooms/room7Map.c"
#include "../maps/rooms/room8Map.c"
#include "../maps/rooms/room9Map.c"

#include "../objects/EventObject.h"
#include "../objects/RoomObject.h"


const EventObject room0Events[] = {
    { .x =  4U, .y =  0U, .type = EV_LOADROOM,  .value =  1U }
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
    { .x =  0U, .y =  9U, .type = EV_LOADROOM,  .value = 14U },
    { .x = 13U, .y =  0U, .type = EV_LOADROOM,  .value =  5U },
    { .x = 12U, .y = 17U, .type = EV_LOADROOM,  .value =  0U },
    { .x = 25U, .y =  9U, .type = EV_LOADROOM,  .value =  8U }
};

const EventObject room1AEvents[] = {
    { .x = 13U, .y =  8U, .type = EV_DIALOG,    .value =  9U }
};

const EventObject room2Events[] = {
    { .x = 10U, .y = 21U, .type = EV_LOADROOM,  .value =  2U },
    { .x = 10U, .y =  0U, .type = EV_LOADROOM,  .value = 20U },
    { .x =  9U, .y = 15U, .type = EV_LOADROOM,  .value = 21U }
};

const EventObject room2AEvents[] = {
    { .x =  7U, .y =  1U, .type = EV_DIALOG,    .value = 10U },
    { .x = 14U, .y =  1U, .type = EV_DIALOG,    .value = 11U }
};

const EventObject room3Events[] = {
    { .x =  0U, .y = 17U, .type = EV_LOADROOM,  .value =  4U },
    { .x =  6U, .y =  0U, .type = EV_LOADROOM,  .value = 11U },
    { .x = 15U, .y = 21U, .type = EV_LOADROOM,  .value = 13U }
};

const EventObject room3AEvents[] = {
    { .x =  2U, .y = 12U, .type = EV_DIALOG,    .value = 14U },
    { .x =  2U, .y = 12U, .type = EV_DIALOG,    .value = 13U },
    { .x = 11U, .y =  4U, .type = EV_DIALOG,    .value = 17U },
    { .x = 11U, .y =  4U, .type = EV_DIALOG,    .value = 16U },
    { .x = 11U, .y =  4U, .type = EV_DIALOG,    .value = 15U }
};

const EventObject room4Events[] = {
    { .x =  9U, .y = 25U, .type = EV_LOADROOM,  .value =  9U },
    { .x =  0U, .y = 18U, .type = EV_LOADROOM,  .value = 19U }
};

const EventObject room4AEvents[] = {
    { .x = 11U, .y =  3U, .type = EV_OPEN_SHOP, .value =  1U }
};

const EventObject room5Events[] = {
    { .x =  5U, .y =  0U, .type = EV_LOADROOM,  .value = 10U }
};

const EventObject room5AEvents[] = {
    { .x =  3U, .y =  7U, .type = EV_OPEN_SHOP, .value =  3U },
    { .x =  7U, .y =  7U, .type = EV_SAVE,      .value =  0U }
};

const EventObject room6Events[] = {
    { .x = 15U, .y =  8U, .type = EV_LOADROOM,  .value =  3U },
    { .x =  5U, .y =  0U, .type = EV_LOADROOM,  .value = 18U },
    { .x =  5U, .y = 23U, .type = EV_LOADROOM,  .value = 17U }
};

const EventObject room6AEvents[] = {
    { .x =  1U, .y =  6U, .type = EV_DIALOG,    .value = 12U }
};

const EventObject room7Events[] = {
    { .x =  5U, .y =  0U, .type = EV_LOADROOM,  .value = 16U },
    { .x =  5U, .y = 10U, .type = EV_LOADROOM,  .value = 15U },
};

const EventObject room7AEvents[] = {
    { .x =  7U, .y =  4U, .type = EV_OPEN_SHOP, .value =  2U },
    { .x =  3U, .y =  4U, .type = EV_SAVE,      .value =  0U }
};

const EventObject room8Events[] = {
    { .x = 25U, .y =  3U, .type = EV_LOADROOM,  .value = 12U },
    { .x = 11U, .y = 19U, .type = EV_LOADROOM,  .value =  6U }
};

const EventObject room8AEvents[] = {
    { .x =  7U, .y =  4U, .type = EV_OPEN_SHOP, .value =  1U }
};

const EventObject room9Events[] = {
    { .x =  7U, .y = 19U, .type = EV_LOADROOM,  .value =  7U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 24U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 23U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 22U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 21U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 20U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 19U },
    { .x =  7U, .y =  6U, .type = EV_DIALOG,    .value = 18U }
};

const EventObject room9AEvents[] = {
    { .x =  6U, .y = 18U, .type = EV_OPEN_SHOP, .value =  4U },
    { .x =  8U, .y = 18U, .type = EV_SAVE,      .value =  0U },
    { .x =  7U, .y =  5U, .type = EV_BATTLE,    .value =  ENEMY_NINJA1 }
};


const UINT8 spawnLocations[][22] = {
    // Room num; x coord; y coord; dir
    { 0U,  4U,  0U, S },
    
    { 1U, 12U, 17U, N },
    { 1U, 13U,  0U, S },
    { 1U,  0U,  9U, E },
    { 1U, 25U,  9U, W },

    { 2U, 10U, 21U, N },  // 5
    { 2U, 10U,  0U, S },
    { 2U,  9U, 15U, E },

    { 3U,  0U, 17U, E },
    { 3U,  6U,  0U, S },
    { 3U, 15U, 21U, N },  // 10

    { 4U,  9U, 25U, N },
    { 4U,  0U, 18U, E },

    { 5U,  5U,  0U, S },

    { 6U, 15U,  8U, W },
    { 6U,  5U,  0U, S },  // 15
    { 6U,  5U, 23U, N },

    { 7U,  5U,  0U, S },
    { 7U,  5U, 10U, N },

    { 8U, 25U,  3U, W },
    { 8U, 11U, 19U, N },  // 20

    { 9U,  7U, 19U, N }
};

const RoomObject roomDict[] = {
    // 0
    {.id = 0U, .w = room0MapWidth, .h = room0MapHeight, .encounterRate =  0U, .roomMap = room0Map, 
        .eventsLen = 1U, .aEventsLen = 10U, .events = room0Events, .aEvents = room0AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}},
    // 1
    {.id = 0U, .w = room1MapWidth, .h = room1MapHeight, .encounterRate = 25U, .roomMap = room1Map, .events = room1Events,
        .eventsLen = 4U, .aEventsLen = 1U, .events = room1Events, .aEvents = room1AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE}},
    // 2
    {.id = 0U, .w = room2MapWidth, .h = room2MapHeight, .encounterRate = 25U, .roomMap = room2Map, .events = room2Events,
        .eventsLen = 3U, .aEventsLen = 2U, .events = room2Events, .aEvents = room2AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_KITSUNE, ENEMY_TANUKI}},
    // 3
    {.id = 0U, .w = room3MapWidth, .h = room3MapHeight, .encounterRate = 25U, .roomMap = room3Map, .events = room3Events,
        .eventsLen = 3U, .aEventsLen = 5U, .events = room3Events, .aEvents = room3AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_KITSUNE, ENEMY_KITSUNE, ENEMY_TANUKI}},
    // 4
    {.id = 0U, .w = room4MapWidth, .h = room4MapHeight, .encounterRate = 25U, .roomMap = room4Map, .events = room4Events,
        .eventsLen = 2U, .aEventsLen = 1U, .events = room4Events, .aEvents = room4AEvents,
        .encounterSet = {ENEMY_TORI, ENEMY_KITSUNE, ENEMY_TANUKI, ENEMY_TORI}},
    // 5
    {.id = 0U, .w = room5MapWidth, .h = room5MapHeight, .encounterRate = 0U, .roomMap = room5Map, .events = room5Events,
        .eventsLen = 1U, .aEventsLen = 2U, .events = room5Events, .aEvents = room5AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}},
    // 6
    {.id = 0U, .w = room6MapWidth, .h = room6MapHeight, .encounterRate = 25U, .roomMap = room6Map, .events = room6Events,
        .eventsLen = 3U, .aEventsLen = 1U, .events = room6Events, .aEvents = room6AEvents,
        .encounterSet = {ENEMY_KITSUNE, ENEMY_TANUKI, ENEMY_TANUKI, ENEMY_KITSUNE}},
    // 7
    {.id = 0U, .w = room7MapWidth, .h = room7MapHeight, .encounterRate =  0U, .roomMap = room7Map, .events = room7Events,
        .eventsLen = 2U, .aEventsLen = 2U, .events = room7Events, .aEvents = room7AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}},
    // 8
    {.id = 0U, .w = room8MapWidth, .h = room8MapHeight, .encounterRate = 25U, .roomMap = room8Map, .events = room8Events,
        .eventsLen = 2U, .aEventsLen = 0U, .events = room8Events, .aEvents = room8AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_TORI, ENEMY_KAME, ENEMY_KAME}},
    // 9
    {.id = 0U, .w = room9MapWidth, .h = room9MapHeight, .encounterRate =  0U, .roomMap = room9Map, .events = room9Events,
        .eventsLen = 8U, .aEventsLen = 3U, .events = room9Events, .aEvents = room9AEvents,
        .encounterSet = {ENEMY_INU, ENEMY_INU, ENEMY_INU, ENEMY_INU}}
};
