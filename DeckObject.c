#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "common.h"
#include "enums.h"

// test deck
const CARDFACE defaultDeck[18U] = { SHURIKEN, SHURIKEN, SHURIKEN, SHURIKEN, SHURIKEN,  SHATSU,
                                      SHATSU,   SHATSU,   SHATSU,   KATANA,   KATANA,  HASAMI,
                                     HIKOUKI,  HIKOUKI,   KABUTO,   KABUTO,    HAATO,   HAATO };

typedef struct DeckObject {
    UINT8 cardCount;
    CardObject orderedCards[18U];
    UINT8 cardIds[18U];
} DeckObject;

void initializeDeck(DeckObject* deck)
{
    for (deck->cardCount = 0U; deck->cardCount != 18U; deck->cardCount++)
    {
        CardObject card;
        card.faceId = defaultDeck[deck->cardCount];
        card.typeId = cardTypesDict[card.faceId];
        card.mpCost = cardCostsDict[card.faceId];
        card.pointVal = cardValsDict[card.faceId];
        card.id = deck->cardCount;
        deck->orderedCards[deck->cardCount] = card; 

        // initialize cardIds
        deck->cardIds[deck->cardCount] = deck->cardCount;
    }
}

void shuffleDeck(DeckObject* deck, UINT8 shuffleCount)
{
    // CardObject tempCard;
    UINT8 index;
    UINT8 temp;
    UINT8 r;

    for (shuffleCount; shuffleCount-- != 0U;)
    {
        r = getRandUint(18U);
        index = shuffleCount % 18U;

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
