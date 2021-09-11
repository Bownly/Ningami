#include <gb/gb.h>
#include <rand.h>

#include "common.h"
#include "enums.h"
#include "fade.h"

#include "battleState.h"
#include "overworldState.h"

#include "PlayerObject.h"

#include "maps/textWindowMap.h"
#include "maps/blankTileMap.h"
#include "maps/titlecardMap.c"
// #include "maps/cardMaps.c"
// #include "maps/scoreNumMaps.c"

extern const unsigned char borderTiles[];
extern const unsigned char cardTiles[];
extern const unsigned char cursorTiles[];
extern const unsigned char fontTiles[];
extern const unsigned char iconTiles[];
extern const unsigned char titlecardTiles[];
// extern const unsigned char scorenumTiles[];

void setBlankBg();
void titleInit();
void titlePressStartLoop();
void initPlayer();

// Save data stuff
const UBYTE RAM_SIG[8U] = {'N','I','N','G','A','M','I',' '};
UBYTE *data;

// const UINT8 borderTileIndex    = 0x30;
// const UINT8 cardsTileIndex     = 0x40;
// const UINT8 scoreNumsTileIndex = 0xB0;

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

PlayerObject player;
UINT8 enemyId;
UINT8 roomId = 1U;

UINT8 animTick = 0U;
// UINT8 maxAnimTick = 96U;  // Arbitrary value with lots of factors

unsigned char blankTile[1U]       = { 0xFF };
unsigned char pressStartText[12U] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0xFF, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };

void vbl_update() {
	++vbl_count;
}

void main()
{
 	// initRAM(0U);
    gamestate = STATE_TITLE;
    substate = 0U;

    while(1U)
    {
        if(!vbl_count)
            wait_vbl_done();
        vbl_count = 0U;

        switch(gamestate)
        {
            case STATE_TITLE:
                if (substate == 0U)
                {
                    titleInit();
                }
                else if (substate == 1U)
                {
                    titlePressStartLoop();
                }
                break;
            case STATE_BATTLE:
                SWITCH_ROM_MBC1(1U);
                battleStateMain();
                break;
            case STATE_OVERWORLD:
                SWITCH_ROM_MBC1(2U);
                overworldStateMain();
                break;
        }
        // // music stuff
        // songPlayerUpdate();
    }
}

void titleInit()
{
    setBlankBg();
    move_bkg(4U, 0U);
    DISPLAY_ON;
    SHOW_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    set_bkg_data(0U, 40U, fontTiles);
    SWITCH_ROM_MBC1(3U);
    set_bkg_data(0x30U, 70U, titlecardTiles);
    set_bkg_tiles(6U, 4U, 9U, 7U, titlecardMap);

    set_bkg_tiles(5U, 13U, 11U, 1U, pressStartText);

    substate = 1U;
    animTick = 0U;
}

void titlePressStartLoop()
{
    animTick++;
    if ((animTick % 64U) / 48U == 0U)
    {
        set_bkg_tiles(5U, 13U, 11U, 1U, pressStartText);
    }
    else
    {
        for (i = 0U; i != 11U; ++i)  // 11 is the width of "press start"
            set_bkg_tiles(5U+i, 13U, 1U, 1U, blankTile);
    }

    curJoypad = joypad();
    if (curJoypad & J_START && !(prevJoypad & J_START))
    {
        fadeout();
        move_bkg(0U, 0U);
        set_bkg_data(0x28U, 4U, iconTiles);
        initrand(DIV_REG);
        initPlayer();
        gamestate = STATE_BATTLE;
        substate = GAME_KAISHI;
    }
    else if (curJoypad & J_SELECT && !(prevJoypad & J_SELECT))
    {
        fadeout();
        move_bkg(0U, 0U);
        set_bkg_data(0x28U, 4U, iconTiles);
        initrand(DIV_REG);
        initPlayer();
        gamestate = STATE_OVERWORLD;
        substate = OW_INIT_OW;
    }
    else if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        roomId = 2U;
    }
    prevJoypad = curJoypad;
}

void initPlayer()
{
    player.x = 80U;
    player.y = 88U;
    player.hpMax = 10U;
    player.hpCur = 10U;
    player.mpMax = 3U;
    player.mpCur = 3U;
    player.shieldCount = 0U;
    player.atk = 0U;
    player.def = 0U;
}

