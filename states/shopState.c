#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"

#include "../database/CardData.h"
#include "../database/ShopData.h"

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
UINT8 prevM;

extern UINT8 gamestate;
extern UINT8 substate;
extern UINT8 oldGamestate;
extern UINT8 oldSubstate;

extern DeckObject deck;
extern PlayerObject player;

extern UINT8 shopId;

extern UINT8 animTick;
extern UINT8 animFrame;

#define stringA     "A TO BUY         "
#define stringB     "B TO NOT BUY     "
#define stringPoor1 "NO CAN DO. YOU   "
#define stringPoor2 "NEED MORE PAPER. "
#define stringDeck1 "SORRY, PAL. YOUR "
#define stringDeck2 "DECK IS FULL.    "

const UINT8 xAnchorCursorShop = 28U;
const UINT8 yAnchorCursorShop = 58U;
const UINT8 xAnchorDeckSizeShop = 3U;
const UINT8 yAnchorDeckSizeShop = 2U;
const UINT8 xAnchorPaperShop = 13U;
const UINT8 yAnchorPaperShop = 2U;


/* SUBSTATE METHODS */
void phaseInitShop();
void phaseSelectCardToBuy();
void phaseBuyYNLoop();
void phaseRejectMessageLoop();

/* HELPER METHODS */

/* DISPLAY METHODS */
void displayCardDescWinShop();
void displayCardWinShop(CARDFACE, UINT8, UINT8);
void displayDeckSize();
void displayShopCursor();
void displayShopPaper();
void displayShopStock(UINT8, UINT8);
void displayYNText();

void shopStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case SHOP_INIT:
            phaseInitShop();
            break;
        case SHOP_SELECT_CARD:
            phaseSelectCardToBuy();
            break;
        case SHOP_YN_LOOP:
            phaseBuyYNLoop();
            break;
        case SHOP_REJECT_LOOP:
            phaseRejectMessageLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = MM_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
void phaseInitShop()
{
    setBlankWin();

    animTick = 0U;
    animFrame = 0U;
    prevM = m;
    m = 0U;
    
    // Draw text window
    set_win_tiles(0U, 14U, 20U, 4U, textWindowMap);

    // Draw cards
    displayShopStock(3U, 6U);
    displayCardDescWinShop();

    // Draw player stats
    displayShopPaper();
    displayDeckSize();

    // Show window
    move_win(7U, 0U);
    SHOW_WIN;

    // Draw cursor
    move_sprite(0U, xAnchorCursorShop, yAnchorCursorShop);

    substate = SHOP_SELECT_CARD;
}

void phaseSelectCardToBuy()
{
    // Cursor anim
    ++animTick;
    animFrame = animTick / 8U % 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    set_sprite_tile(0U, animFrame);

    if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        displayYNText();
        substate = SHOP_YN_LOOP;
    }
    else if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        animTick = 0U;
        animFrame = 0U;
        m = prevM;
        move_sprite(0U, 0U, 0U);
        substate = oldSubstate;
        gamestate = oldGamestate;
        HIDE_WIN;
    }
    else if (curJoypad & J_LEFT && !(prevJoypad & J_LEFT))
    {
        if (m-- == 0U)
            m = 3U;  // Magic number equal to amount of cards in stock - 1

        displayShopCursor();
        displayCardDescWinShop();
        // TODO: playMoveSfx();
    }
    else if (curJoypad & J_RIGHT && !(prevJoypad & J_RIGHT))
    {
        if (++m == 4U)  // Magic number equal to amount of cards in stock
            m = 0U;

        displayShopCursor();
        displayCardDescWinShop();
        // TODO: playMoveSfx();
    }
}

