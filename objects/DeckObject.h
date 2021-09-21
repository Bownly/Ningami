#ifndef DECKOBJECT_H
#define DECKOBJECT_H

#include "CardObject.h"
#include "../common.h"

typedef struct DeckObject {
    UINT8 orderedCards[18U];
    UINT8 cardIds[18U];  // 0-17, index of orderedCards
    UINT8 discardPile[18U];  // See above
    UINT8 cardCount;
    UINT8 discardCount;
    UINT8 deckSize;
} DeckObject;

void initializeDeck(DeckObject* deck);
void addCardToDeck(DeckObject* deck, CardObject* card);
void shuffleDeck(DeckObject* deck, UINT8 shuffleCount, UINT8 includeDiscarded);
UINT8 drawCard(DeckObject* deck);
void discardCard(DeckObject* deck, UINT8 cardId);
void removeCardFromDeck(DeckObject* deck, UINT8 index);

#endif
