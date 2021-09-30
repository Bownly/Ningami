#include <gb/gb.h>

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H
 
typedef struct EnemyObject {
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 shieldsMax;
    UINT8 shieldsCur;
    UINT8 atk;
    UINT8 paperAmount;
    UINT8 enemySpr;
} EnemyObject;

extern const EnemyObject enemyDex[];

#endif