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

extern const UINT8 cardCostsDict[9U];
extern const UINT8 cardValsDict[9U];
extern const UINT8 cardTypesDict[9U];
extern const UINT8 cardPaperCostsDict[9U];

#endif