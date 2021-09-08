#include <gb/gb.h>
#include <rand.h>

#include "common.h"
#include "enums.h"
#include "fade.h"

#include "CardObject.h"
#include "DeckObject.c"
#include "EnemyObject.h"
#include "HandObject.c"
#include "PlayerObject.h"

#include "maps/textWindowMap.c"
#include "maps/blankTileMap.c"
#include "maps/cardMaps.c"
#include "maps/enemyMap.c"
// #include "maps/scoreNumMaps.c"

extern const unsigned char borderTiles[];
extern const unsigned char cardTiles[];
extern const unsigned char cursorTiles[];
extern const unsigned char emptyTiles[];
extern const unsigned char enemyHorseTiles[];
extern const unsigned char fontTiles[];
// extern const unsigned char scorenumTiles[];

const UINT8 borderTileIndex = 0x30;
const UINT8 cardsTileIndex  = 0x40;
const UINT8 enemyTileIndex  = 0xB0;
// const UINT8 scoreNumsTileIndex = 0xB0;

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

CardObject* tempCardPtr;
DeckObject deck;
EnemyObject enemy;
HandObject hand;
extern PlayerObject player;

UINT8 xAnchorHand = 6U;
const UINT8 yAnchorHand = 11U;
const UINT8 xAnchorHP = 2U;
const UINT8 yAnchorHP = 12U;
const UINT8 xAnchorMP = 16U;
const UINT8 yAnchorMP = 12U;
const UINT8 xAnchorShield = 15U;
const UINT8 yAnchorShield = 13U;
const UINT8 xAnchorEnemy = 8U;
const UINT8 yAnchorEnemy = 4U;

extern UINT8 animTick;
const UINT8 maxAnimTick = 16U;
ANIMTYPE curAnim = ANIM_ENEMY_ATTACK;

const unsigned char blankEnemyMap[16U] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

/* SUBSTATE METHODS */
void phaseOpunZaGeimu();
void phaseStartTurn();
void phaseSelectCard();
void phaseUseCard();
void phaseAnimatePlayerMove();
void phaseEnemyTurn();
void phaseAnimateEnemyMove();
void phaseWinCheck();
void phaseLoseCheck();
void phaseShowMessages();
void phaseCalcSpoils();
void phaseEndBattle();

/* HELPER METHODS */
void queueMessage(UINT8, UINT8);

/* DISPLAY METHODS */
void displayCursor(UINT8);
void displayCard(CardObject*, UINT8, UINT8);
void displayHand(HandObject*, UINT8, UINT8);
void displayFullDeck(DeckObject*, UINT8, UINT8);
void displayHP();
void displayMP();
void displayShields();
// void displayScore(UINT8);
// void displayScoreDigit(UINT8, UINT8, UINT8);
// void displayStack(StackObject*, UINT8, UINT8, UINT8);


void battleStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case GAME_KAISHI:
            phaseOpunZaGeimu();
            break;
        case TURN_KAISHI:
            phaseStartTurn();
            break;
        case CARD_SELECT:
            phaseSelectCard();
            break;
        case USE_CARD:
            phaseUseCard();
            break;
        case PLAYER_ANIM:
            phaseAnimatePlayerMove();
            break;
        case ENEMY_TURN:
            phaseEnemyTurn();
            break;
        case ENEMY_ANIM:
            phaseAnimateEnemyMove();
            break;
        case WIN_CHECK:
            phaseWinCheck();
            break;
        case LOSE_CHECK:
            phaseLoseCheck();
            break;
        case SHOW_MESSAGES:
            phaseShowMessages();
            break;
        case CALC_SPOILS:
            phaseCalcSpoils();
            break;
        case BATTLE_END:
            phaseEndBattle();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = MAIN_TITLE;
            substate = 0;
            break;
    }
    prevJoypad = curJoypad;
}