void phaseBuyYNLoop()
{
    if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        k = cardDex[shopDex[shopId][m]].paperCost;

        if (deck.deckSize == 18U)
        {
            printLine(1U, 15U, stringDeck1, TRUE);
            printLine(1U, 16U, stringDeck2, TRUE);
            substate = SHOP_REJECT_LOOP;
            // TODO: sfx
        }
        else if (player.paper < k)  // Too poor
        {
            printLine(1U, 15U, stringPoor1, TRUE);
            printLine(1U, 16U, stringPoor2, TRUE);
            substate = SHOP_REJECT_LOOP;
            // TODO: sfx
        }
        else
        {
            // Subtract paper
            player.paper -= k;

            // Add card to deck
            shuffleDeck(&deck, 0U, TRUE);
            deck.orderedCards[deck.cardCount] = shopDex[shopId][m];
            deck.cardIds[deck.cardCount] = deck.cardCount;
            deck.cardCount++;
            deck.deckSize++;

            // Update UI
            displayShopPaper();
            displayDeckSize();

            // Retvrn to loop
            substate = SHOP_SELECT_CARD;
            displayCardDescWinShop();

            // TODO: sfx
        }

    }
    else if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        substate = SHOP_SELECT_CARD;
        displayCardDescWinShop();
    }
}

void phaseRejectMessageLoop()
{
    if ((curJoypad & J_A && !(prevJoypad & J_A))
        || (curJoypad & J_B && !(prevJoypad & J_B)))
    {
        substate = SHOP_SELECT_CARD;
        displayCardDescWinShop();
    }
}

/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
void displayCardDescWinShop()
{
    printLine(1U, 15U, cardDescStrings[(shopDex[shopId][m])<<1U], TRUE);
    printLine(1U, 16U, cardDescStrings[((shopDex[shopId][m])<<1U)+1U], TRUE);
}

void displayCardWinShop(CARDFACE cardFace, UINT8 x, UINT8 y)
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
        case ONIGIRI:
            set_win_tiles(x, y, 2U, 3U, card10Map);
            break;
        default:
            set_win_tiles(x, y, 2U, 3U, cardBackMap);
            set_win_tile_xy(x, y, cardFace);
            break;
    }

    // Paper cost
    k = cardDex[cardFace].paperCost;
    y += 3;  // Increment once instead of once per line for the next 3 lines
    if (k > 9U)
        set_win_tile_xy(x-1U, y, k/10U);
    set_win_tile_xy(x, y, k%10U);
    set_win_tile_xy(x+1U, y, 0x2D);

}

void displayDeckSize()
{
    if (deck.deckSize/10U != 0U)
        set_win_tile_xy(xAnchorDeckSizeShop, yAnchorDeckSizeShop, deck.deckSize/10U);
    else
        set_win_tile_xy(xAnchorDeckSizeShop, yAnchorDeckSizeShop, 0xFFU);
    set_win_tile_xy(xAnchorDeckSizeShop+1U, yAnchorDeckSizeShop, deck.deckSize%10U);
    set_win_tile_xy(xAnchorDeckSizeShop+2U, yAnchorDeckSizeShop, 0x27U);

    set_win_tile_xy(xAnchorDeckSizeShop+3U, yAnchorDeckSizeShop, 1U);
    set_win_tile_xy(xAnchorDeckSizeShop+4U, yAnchorDeckSizeShop, 8U);
    set_win_tile_xy(xAnchorDeckSizeShop+5U, yAnchorDeckSizeShop, 0x2BU);
}

void displayShopCursor()
{
    move_sprite(0U, xAnchorCursorShop + m*32U, yAnchorCursorShop);
}

void displayShopPaper()
{
    if (player.paper/100U != 0U)
        set_win_tile_xy(xAnchorPaperShop, yAnchorPaperShop, player.paper/100U);
    else
        set_win_tile_xy(xAnchorPaperShop, yAnchorPaperShop, 0xFFU);
    if (player.paper/10U != 0U)
        set_win_tile_xy(xAnchorPaperShop+1U, yAnchorPaperShop, player.paper/10U %10U);
    else
        set_win_tile_xy(xAnchorPaperShop+1U, yAnchorPaperShop, 0xFFU);
    set_win_tile_xy(xAnchorPaperShop+2U, yAnchorPaperShop, player.paper%10U);
    set_win_tile_xy(xAnchorPaperShop+3U, yAnchorPaperShop, 0x2DU);
}

void displayShopStock(UINT8 x, UINT8 y)
{
    for (i = 0U; i != 4U; ++i)
    {
        displayCardWinShop(shopDex[shopId][i], (i*4U) + x, y);
    }
}

void displayYNText()
{
    printLine(1U, 15U, stringA, TRUE);
    printLine(1U, 16U, stringB, TRUE);
}
