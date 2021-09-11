#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "common.h"
#include "enums.h"
#include "fade.h"

#include "CardObject.h"
#include "DeckObject.h"
#include "PlayerObject.h"

// #include "maps/textWindowMap.c"
// #include "maps/blankTileMap.c"
#include "maps/cardMaps.h"
// #include "maps/cardDescStrings.c"

#define PLAYER_SPR_NUM_START 0U
#define PLAYER_TILE_NUM_START 0U

// extern const unsigned char borderTiles[];
extern const unsigned char cardTiles[];
// extern const unsigned char cursorTiles[];
// extern const unsigned char emptyTiles[];
// extern const unsigned char fontTiles[];
// extern const unsigned char forestMetaTiles[][4U];

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

// CardObject* tempCardPtr;
extern DeckObject deck;
// EnemyObject enemy;
// HandObject hand;
extern PlayerObject player;

extern UINT8 animTick;
extern UINT8 animFrame;

/* SUBSTATE METHODS */
void phaseInitPausemenu();
void phasePausemenuLoop();

/* HELPER METHODS */
// void loadRoom();
// void checkUnderfootTile();

/* DISPLAY METHODS */
// void draw_new_bkg();
// void drawBkgTile(UINT8, UINT8, TileObject*);
void displayCursor(UINT8);
void displayCard2(CardObject*, UINT8, UINT8);
void displayFullDeck(DeckObject*, UINT8, UINT8);

void pausemenuStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case PM_INIT:
            phaseInitPausemenu();
            break;
        case PM_LOOP:
            phasePausemenuLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = 0U;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
void phaseInitPausemenu()
{
    setBlankWin();
    HIDE_SPRITES;

    // Draw deck
    initializeDeck(&deck);
    displayFullDeck(&deck, 0U, 0U);

    // Draw player stats

    // Show window
    move_win(7U, 0U);
    // move_win(SCX_REG, SCY_REG);
    SHOW_WIN;

    substate = PM_LOOP;
}

void phasePausemenuLoop()
{
    // If B or Start, hide window
    if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        substate = oldSubstate;
        gamestate = oldGamestate;
        SHOW_SPRITES;
        HIDE_WIN;
    }
}


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
void displayCard2(CardObject* card, UINT8 x, UINT8 y)
{
    switch (card->faceId)
    {
        case SHURIKEN:
            set_win_tiles(x, y, 2U, 3U, card1Map);
            break;
        case KATANA:
            set_win_tiles(x, y, 2U, 3U, card2Map);
            break;
        case HASAMI:
            set_win_tiles(x, y, 2U, 3U, card3Map);
            break;
        case HIKOUKI:
            set_win_tiles(x, y, 2U, 3U, card4Map);
            break;
        case SHOUZOKU:
            set_win_tiles(x, y, 2U, 3U, card5Map);
            break;
        case KABUTO:
            set_win_tiles(x, y, 2U, 3U, card6Map);
            break;
        case HAATO:
            set_win_tiles(x, y, 2U, 3U, card7Map);
            break;
        default:
            set_win_tiles(x, y, 2U, 3U, cardBackMap);
            set_win_tile_xy(x, y, card->faceId);
            break;
    }
}
void displayFullDeck(DeckObject* deck, UINT8 x, UINT8 y)
{
    for (i = 0U; i != deck->cardCount; i++)
    {
        displayCard2(&deck->orderedCards[deck->cardIds[i]], (i*2U)%20U + x, y + (i/10U * 3U));
    }
}