void phaseOpunZaGeimu()
{
    // Initialize variables and graphics
    setBlankBg();
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    set_bkg_data(0U, 40U, fontTiles);
    set_bkg_data(borderTileIndex, 8U, borderTiles);
    set_bkg_data(cardsTileIndex, 60U, cardTiles);
    set_sprite_data(0U, 3U, cursorTiles);
    // set_bkg_data(scoreNumsTileIndex, 20U, scorenumTiles);

    move_bkg(0, 0);
    set_bkg_tiles(0U, 18U, 16U, 1U, blankEnemyMap);
    
    // TODO make this variable based on different enemy types    
    set_bkg_data(enemyTileIndex, 16U, enemyHorseTiles);
    enemy.hpMax = 100U;
    enemy.hpCur = 100U;
    enemy.shieldCount = 0U;
    enemy.atk = 2U;
    enemy.def = 0U;

    xAnchorHand = 6U;

    initrand(DIV_REG);
    // Initialize deck and hand; shuffle deck
    initializeDeck(&deck);
    shuffleDeck(&deck, 64U, FALSE);
    initializeHand(&hand);

    // Show enemies on screen
    set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, enemyMap);

    // Show player stats on screen
    displayHP();
    displayMP();
    displayShields();

    // Initialize score vals

    // Set substate
    substate = TURN_KAISHI;

    // // test junk
    // displayFullDeck(&deck, 0, 0);
}

void phaseStartTurn()
{
    // Reset MP and Shields
    player.mpCur = player.mpMax;
    displayMP();
    player.shieldCount = 0U;
    displayShields();

    // Discard old hand
    if (hand.cardCount != 0U)
    {
        for (i = 0U; i != hand.cardCount;)
        {
            tempCardPtr = removeCardFromHand(&hand, i);
            discardCard(&deck, tempCardPtr->id);
        }
    }

    // Draw new hand
    UINT8 c = 0U;
    for (; c != 4U; c++)
    {
        // Shuffle discard pile into deck if needed
        if (deck.cardCount == 0U)
        {
            shuffleDeck(&deck, 64U, TRUE);
            for (i = 0; i != hand.cardCount; ++i)
            {
                deck.cardIds[deck.cardCount + i] = hand.cards[i]->id;
            }
        }
        tempCardPtr = drawCard(&deck);
        addCardToHand(&hand, tempCardPtr);
    }

    // Show hand
    displayHand(&hand, xAnchorHand, yAnchorHand);

    // Reset cursor location
    m = 0U;  // using m for cursor location
    displayCursor(m);

    // Reset MP to max, and update shown value
    substate = CARD_SELECT;
}

void phaseSelectCard()
{
    // Player inputs
    if (curJoypad & J_RIGHT && !(prevJoypad & J_RIGHT))
    {
        if (++m == hand.cardCount)
            m = 0U;
        displayCursor(m);
        // playMoveSfx();

        // Update card description as selected card changes
    }
    else if (curJoypad & J_LEFT && !(prevJoypad & J_LEFT))
    {
        if (m-- == 0U)
            m = hand.cardCount - 1U;
        displayCursor(m);
        // playMoveSfx();

        // Update card description as selected card changes
    }
    else if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        if (player.mpCur >= hand.cards[m]->mpCost)
        {
            player.mpCur -= hand.cards[m]->mpCost;
            displayMP();
            animTick = 0U;
            substate = USE_CARD;
            move_sprite(0U, 0U, 0U);
        }
        // TODO
        // else
        // {
        //     // Play buzzer sfx or something
        // }
    }
}

void phaseUseCard()
{
    // Remove card from hand and discard it
    tempCardPtr = removeCardFromHand(&hand, m);
    discardCard(&deck, tempCardPtr->id);

    // Redraw hand
    displayHand(&hand, xAnchorHand, yAnchorHand);

    // If attack card
    if (tempCardPtr->typeId == CT_ATTACK)
    {
        // Run damage calcs on target
        k = tempCardPtr->pointVal + player.atk;
        enemy.hpCur -= k;

        // Set curAnim to ANIM_ATTACK
        curAnim = ANIM_ATTACK;
    }
    else if (tempCardPtr->typeId == CT_SHIELD)
    {
        k = tempCardPtr->pointVal + player.def;
        player.shieldCount += k;
        displayShields();
    }
    else if (tempCardPtr->typeId == CT_HEAL)
    {
        player.hpCur += tempCardPtr->pointVal;
        if (player.hpCur > player.hpMax)
        {
            player.hpCur = player.hpMax;
        }
        displayHP();
    }

    // Goto PLAYER_ANIM
    substate = PLAYER_ANIM;
}

