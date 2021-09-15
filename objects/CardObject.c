#include <gb/gb.h>
#include "../enums.h"

const UINT8 cardCostsDict[9U]       = { 1U, 2U, 3U, 0U, 1U, 2U, 2U, 0U, 2U };
const UINT8 cardValsDict[9U]        = { 3U, 7U, 11U, 2U, 3U, 7U, 5U, 1U, 3U };
const UINT8 cardTypesDict[9U]       = { CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_ATTACK, CT_SHIELD, CT_SHIELD, CT_HEAL, CT_MANA, CT_ATKDEF };
const UINT8 cardpaperCostsDict[9U]  = { 5U, 10U, 15U, 10U, 5U, 10U, 10U, 15U, 20U };

//     SHURIKEN ,  // Low cost damage
//     KATANA   ,  // High cost big damage
//     HASAMI   ,  // Higher cost bigger damage
//     HIKOUKI  ,  // Free cost, small damage
//     SHOUZOKU ,  // Low cost shield
//     KABUTO   ,  // High cost shield
//     HAATO    ,  // Heal
//     MAKIMONO ,  // Gain 1 MP
//     FUUSEN   ,  // Low damage and low shield
//     EMPTY
