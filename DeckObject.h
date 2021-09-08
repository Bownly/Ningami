#ifndef DECKOBJECT_H
#define DECKOBJECT_H

#include "CardObject.h"
#include "common.h"

typedef struct DeckObject {
    UINT8 cardCount;
    CardObject orderedCards[30U];
    UINT8 cardIds[30U];
} DeckObject;

void initializeDeck(DeckObject* deck);
void addCardToDeck(DeckObject* deck, CardObject* card);
void shuffleDeck(DeckObject* deck, UINT8 shuffleCount, UINT8 includeDiscarded);
CardObject* drawCard(DeckObject* deck);
void discardCard(DeckObject* deck, UINT8 cardId);

#endif
