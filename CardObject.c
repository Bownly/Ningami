#include <gb/gb.h>
#include "enums.h"

typedef struct CardObject {
    UINT8 id;
    CARDTYPE typeId;
    CARDFACE faceId;
    UINT8 pointVal;
    UINT8 mpCost;
} CardObject;

const UINT8 cardCostsDict[7U] = { 1U, 2U, 3U, 0U, 1U, 2U, 1U };
const UINT8 cardValsDict[7U]  = { 3U, 7U, 11U, 2U, 3U, 7U, 5U };
const UINT8 cardTypesDict[7U] = { CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_SHIELD, CT_SHIELD, CT_HEAL };

//     SHURIKEN ,  // Low cost damage
//     KATANA   ,  // High cost big damage
//     HASAMI   ,  // Higher cost bigger damage
//     HIKOUKI  ,  // Free cost, small damage
//     SHATSU   ,  // Low cost shield
//     KABUTO   ,  // High cost shield
//     HAATO    ,  // Heal
//     EMPTY    
