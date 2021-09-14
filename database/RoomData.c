#include <gb/gb.h>
#include "../enums.h"
#include "../objects/EventObject.h"

const EventObject room1Events[] = {
    { .x =  5U, .y =  5U, .type = EV_DIALOG, .value = 2U },
    { .x = 10U, .y = 10U, .type = EV_DIALOG, .value = 3U },
};

const EventObject room2Events[] = {
    { .x = 14U, .y =  3U, .type = EV_DIALOG, .value = 3U },
    { .x = 14U, .y =  3U, .type = EV_DIALOG, .value = 2U },
    { .x =  4U, .y = 18U, .type = EV_DIALOG, .value = 1U }
};
