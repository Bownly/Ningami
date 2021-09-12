#include <gb/gb.h>
#include "../enums.h"
#include "../objects/EventObject.h"

const EventObject room1Events[] = {
    { .x =  5U, .y =  5U, .type = EV_DIALOG, .value = 1U },
    { .x = 10U, .y = 10U, .type = EV_DIALOG, .value = 2U },
};

const EventObject room2Events[] = {
    { .x =  2U, .y =  2U, .type = EV_DIALOG, .value = 0U },
    { .x = 10U, .y =  2U, .type = EV_DIALOG, .value = 3U },
};
