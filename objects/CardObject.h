#include <gb/gb.h>
#include "../enums.h"

#ifndef CARDOBJECT_H
#define CARDOBJECT_H
 
typedef struct CardObject {
    UINT8 id;
    CARDFACE faceId;
    CARDTYPE typeId;
    UINT8 pointVal;
    UINT8 mpCost;
    UINT8 paperCost;
} CardObject;

#endif