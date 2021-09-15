#include <gb/gb.h>
#include "../enums.h"

#include "EnemyObject.h"

// typedef struct EnemyObject {
//     UINT8 hpMax;
//     UINT8 hpCur;
//     UINT8 shieldCount;
//     UINT8 atk;
//     UINT8 def;
//     UINT8 enemySpr;
// } EnemyObject;

const EnemyObject enemyDex[] = {
    { .hpMax = 10U, .hpCur = 10U, .shieldCount = 0U, .atk = 3U, .def = 0U, .enemySpr = 0U },
    { .hpMax = 15U, .hpCur = 15U, .shieldCount = 0U, .atk = 4U, .def = 0U, .enemySpr = 1U },
    { .hpMax = 20U, .hpCur = 20U, .shieldCount = 0U, .atk = 4U, .def = 1U, .enemySpr = 2U },
    { .hpMax = 11U, .hpCur = 11U, .shieldCount = 0U, .atk = 0U, .def = 0U, .enemySpr = 1U }
};