void phaseAnimatePlayerMove()
{
    if (animTick != maxAnimTick)
    {
        switch (curAnim)
        {
            case ANIM_ATTACK:  // If ANIM_ENEMY_BLINK, blink target
                if ((animTick >> 2U) % 2U == 0U)
                    set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, blankEnemyMap);
                else
                    set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, enemyMap);
                break;
            case ANIM_HEAL:  // If ANIM_HEAL, show heart popup
                // TODO: display heal anim
                // TODO: display number popup anim
                break;
            case ANIM_SHIELD:  // If ANIM_SHIELD, show shield popup
                // TODO: display shield anim
                // TODO: display number popup anim
                break;
        }
        ++animTick;
    }
    else
    {
        switch (curAnim)
        {
            case ANIM_ATTACK:  // If ANIM_ENEMY_BLINK, blink target
                // If dead, undraw
                if (enemy.hpCur == 0)
                {
                    set_bkg_tiles(8U, 4U, 4U, 4U, blankEnemyMap);
                    // TODO: play sfx
                }
                break;
            case ANIM_HEAL:  // If ANIM_HEAL, redraw hp
                displayHP();
                break;
            case ANIM_SHIELD:  // If ANIM_SHIELD, redraw shields
                displayShields();
                break;
        }
        // Goto WIN_CHECK
        substate = WIN_CHECK;
    }
}

void phaseEnemyTurn()
{
    // Selects random move based on enemy's movepool
    // TODO: This ^
    curAnim = ANIM_ENEMY_ATTACK;
    player.hpCur -= enemy.atk;

    // Goto ENEMY_ANIM
    substate = ENEMY_ANIM;
    animTick = 0U;
}

void phaseAnimateEnemyMove()
{
    if (animTick != maxAnimTick)
    {
        switch (curAnim)
        {
            case ANIM_ENEMY_ATTACK:
                switch (animTick)
                {
                    // Magic numbers because case expressions must be constants. The forumla is 1/4s of maxAnimTick.
                    case 0U:
                        scroll_bkg(1, 0);
                        break;
                    case 4U:
                        scroll_bkg(-2, 0);
                        break;
                    case 8U:
                        scroll_bkg(0, 1);
                        break;
                    case 12U:
                        scroll_bkg(0, -2);
                        break;
                }
                // TODO: popup damage number
                // TODO: sfx
                break;
            case ANIM_ENEMY_HEAL:
                // If ANIM_ENEMY_HEAL, show heart popup
                // TODO: This ^ and sfx
                break;
            case ANIM_ENEMY_SHIELD:
                // If ANIM_ENEMY_SHIELD, show shield popup
                // TODO: This ^ and sfx
                break;
        }
        // Increment animTick
        ++animTick;
    }
    else
    {
        switch (curAnim)
        {
            case ANIM_ENEMY_ATTACK:
                move_bkg(0, 0);
                displayHP();
                break;
            case ANIM_ENEMY_HEAL:
                // If ANIM_ENEMY_HEAL, show heart popup
                // TODO: This ^ and sfx
                break;
            case ANIM_ENEMY_SHIELD:
                // If ANIM_ENEMY_SHIELD, show shield popup
                // TODO: This ^ and sfx
                // displayEnemyShields();
                break;
        }
        // Goto LOSE_CHECK
        substate = LOSE_CHECK;
    }
}

void phaseWinCheck()
{
    // If enemy is dead
    if (enemy.hpCur == 0U)
    {
        // Queue win message

        // Goto SHOW_MESSAGES
        substate = SHOW_MESSAGES;
    }
    else
    {
        // Return to CARD_SELECT if more cards can be played
        // Else goto ENEMY_TURN
        substate = ENEMY_TURN;

        for (i = 0U; i != hand.cardCount; ++i)
        {
            if (hand.cards[i]->mpCost <= player.mpCur)
            {
                substate = CARD_SELECT;
                // Reset cursor location
                m = 0U;
                displayCursor(m);
            }
        }
    }
}

void phaseLoseCheck()
{
    // If player is dead
    if (player.hpCur == 0U)
    {
        // Queue lose message
        substate = TURN_KAISHI;
    }
    else
    {
        // Goto SHOW_MESSAGES
        substate = TURN_KAISHI;
    }
}

void phaseShowMessages()
{
    // If messageQueueCount != 0
        // If messageShown == TRUE
            // Poll inputs
            // A pops message from queue, decrements messageQueueCount
            // Set messageShown to FALSE
            // If messageType == MSG_WIN
                // Goto CALC_SPOILS
            // Else goto BATTLE_END
        // Else if messageShown == FALSE
            // Draw message to screen
            // Decrement messageQueueCount
            // Set messageShown to TRUE
}

void phaseCalcSpoils()
{
    // Queue spoils message
    // Goto SHOW_MESSAGES
}

void phaseEndBattle()
{
    // If win, end battle
    // If lose, goto title screen
}


