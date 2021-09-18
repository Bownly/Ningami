#include <gb/gb.h>

#include "../enums.h"
#include "../objects/CardObject.h"

extern const CardObject cardDex[9] = {
    {.id = 0U, .faceId = SHURIKEN, .typeId = CT_ATTACK, .pointVal =  3U, .mpCost = 1U, .paperCost =  5U },
    {.id = 1U, .faceId = KATANA,   .typeId = CT_ATTACK, .pointVal =  7U, .mpCost = 2U, .paperCost = 10U },
    {.id = 2U, .faceId = HASAMI,   .typeId = CT_ATTACK, .pointVal = 11U, .mpCost = 3U, .paperCost = 16U },
    {.id = 3U, .faceId = HIKOUKI,  .typeId = CT_ATTACK, .pointVal =  2U, .mpCost = 0U, .paperCost = 10U },
    {.id = 4U, .faceId = SHOUZOKU, .typeId = CT_SHIELD, .pointVal =  3U, .mpCost = 1U, .paperCost =  5U },
    {.id = 5U, .faceId = KABUTO,   .typeId = CT_SHIELD, .pointVal =  7U, .mpCost = 2U, .paperCost = 10U },
    {.id = 6U, .faceId = HAATO,    .typeId = CT_HEAL,   .pointVal =  5U, .mpCost = 2U, .paperCost = 10U },
    {.id = 7U, .faceId = MAKIMONO, .typeId = CT_MANA,   .pointVal =  1U, .mpCost = 0U, .paperCost = 15U },
    {.id = 8U, .faceId = FUUSEN,   .typeId = CT_ATKDEF, .pointVal =  3U, .mpCost = 2U, .paperCost = 20U }
};
