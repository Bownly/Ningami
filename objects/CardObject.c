#include <gb/gb.h>
#include "../enums.h"

const UINT8 cardCostsDict[7U] = { 1U, 2U, 3U, 0U, 1U, 2U, 2U };
const UINT8 cardValsDict[7U]  = { 3U, 7U, 11U, 2U, 3U, 7U, 5U };
const UINT8 cardTypesDict[7U] = { CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_SHIELD, CT_SHIELD, CT_HEAL };

//     SHURIKEN ,  // Low cost damage
//     KATANA   ,  // High cost big damage
//     HASAMI   ,  // Higher cost bigger damage
//     HIKOUKI  ,  // Free cost, small damage
//     SHOUZOKU ,  // Low cost shield
//     KABUTO   ,  // High cost shield
//     HAATO    ,  // Heal
//     EMPTY    
