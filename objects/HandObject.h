#ifndef HANDOBJECT_H
#define HANDOBJECT_H

#include "CardObject.h"
#include "../enums.h"

typedef struct HandObject {
    UINT8 playerId;
    UINT8 cardCount;
    UINT8 cardIds[4U];
    CardObject emptyCard;
} HandObject;

void initializeHand(HandObject* hand);
void addCardToHand(HandObject* hand, UINT8 cardId);
UINT8 removeCardFromHand(HandObject* hand, UINT8 cardIndex);
void sortHand(HandObject* hand);
UINT8 checkHandIsEmpty(HandObject* hand);

#endif
