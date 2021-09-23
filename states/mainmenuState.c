#include <gb/gb.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"
#include "../ram.h"

#include "../maps/titlecardMap.c"
#include "../objects/DeckObject.h"
#include "../objects/PlayerObject.h"

extern const unsigned char cursorTiles[];
extern const unsigned char fontTiles[];
extern const unsigned char iconTiles[];
extern const unsigned char titlecardTiles[];

extern UINT8 curJoypad;
extern UINT8 prevJoypad;
extern UINT8 vbl_count;
extern UINT8 i;  // Used mostly for loops
extern UINT8 j;  // Used mostly for loops
extern UINT8 k;  // Used for whatever
extern UINT8 l;  // Used for whatever
extern UINT8 m;  // Used for menus generally
extern UINT8 n;  // Used for menus generally
extern UINT8 r;  // Used for randomization stuff

extern UINT8 gamestate;
extern UINT8 substate;
extern UINT8 oldGamestate;
extern UINT8 oldSubstate;

extern PlayerObject player;
extern DeckObject deck;

extern UINT8 enemyId;
extern UINT8 roomId;
extern UINT8 shopId;
extern UINT8 dialogId;
extern UINT8 dialogQueue[8U];
extern UINT8 dialogQueueCount;

extern UINT8 animTick;
extern UINT8 animFrame;

const UINT8 xAnchorMMCursor =  40U;
const UINT8 yAnchorMMCursor = 108U;

unsigned char blankTile[1U]       = { 0xFF };
unsigned char pressStartText[11U] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0xFF, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };
unsigned char newGameText[8U]     = { 0x17, 0x0E, 0x20, 0xFF, 0x10, 0x0A, 0x16, 0x0E };
unsigned char loadGameText[9U]    = { 0x15, 0x18, 0x0A, 0x0D, 0xFF, 0x10, 0x0A, 0x16, 0x0E };


/* SUBSTATE METHODS */
void phaseInitMainMenu();
void phasePressStartLoop();
void phaseMainMenuLoop();

/* HELPER METHODS */
void initPlayer();

/* DISPLAY METHODS */


void mainmenuStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case MM_INIT:
            phaseInitMainMenu();
            break;
        case MM_START_LOOP:
            phasePressStartLoop();
            break;
        case MM_LOOP:
            phaseMainMenuLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = 0U;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
void phaseInitMainMenu()
{
    setBlankBg();
    move_bkg(4U, 0U);
    DISPLAY_ON;
    SHOW_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    set_bkg_data(0U, 40U, fontTiles);
    set_bkg_data(0x30U, 70U, titlecardTiles);
    set_sprite_data(0U, 3U, cursorTiles);

    set_bkg_tiles(6U, 4U, 9U, 7U, titlecardMap);
    set_bkg_tiles(5U, 13U, 11U, 1U, pressStartText);


    m = 0U;
    enemyId = 0U;
    roomId = 0U;
    shopId = 0U;
    dialogId = 0U;
    dialogQueueCount = 0U;
    animTick = 0U;

    substate = MM_START_LOOP;
}

void phasePressStartLoop()
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
        move_sprite(0U, xAnchorMMCursor, yAnchorMMCursor);
        SHOW_SPRITES;

        for (i = 0U; i != 11U; ++i)  // 11 is the width of "press start"
            set_bkg_tiles(5U+i, 13U, 1U, 1U, blankTile);

        set_bkg_tiles(6U, 12U, 9U, 1U, loadGameText);
        set_bkg_tiles(6U, 14U, 8U, 1U, newGameText);

        substate = MM_LOOP;
    }
    prevJoypad = curJoypad;

}

void phaseMainMenuLoop()
{
    ++animTick;
    animFrame = animTick / 8U % 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    set_sprite_tile(0U, animFrame);

    if ((curJoypad & J_UP && !(prevJoypad & J_UP))
        || (curJoypad & J_DOWN && !(prevJoypad & J_DOWN)))
    {
        ++m;
        m %= 2U;
        move_sprite(0U, xAnchorMMCursor, yAnchorMMCursor + m*16U);
    }
    if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        fadeout();
        if (m == 0U)  // Load Game
        {
            ENABLE_RAM_MBC1;
            SWITCH_RAM_MBC1(0U);
            loadGameData();
            DISABLE_RAM_MBC1;
        }
        else if (m == 1U)  // New Game
        {
            initializeDeck(&deck);
            initPlayer();
        }        
        initrand(DIV_REG);
        move_bkg(0U, 0U);
        set_bkg_data(0x28U, 7U, iconTiles);
        loadOverworldGraphics();
        gamestate = STATE_OVERWORLD;
        substate = OW_INIT_OW;
    }
}


/******************************** HELPER METHODS *********************************/
void initPlayer()
{
    player.xTile = 4U;
    player.yTile = 14U;
    player.dir = N;
    player.hpMax = 10U;
    player.hpCur = 10U;
    player.mpMax = 3U;
    player.mpCur = 3U;
    player.shieldCount = 0U;
    player.atk = 0U;
    player.def = 0U;
    player.paper = 25U;
}

/******************************** DISPLAY METHODS ********************************/

