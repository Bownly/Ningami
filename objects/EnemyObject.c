#include <gb/gb.h>
#include "../enums.h"

typedef struct EnemyObject {
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 shieldCount;
    UINT8 atk;
    UINT8 def;
} EnemyObject;

const EnemyObject enemyDex[] = {
    { .hpMax = 10U, .hpCur = 10U, .shieldCount = 0U, .atk = 3U, .def = 0U },
    { .hpMax = 11U, .hpCur = 11U, .shieldCount = 0U, .atk = 6U, .def = 1U }
};
