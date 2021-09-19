#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"

#include "../maps/textWindowMap.h"
#include "../maps/cardMaps.h"
#include "../maps/cardDescStrings.h"

#include "../objects/CardObject.h"
#include "../objects/DeckObject.h"
#include "../objects/PlayerObject.h"

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
UINT8 oldM;  

extern UINT8 gamestate;
extern UINT8 substate;
extern UINT8 oldGamestate;
extern UINT8 oldSubstate;

extern DeckObject deck;
extern PlayerObject player;

extern UINT8 animTick;
extern UINT8 animFrame;

const UINT8 xAnchorHp = 4U;
const UINT8 yAnchorHp = 2U;
const UINT8 xAnchorPaper = 12U;
const UINT8 yAnchorPaper = 2U;
const UINT8 xAnchorCursor = 36U;
const UINT8 yAnchorCursor = 42U;

/* SUBSTATE METHODS */
void phaseInitPausemenu();
void phasePausemenuLoop();

/* HELPER METHODS */

/* DISPLAY METHODS */
void displayDeckCursor();
void displayCardWin(CARDFACE, UINT8, UINT8);
void displayCardDescWin();
void displayFullDeck(DeckObject*, UINT8, UINT8);
void displayHp();
void displayPaper();

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

    animTick = 0U;
    animFrame = 0U;
    oldM = m;
    m = 0U;
    n = 0U;
    
    // Draw text window
    set_win_tiles(0U, 14U, 20U, 4U, textWindowMap);

    // Draw cards
    displayFullDeck(&deck, 4U, 4U);
    displayCardDescWin();

    // Draw player stats
    displayHp();
    displayPaper();

    // Show window
    move_win(7U, 0U);
    // move_win(SCX_REG, SCY_REG);
    SHOW_WIN;

    // Draw cursor
    move_sprite(0U, xAnchorCursor, yAnchorCursor);

    substate = PM_LOOP;
}

void phasePausemenuLoop()
{
    ++animTick;
    animFrame = animTick / 8U % 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    set_sprite_tile(0U, animFrame);

    // If B or Start, hide window
    if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        animTick = 0U;
        animFrame = 0U;
        m = oldM;
        move_sprite(0U, 0U, 0U);
        substate = oldSubstate;
        gamestate = oldGamestate;
        HIDE_WIN;
    }
    else if (curJoypad & J_UP && !(prevJoypad & J_UP))
    {
        if (n == 0)
        {
            n = 3U;
            do
            {
                --n;
                k = n*6U + m;
            } while (k >= deck.deckSize);
        }
        else
            --n;
        displayDeckCursor();
        displayCardDescWin();
    }
    else if (curJoypad & J_DOWN && !(prevJoypad & J_DOWN))
    {
        ++n;
        if ((n*6U + m) >= deck.deckSize)
            n = 0;
        displayDeckCursor();
        displayCardDescWin();
    }
    else if (curJoypad & J_LEFT && !(prevJoypad & J_LEFT))
    {
        if (m == 0)
        {
            if (n == (deck.deckSize-1U)/6U)  // AkA, if we're on the bottommost row
                m = (deck.deckSize-1U)%6U;
            else
                m = 5U;
        }
        else
            --m;
        displayDeckCursor();
        displayCardDescWin();
    }
    else if (curJoypad & J_RIGHT && !(prevJoypad & J_RIGHT))
    {
        ++m;
        if (m == 6 || (n*6U + m) >= deck.deckSize)
            m = 0;
        displayDeckCursor();
        displayCardDescWin();
    }
}


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
void displayCardWin(CARDFACE cardFace, UINT8 x, UINT8 y)
{
    switch (cardFace)
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
        case MAKIMONO:
            set_win_tiles(x, y, 2U, 3U, card8Map);
            break;
        case FUUSEN:
            set_win_tiles(x, y, 2U, 3U, card9Map);
            break;
        default:
            set_win_tiles(x, y, 2U, 3U, cardBackMap);
            set_win_tile_xy(x, y, cardFace);
            break;
    }
}

void displayCardDescWin()
{
    printLine(1U, 15U, cardDescStrings[(deck.orderedCards[n*6U + m])<<1U], TRUE);
    printLine(1U, 16U, cardDescStrings[((deck.orderedCards[n*6U + m])<<1U)+1U], TRUE);
}

void displayDeckCursor()
{
    move_sprite(0U, xAnchorCursor + m*16U, yAnchorCursor + n*24U);
}

void displayFullDeck(DeckObject* deck, UINT8 x, UINT8 y)
{
    for (i = 0U; i != deck->deckSize; ++i)
    {
        displayCardWin(deck->orderedCards[i], (i*2U)%12U + x, y + (i/6U * 3U));
    }
}

void displayHp()
{
    if (player.hpCur/10U != 0U)
        set_win_tile_xy(xAnchorHp, yAnchorHp, player.hpCur/10U);
    else
        set_win_tile_xy(xAnchorHp, yAnchorHp, 0xFFU);
    set_win_tile_xy(xAnchorHp+1U, yAnchorHp, player.hpCur%10U);
    set_win_tile_xy(xAnchorHp+2U, yAnchorHp, 0x27U);

    set_win_tile_xy(xAnchorHp+3U, yAnchorHp, player.hpMax/10U);
    set_win_tile_xy(xAnchorHp+4U, yAnchorHp, player.hpMax%10U);
    set_win_tile_xy(xAnchorHp+5U, yAnchorHp, 0x28U);
}

void displayPaper()
{
    if (player.paper/100U != 0U)
        set_win_tile_xy(xAnchorPaper, yAnchorPaper, player.paper/100U);
    else
        set_win_tile_xy(xAnchorPaper, yAnchorPaper, 0xFFU);
    if (player.paper/10U != 0U)
        set_win_tile_xy(xAnchorPaper+1U, yAnchorPaper, player.paper/10U %10U);
    else
        set_win_tile_xy(xAnchorPaper+1U, yAnchorPaper, 0xFFU);
    set_win_tile_xy(xAnchorPaper+2U, yAnchorPaper, player.paper%10U);
    set_win_tile_xy(xAnchorPaper+3U, yAnchorPaper, 0x2DU);
}

