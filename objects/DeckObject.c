#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "DeckObject.h"
#include "../common.h"
#include "../enums.h"

// test deck
const CARDFACE defaultDeck[18U] = { SHURIKEN, SHURIKEN, SHURIKEN, SHURIKEN, SHURIKEN,  SHOUZOKU,
                                    SHOUZOKU, SHOUZOKU, SHOUZOKU,   KATANA,   KATANA,    HASAMI,
                                     HIKOUKI,  HIKOUKI,   KABUTO,   KABUTO,    HAATO,     HAATO };

void initializeDeck(DeckObject* deck)
{
    deck->emptyCard.faceId = EMPTY;
    for (deck->cardCount = 0U; deck->cardCount != 18U; deck->cardCount++)
    {
        CardObject card;
        card.faceId = defaultDeck[deck->cardCount];
        card.typeId = cardTypesDict[card.faceId];
        card.mpCost = cardCostsDict[card.faceId];
        card.pointVal = cardValsDict[card.faceId];
        card.id = deck->cardCount;
        deck->orderedCards[deck->cardCount] = card; 

        // initialize cardIds and discardPile
        deck->cardIds[deck->cardCount] = deck->cardCount;
    }
    deck->discardCount = 0U;
    deck->deckSize = 18U;
}

void shuffleDeck(DeckObject* deck, UINT8 shuffleCount, UINT8 includeDiscarded)
{
    // CardObject tempCard;
    UINT8 index;
    UINT8 temp;
    UINT8 r;

    // Return discarded cards to deck
    if (includeDiscarded == TRUE)
    {
        for (deck->discardCount; deck->discardCount != 0; deck->discardCount--)
        {
            deck->cardIds[deck->cardIds[deck->cardCount + deck->discardCount] = deck->discardPile[deck->discardCount]];
            deck->cardCount++;
        }
    }

    for (shuffleCount; shuffleCount-- != 0U;)
    {
        r = getRandUint(deck->cardCount);
        index = shuffleCount % deck->cardCount;

        temp = deck->cardIds[index];
        deck->cardIds[index] = deck->cardIds[r];
        deck->cardIds[r] = temp;
    }
}

CardObject* drawCard(DeckObject* deck)
{
    deck->cardCount--;
    return &deck->orderedCards[deck->cardIds[deck->cardCount]];
}

void discardCard(DeckObject* deck, UINT8 cardId)
{
    deck->discardPile[deck->discardCount] = cardId;
    deck->discardCount++;
}
