#include <gb/gb.h>

#ifndef CARDOBJECT_H
#define CARDOBJECT_H
 
typedef struct CardObject {
    UINT8 id;
    CARDTYPE typeId;
    CARDFACE faceId;
    UINT8 pointVal;
    UINT8 mpCost;
} CardObject;

extern const UINT8 cardCostsDict[7U];
extern const UINT8 cardValsDict[7U];
extern const UINT8 cardTypesDict[7U];

#endif