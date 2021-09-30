#include <gb/gb.h>
#include "../enums.h"

#include "EnemyObject.h"

const EnemyObject enemyDex[] = {
    { .hpMax = 10U, .hpCur = 10U, .shieldsMax = 0U, .shieldsCur = 0U, .atk = 3U, .paperAmount =  5U, .enemySpr = 0U },  // Inu
    { .hpMax = 15U, .hpCur = 15U, .shieldsMax = 1U, .shieldsCur = 0U, .atk = 4U, .paperAmount = 10U, .enemySpr = 1U },  // Kitsune
    { .hpMax = 20U, .hpCur = 20U, .shieldsMax = 2U, .shieldsCur = 0U, .atk = 4U, .paperAmount = 15U, .enemySpr = 2U },  // Tanuki
    { .hpMax =  9U, .hpCur =  9U, .shieldsMax = 0U, .shieldsCur = 0U, .atk = 7U, .paperAmount = 20U, .enemySpr = 3U },  // Tori
    { .hpMax = 10U, .hpCur = 10U, .shieldsMax = 5U, .shieldsCur = 0U, .atk = 4U, .paperAmount = 20U, .enemySpr = 4U },  // Kame
    { .hpMax = 25U, .hpCur = 25U, .shieldsMax = 0U, .shieldsCur = 0U, .atk = 5U, .paperAmount =  0U, .enemySpr = 5U },  // Ninja 1
    { .hpMax = 15U, .hpCur = 15U, .shieldsMax = 3U, .shieldsCur = 0U, .atk = 4U, .paperAmount = 99U, .enemySpr = 6U }   // Ninja 2
};
