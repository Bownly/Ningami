#include <gb/gb.h>
#include "rand.h"

#include "CardObject.h"
#include "enums.h"

typedef struct HandObject {
    UINT8 playerId;
    UINT8 cardCount;
    CardObject* cards[4U];
    CardObject emptyCard;
} HandObject;

void initializeHand(HandObject* hand)
{
    hand->emptyCard.faceId = EMPTY;

    for (UINT8 iter = 0U; iter != 4U; iter++)
    {
        hand->cards[iter] = &hand->emptyCard;
    }
    hand->cardCount = 0U;
}

void addCardToHand(HandObject* hand, CardObject* card)
{
    hand->cards[hand->cardCount] = card;
    hand->cardCount++;
}

CardObject* removeCardFromHand(HandObject* hand, UINT8 cardIndex)
{
    CardObject* returnVal = hand->cards[cardIndex];
    for (UINT8 iterator = cardIndex; iterator != (hand->cardCount-1U); iterator++)
    {
        hand->cards[iterator] = hand->cards[iterator+1U];
    }
    hand->cardCount--;
    return returnVal;
}

void sortHand(HandObject* hand)
{
    UINT8 blah = 0U;
    for (UINT8 iter = 0U; iter != 4U; iter++)
    {
        if (hand->cards[iter]->faceId != EMPTY)
        {
            hand->cards[blah] = hand->cards[iter];
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
