#include <gb/gb.h>

#include "../enums.h"

extern const CARDFACE shopDex[][4U] = {
    { SHURIKEN, SHOUZOKU,  HIKOUKI,   HAATO },
    { KATANA,     KABUTO,    HAATO,  FUUSEN },
    { SHOUZOKU,   KABUTO, MAKIMONO,  FUUSEN },
    { SHURIKEN,   KATANA,   HASAMI, HIKOUKI },
    { HASAMI,   MAKIMONO,   FUUSEN, ONIGIRI }
};


// typedef enum {
//     SHURIKEN =  0U,  // Low cost damage
//     KATANA   =  1U,  // High cost big damage
//     HASAMI   =  2U,  // Higher cost bigger damage
//     HIKOUKI  =  3U,  // Free cost, small damage
//     SHOUZOKU =  4U,  // Low cost shield
//     KABUTO   =  5U,  // High cost shield
//     HAATO    =  6U,  // Heal
//     MAKIMONO =  7U,  // Gain 1 MP
//     FUUSEN   =  8U,  // Low damage and low shield
//     ONIGIRI  =  9U,  // Full heal
//     EMPTY    = 10U
