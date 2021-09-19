#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "../enums.h"

typedef struct HandObject {
    UINT8 playerId;
    UINT8 cardCount;
    UINT8 cardIds[4U];
    CardObject emptyCard;
} HandObject;

void initializeHand(HandObject* hand)
{
    hand->emptyCard.faceId = EMPTY;

    for (UINT8 iter = 0U; iter != 4U; iter++)
    {
        hand->cardIds[iter] = EMPTY;
    }
    hand->cardCount = 0U;
}

void addCardToHand(HandObject* hand, UINT8 cardId)
{
    hand->cardIds[hand->cardCount] = cardId;
    hand->cardCount++;
}

UINT8 removeCardFromHand(HandObject* hand, UINT8 cardIndex)
{
    UINT8 returnVal = hand->cardIds[cardIndex];
    for (UINT8 iterator = cardIndex; iterator != (hand->cardCount-1U); iterator++)
    {
        hand->cardIds[iterator] = hand->cardIds[iterator+1U];
    }
    hand->cardCount--;
    return returnVal;
}

void sortHand(HandObject* hand)
{
    UINT8 blah = 0U;
    for (UINT8 iter = 0U; iter != 4U; iter++)
    {
        if (hand->cardIds[iter] != EMPTY)
        {
            hand->cardIds[blah] = hand->cardIds[iter];
            blah++;
        }
    }
    hand->cardCount = blah++;
}

UINT8 checkHandIsEmpty(HandObject* hand)
{
    if (hand->cardCount == 0U)
        return 1U;
    else
        return 0U;
}
