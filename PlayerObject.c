#include <gb/gb.h>
#include "enums.h"

typedef struct PlayerObject {
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 mpMax;
    UINT8 mpCur;
    UINT8 shieldCount;
    UINT8 atk;
    UINT8 def;
} PlayerObject;

