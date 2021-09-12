#ifndef DECKOBJECT_H
#define DECKOBJECT_H

#include "CardObject.h"
#include "common.h"

extern const CARDFACE defaultDeck[18U];

typedef struct DeckObject {
    UINT8 cardCount;
    CardObject orderedCards[18U];
    UINT8 cardIds[18U];
    CardObject emptyCard;
    UINT8 discardCount;
    UINT8 discardPile[18U];
    UINT8 deckSize;
} DeckObject;

void initializeDeck(DeckObject* deck);
void addCardToDeck(DeckObject* deck, CardObject* card);
void shuffleDeck(DeckObject* deck, UINT8 shuffleCount, UINT8 includeDiscarded);
CardObject* drawCard(DeckObject* deck);
void discardCard(DeckObject* deck, UINT8 cardId);

#endif
