// #include <gb/gb.h>
// #include "rand.h"

// #include "CardObject.h"
// #include "enums.h"

// typedef struct StackObject {
//     UINT8 cardCount;
//     CardObject* cards[10U];
// } StackObject;

// void addCardToStack(StackObject* stack, CardObject* card)
// {
//     // for bolted cards
//     if (stack->cardCount != 0U)
//     {
//         UINT8 count = stack->cardCount;
//         while (stack->cards[count-1U]->isFaceUp == 0U && count != 0U)
//         {
//             count--;
//         }
//         stack->cardCount = count;
//     } 

//     card->isFaceUp = 1U;
//     stack->cards[stack->cardCount++] = card;
// }

// CardObject* removeCardFromStack(StackObject* stack, UINT8 cardIndex)
// {
//     CardObject* returnVal = stack->cards[cardIndex];
//     for (UINT8 iterator = cardIndex; iterator != (stack->cardCount-1); iterator++)
//     {
//         stack->cards[iterator] = stack->cards[iterator+1];
//     }
//     stack->cardCount--;
//     return returnVal;
// }

// void clearStack(StackObject* stack)
// {
//     stack->cardCount = 0U;
// }

// void killStackTopCard(StackObject* stack)
// {
//     UINT8 count = 1U;
//     while (count != 0U)
//     {
//         if (stack->cards[(stack->cardCount)-count]->isFaceUp == 0U)
//         {
//             count++;
//         }
//         else
//         {
//             stack->cards[(stack->cardCount)-count]->isFaceUp = 0U;
//             count = 0U;
//         }
//     }
// }

// void reviveStackTopCard(StackObject* stack)
// {
//     stack->cards[(stack->cardCount)-1]->isFaceUp = 1U;
// }

// UINT8 getStackScoreSum(StackObject* stack)
// {
//     UINT8 sum = 0U;
//     for (UINT8 iter = 0U; iter != stack->cardCount; iter++)
//     {
//         if (stack->cards[iter]->isFaceUp == 1U)
//         {
//             sum += stack->cards[iter]->pointVal;
//         }
//     }
//     return sum;
// }
