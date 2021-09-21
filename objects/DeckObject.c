#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "DeckObject.h"
#include "../common.h"
#include "../enums.h"

// const CARDFACE startDeck[9U] = { SHURIKEN, SHURIKEN, SHURIKEN,
//                                  SHURIKEN, SHOUZOKU, SHOUZOKU,
//                                  SHOUZOKU, SHOUZOKU,    HAATO };

const CARDFACE startDeck[18U] = { SHURIKEN, SHURIKEN, SHURIKEN, SHOUZOKU, SHOUZOKU, SHOUZOKU,
                                     HAATO, MAKIMONO,   FUUSEN,   KATANA,   KATANA,   HASAMI,
                                   HIKOUKI,  HIKOUKI,   KABUTO,   KABUTO,  ONIGIRI, SHURIKEN };


void initializeDeck(DeckObject* deck)
{
    deck->discardCount = 0U;
    deck->deckSize = 9U;

    for (deck->cardCount = 0U; deck->cardCount != deck->deckSize; deck->cardCount++)
    {
        deck->orderedCards[deck->cardCount] = startDeck[deck->cardCount];
        deck->cardIds[deck->cardCount] = deck->cardCount;
    }
}

void shuffleDeck(DeckObject* deck, UINT8 shuffleCount, UINT8 includeDiscarded)
{
    UINT8 index;
    UINT8 temp;
    UINT8 r;

    // Return discarded cards to deck
    if (includeDiscarded == TRUE)
    {
        for (index = 0U; index != deck->discardCount; ++index)
        {
            deck->cardIds[deck->cardCount] = deck->discardPile[index];
            deck->cardCount++;
        }
        deck->discardCount = 0U;
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
    return deck->cardIds[deck->cardCount];
}

void discardCard(DeckObject* deck, UINT8 cardId)
{
    deck->discardPile[deck->discardCount] = cardId;
    deck->discardCount++;
}

void removeCardFromDeck(DeckObject* deck, UINT8 index)
{
    deck->deckSize--;
    for (UINT8 c = index; c != deck->deckSize; ++c)
    {
        deck->orderedCards[c] = deck->orderedCards[c+1U];
    }

    // Reset cardIds
    for (deck->cardCount = 0U; deck->cardCount != deck->deckSize; deck->cardCount++)
    {
        deck->cardIds[deck->cardCount] = deck->cardCount;
    }
}