void queueMessage(UINT8 messageType, UINT8 value)
{
    m = messageType;
    n = value;
    // Push message of messageType with value to messageQueue
    // Increment messageQueueCount
}


/******************************** DISPLAY METHODS ********************************/
void displayCursor(UINT8 xindex)
{
    // The coords are magic numbers. Fight me.
    move_sprite(0U, 60U + (xindex << 4U), 100U);
}

void displayCard(CardObject* card, UINT8 x, UINT8 y)
{
    switch (card->faceId)
    {
        case SHURIKEN:
            set_bkg_tiles(x, y, 2U, 3U, card1Map);
            break;
        case KATANA:
            set_bkg_tiles(x, y, 2U, 3U, card2Map);
            break;
        case HASAMI:
            set_bkg_tiles(x, y, 2U, 3U, card3Map);
            break;
        case HIKOUKI:
            set_bkg_tiles(x, y, 2U, 3U, card4Map);
            break;
        case SHATSU:
            set_bkg_tiles(x, y, 2U, 3U, card5Map);
            break;
        case KABUTO:
            set_bkg_tiles(x, y, 2U, 3U, card6Map);
            break;
        case HAATO:
            set_bkg_tiles(x, y, 2U, 3U, card7Map);
            break;
        default:
            set_bkg_tiles(x, y, 2U, 3U, cardBackMap);
            set_bkg_tile_xy(x, y, card->faceId);
            break;
    }
}

void displayHand(HandObject* hand, UINT8 x, UINT8 y)
{
    for (i = 0U; i != hand->cardCount; ++i)
    {
        displayCard(hand->cards[i], i*2U + x, y);
    }
    for (; i != 4U; ++i)
    {
        set_bkg_tiles(i*2U + x, y, 2U, 3U, cardEmptyMap);
    }
}

// void displayDeck(DeckObject* deck, UINT8 x, UINT8 y)
// {
//     if (deck->cardCount != 0U && deck->cardCount != 1U)
//         set_bkg_tiles(x, y, 2U, 3U, cardBackMap);
//     else
//         set_bkg_tiles(x, y, 2U, 3U, cardEmptyMap);
// }

// This is meant for testing purposes only
void displayFullDeck(DeckObject* deck, UINT8 x, UINT8 y)
{
    for (i = 0U; i != deck->cardCount; i++)
    {
        displayCard(&deck->orderedCards[deck->cardIds[i]], (i*2U)%20U + x, y + (i/10U * 3U));
    }
}

void displayHP()
{
    if (player.hpCur/10U != 0)
        set_bkg_tile_xy(xAnchorHP, yAnchorHP, player.hpCur/10U);
    else
        set_bkg_tile_xy(xAnchorHP, yAnchorHP, 0xFFU);
    set_bkg_tile_xy(xAnchorHP+1, yAnchorHP, player.hpCur%10U);
    set_bkg_tile_xy(xAnchorHP+2, yAnchorHP, 0x28U);

    set_bkg_tile_xy(xAnchorHP, yAnchorHP+1, 0x27U);
    set_bkg_tile_xy(xAnchorHP+1, yAnchorHP+1, player.hpMax/10U);
    set_bkg_tile_xy(xAnchorHP+2, yAnchorHP+1, player.hpMax%10U);
}

void displayMP()
{
    set_bkg_tile_xy(xAnchorMP, yAnchorMP, player.mpCur%10U);
    set_bkg_tile_xy(xAnchorMP+1, yAnchorMP, 0x2AU);
}

void displayShields()
{
    if (player.shieldCount/10U != 0)
        set_bkg_tile_xy(xAnchorShield, yAnchorShield, player.shieldCount/10U);
    else
        set_bkg_tile_xy(xAnchorShield, yAnchorShield, 0xFFU);
    set_bkg_tile_xy(xAnchorShield+1, yAnchorShield, player.shieldCount%10U);
    set_bkg_tile_xy(xAnchorShield+2, yAnchorShield, 0x29U);
}


// /******************************** HELPER METHODS ********************************/
// void playNumCard(CardObject* card, UINT8 x, UINT8 y, UINT8 player)
// {
//     if (player == P1)
//     {
//         addCardToStack(&stackP1, card);
//         displayStack(&stackP1, x, y, player);
//     }
//     else
//     {
//         addCardToStack(&stackCPU, card);
//         displayStack(&stackCPU, x, y, player);
//     }

//     // update score gfx
//     displayScore(player);
// }
