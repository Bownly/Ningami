#include <gb/gb.h>
#include <rand.h>

#include "common.h"
#include "enums.h"
#include "fade.h"
#include "ram.h"

#include "objects/DeckObject.h"
#include "objects/PlayerObject.h"

#include "maps/textWindowMap.h"
#include "maps/blankTileMap.h"

#include "states/battleState.h"
#include "states/dialogState.h"
#include "states/overworldState.h"
#include "states/mainmenuState.h"
#include "states/pausemenuState.h"
#include "states/shopState.h"

// Save data stuff
const UBYTE RAM_SIG[7U] = {'N','I','N','G','A','M','I'};
UBYTE *data;

UINT8 vbl_count;
UINT8 curJoypad;
UINT8 prevJoypad;
UINT8 i;  // Used mostly for loops
UINT8 j;  // Used mostly for loops
UINT8 k;  // Used for whatever
UINT8 l;  // Used for whatever
UINT8 m;  // Used for menus generally
UINT8 n;  // Used for menus generally
UINT8 r;  // Used for randomization stuff

UINT8 gamestate = STATE_TITLE;
UINT8 substate;
UINT8 oldGamestate;
UINT8 oldSubstate;

PlayerObject player;
DeckObject deck;

UINT8 enemyId = 0U;
UINT8 roomId = 0U;
UINT8 shopId = 0U;
UINT8 dialogId = 0U;
UINT8 dialogQueue[8];
UINT8 dialogQueueCount = 0U;

UINT8 animFrame = 0U;
UINT8 animTick = 0U;

void setBlankBg();
void initRAM(UBYTE);


void vbl_update() {
	++vbl_count;
}

void main()
{
 	initRAM(0U);
    gamestate = STATE_TITLE;
    substate = MM_INIT;

    while(1U)
    {
        if(!vbl_count)
            wait_vbl_done();
        vbl_count = 0U;

        switch(gamestate)
        {
            case STATE_TITLE:
                SWITCH_ROM_MBC1(3U);
                mainmenuStateMain();
                break;
            case STATE_BATTLE:
                SWITCH_ROM_MBC1(1U);
                battleStateMain();
                break;
            case STATE_OVERWORLD:
                SWITCH_ROM_MBC1(2U);
                overworldStateMain();
                break;
            case STATE_PAUSEMENU:
                SWITCH_ROM_MBC1(3U);
                pausemenuStateMain();
                break;
            case STATE_DIALOG:
                SWITCH_ROM_MBC1(4U);
                dialogStateMain();
                break;
            case STATE_SHOP:
                SWITCH_ROM_MBC1(5U);
                shopStateMain();
                break;
        }
        // Music stuff
        // songPlayerUpdate();
    }
}

void initRAM(UBYTE force_clear)
{
    UBYTE initialized;

    ENABLE_RAM_MBC1;
    SWITCH_RAM_MBC1(0U);

    // Check for signature
    initialized = 1U;
    for (i = 0U; i != 7U; ++i)
    {
        if (ram_data[RAM_SIG_ADDR + i] != RAM_SIG[i])
        {
            initialized = 0U;
            break;
        }
    }

    // Initialize memory
    if (initialized == 0U || force_clear)
    {
        for(i = 0U; i != 255U; ++i) {
            ram_data[i] = 0U;
        }

        for (i = 0U; i != 7U; ++i) {
            ram_data[RAM_SIG_ADDR + i] = RAM_SIG[i];
        }
    }

    DISABLE_RAM_MBC1;
}
