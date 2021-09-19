#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "DeckObject.h"
#include "../common.h"
#include "../enums.h"

// const CARDFACE startDeck[9U] = { SHURIKEN, SHURIKEN, SHURIKEN,
//                                  SHURIKEN, SHOUZOKU, SHOUZOKU,
//                                  SHOUZOKU, SHOUZOKU,    HAATO };

const CARDFACE startDeck[18U] = { SHURIKEN, SHURIKEN, SHURIKEN,   HAATO, MAKIMONO,    FUUSEN,
                                  SHOUZOKU, SHOUZOKU, SHOUZOKU,  KATANA,   KATANA,    HASAMI,
                                  HIKOUKI,  HIKOUKI,   KABUTO,   KABUTO,    HAATO,  SHURIKEN };


void initializeDeck(DeckObject* deck)
{
    deck->discardCount = 0U;
    deck->deckSize = 17U;

    for (deck->cardCount = 0U; deck->cardCount != deck->deckSize; deck->cardCount++)
    {
        deck->orderedCards[deck->cardCount] = startDeck[deck->cardCount];
        deck->cardIds[deck->cardCount] = deck->cardCount;
    }
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

UINT8 drawCard(DeckObject* deck)
{
    deck->cardCount--;
    return deck->orderedCards[deck->cardIds[deck->cardCount]];
}

void discardCard(DeckObject* deck, UINT8 cardId)
{
    deck->discardPile[deck->discardCount] = cardId;
    deck->discardCount++;
}
