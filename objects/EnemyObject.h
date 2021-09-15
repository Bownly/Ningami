#include <gb/gb.h>

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H
 
typedef struct EnemyObject {
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 shieldCount;
    UINT8 atk;
    UINT8 def;
    UINT8 enemySpr;
} EnemyObject;

extern const EnemyObject enemyDex[];

#endif