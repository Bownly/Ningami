#include <gb/gb.h>

#include "ram.h"

#include "objects/DeckObject.h"
#include "objects/PlayerObject.h"

UBYTE ram_data[128U];
extern UBYTE *data;

extern PlayerObject player;
extern DeckObject deck;

void saveGameData()
{
    data = &ram_data[RAM_PLAYER];
    *data++ = player.x;
    *data++ = player.y;
    *data++ = player.xTile;
    *data++ = player.yTile;
    *data++ = player.dir;
    *data++ = player.hpMax;
    *data++ = player.hpCur;
    *data++ = player.mpMax;
    *data++ = player.mpCur;
    *data++ = player.shieldCount;
    *data++ = player.atk;
    *data++ = player.def;
    *data++ = player.paper;

    data = &ram_data[RAM_DECK];
    for (UINT8 i = 0U; i != 18U; ++i)  // 18 is a magic number equivalent to max deck size
    {
        *data++ = deck.orderedCards[i];
    }
    for (UINT8 i = 0U; i != 18U; ++i)  // 18 is a magic number equivalent to max deck size
    {
        *data++ = deck.cardIds[i];
    }
    *data++ = deck.cardCount;
    *data = deck.deckSize;
}

void loadGameData()
{
    data = &ram_data[RAM_PLAYER];
    player.x           = *data++;
    player.y           = *data++;
    player.xTile       = *data++;
    player.yTile       = *data++;
    player.dir         = *data++;
    player.hpMax       = *data++;
    player.hpCur       = *data++;
    player.mpMax       = *data++;
    player.mpCur       = *data++;
    player.shieldCount = *data++;
    player.atk         = *data++;
    player.def         = *data++;
    player.paper       = *data++;

    data = &ram_data[RAM_DECK];
    for (UINT8 i = 0U; i != 18U; ++i)  // 18 is a magic number equivalent to max deck size
    {
        deck.orderedCards[i] = *data++;
    }
    for (UINT8 i = 0U; i != 18U; ++i)  // 18 is a magic number equivalent to max deck size
    {
        deck.cardIds[i] = *data++;
    }
    deck.cardCount = *data++;
    deck.deckSize  = *data;
}
