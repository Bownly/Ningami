#include <gb/gb.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"

#include "../database/CardData.h"

#include "../maps/textWindowMap.h"
#include "../maps/blankTileMap.c"
#include "../maps/cardMaps.h"
#include "../maps/enemyMap.c"
#include "../maps/cardDescStrings.h"
#include "../maps/battleAnimMaps.h"

#include "../objects/CardObject.h"
#include "../objects/DeckObject.h"
#include "../objects/EnemyObject.h"
#include "../objects/HandObject.c"
#include "../objects/PlayerObject.h"

#define stringWonA "   YOU DEFEATED  "
#define stringWonB "  WON SOME PAPER "

extern const unsigned char borderTiles[];
extern const unsigned char cardTiles[];
extern const unsigned char cursorTiles[];
extern const unsigned char emptyTiles[];
extern const unsigned char enemyDogTiles[];
extern const unsigned char enemyHorseTiles[];
extern const unsigned char enemyKitsuneTiles[];
extern const unsigned char enemyTanukiTiles[];
extern const unsigned char fontTiles[];
extern const unsigned char glintTiles[];
extern const unsigned char healAnimTiles[];
extern const unsigned char manaAnimTiles[];
extern const unsigned char shieldAnimTiles[];

const UINT8 enemyTileIndex  = 0xE0;
const UINT8 battleAnimTileIndex  = 0xF0;
const UINT8 glintTileIndex  = 0xFC;

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
extern UINT8 oldGamestate;
extern UINT8 substate;
extern UINT8 oldSubstate;

UINT8 tempCardId;
CardObject* tempCardPtr;
extern DeckObject deck;
HandObject hand;
EnemyObject enemy;
extern PlayerObject player;
extern UINT8 enemyId;
extern const EnemyObject enemyDex[];

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
const UINT8 xAnchorEnemyHP = 2U;
const UINT8 yAnchorEnemyHP = 5U;
const UINT8 xAnchorEnemyAtk = 15U;
const UINT8 yAnchorEnemyAtk = 5U;
const UINT8 xAnchorEnemyShield = 15U;
const UINT8 yAnchorEnemyShield = 6U;
// const UINT8 xAnchorPaperWinnings = 6U;
// const UINT8 yAnchorPaperWinnings = 6U;

extern UINT8 animFrame;
extern UINT8 animTick;
const UINT8 maxAnimTick = 16U;
ANIMTYPE curAnim = ANIM_ENEMY_ATTACK;

const unsigned char blankEnemyMap[16U] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };
const unsigned char blankTile8x8[16U]  = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

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
void phaseWinLoop();

/* HELPER METHODS */

/* DISPLAY METHODS */
void displayCursor(UINT8);
void displayCard(UINT8, UINT8, UINT8);
void displayCardDesc();
void displayHand(HandObject*, UINT8, UINT8);
void displayHP();
void displayMP();
void displayPaperEarnings();
void displayShields();
void displayEnemyHP();
void displayEnemyAtk();
void displayEnemyShields();
void hideGlintSprites();


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
        case BATTLE_END:
            phaseWinLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = 0U;
            break;
    }
    prevJoypad = curJoypad;
}

/******************************** SUBSTATE METHODS *******************************/
void phaseOpunZaGeimu()
{
    // Initialize variables and graphics
    animTick = 0U;
    animFrame = 0U;
    setBlankBg();
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    // set_bkg_data(scoreNumsTileIndex, 20U, scorenumTiles);
    set_bkg_data(glintTileIndex, 2U, glintTiles);

    set_sprite_tile(1U, glintTileIndex);
    set_sprite_tile(2U, glintTileIndex+1U);
    set_sprite_prop(1U, get_sprite_prop(1U) & ~S_FLIPX);
    set_sprite_prop(1U, get_sprite_prop(1U) & ~S_FLIPY);
    set_sprite_prop(2U, get_sprite_prop(2U) & ~S_FLIPX);
    set_sprite_prop(2U, get_sprite_prop(2U) & ~S_FLIPY);

    move_bkg(0, 0);
    set_bkg_tiles(0U, 18U, 16U, 1U, blankEnemyMap);
    
    // Initialize enemy data
    // TODO make this variable based on different enemy types
    switch (enemyId)
    {
        case ENEMY_INU:
            set_bkg_data(enemyTileIndex, 16U, enemyDogTiles);
            break;
        case ENEMY_KITSUNE:
            set_bkg_data(enemyTileIndex, 16U, enemyKitsuneTiles);
            break;
        case ENEMY_TANUKI:
            set_bkg_data(enemyTileIndex, 16U, enemyTanukiTiles);
            break;
        case ENEMY_TSURU:
            set_bkg_data(enemyTileIndex, 16U, enemyHorseTiles);
            break;
        default:
            set_bkg_data(enemyTileIndex, 16U, enemyDogTiles);
            break;
    }
    enemy = enemyDex[enemyId];

    xAnchorHand = 6U;

    initrand(DIV_REG);
    // Initialize hand; shuffle deck
    shuffleDeck(&deck, 64U, TRUE);
    initializeHand(&hand);

    // Show enemy on screen
    set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, enemyMap);

    // Show player and enemy stats on screen
    displayHP();
    displayMP();
    displayShields();
    displayEnemyHP();
    displayEnemyAtk();
    displayEnemyShields();

    // Draw the dialog box
    set_bkg_tiles(0U, 14U, 20U, 4U, textWindowMap);

    // Set substate
    substate = TURN_KAISHI;

    fadein();

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
            tempCardId = removeCardFromHand(&hand, i);
            discardCard(&deck, tempCardId);
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
            // Ensure the IDs in the hand return to the deck
            for (i = 0U; i != hand.cardCount; ++i)
            {
                deck.cardIds[deck.cardCount + i] = hand.cardIds[i];
            }
        }
        tempCardId = drawCard(&deck);
        addCardToHand(&hand, tempCardId);
    }

    // Show hand
    displayHand(&hand, xAnchorHand, yAnchorHand);

    // Reset cursor location
    m = 0U;  // using m for cursor location
    displayCursor(m);

    // Update card description of default selected card
    displayCardDesc();

    // Reset MP to max, and update shown value
    animTick = 0U;
    substate = CARD_SELECT;
}

void phaseSelectCard()
{
    ++animTick;
    animFrame = animTick / 8U % 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    set_sprite_tile(0U, animFrame);
    
    // Player inputs
    if (curJoypad & J_START && !(prevJoypad & J_START))
    {
        oldSubstate = substate;
        oldGamestate = gamestate;
        gamestate = STATE_PAUSEMENU;
        substate = PM_INIT;
    }
    else if (curJoypad & J_LEFT && !(prevJoypad & J_LEFT))
    {
        if (m-- == 0U)
            m = hand.cardCount - 1U;
        // TODO: playMoveSfx();

        // Update card description as selected card changes
        displayCardDesc();
    }
    else if (curJoypad & J_RIGHT && !(prevJoypad & J_RIGHT))
    {
        if (++m == hand.cardCount)
            m = 0U;
        // TODO: playMoveSfx();

        // Update card description as selected card changes
        displayCardDesc();
    }
    else if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        tempCardId = deck.orderedCards[hand.cardIds[m]];
        if (player.mpCur >= cardDex[tempCardId].mpCost)
        {
            player.mpCur -= cardDex[tempCardId].mpCost;
            displayMP();
            animTick = 0U;
            substate = USE_CARD;
            move_sprite(0U, 0U, 0U);
        }
        // TODO sfx
        // else
        // {
        //     // Play buzzer sfx or something
        // }
    }
    displayCursor(m);
}

void phaseUseCard()
{
    // Hide cursor
    move_sprite(0U, 0U, 0U);

    // Remove card from hand and discard it
    tempCardId = removeCardFromHand(&hand, m);
    discardCard(&deck, tempCardId);

    // Redraw hand
    displayHand(&hand, xAnchorHand, yAnchorHand);

    // Update card description to blank
    printLine(1U, 15U, cardDescStrings[20], FALSE);
    printLine(1U, 16U, cardDescStrings[20], FALSE);

    // Convert tempCardId from an index for deck position to cardDex index 
    tempCardId = deck.orderedCards[tempCardId];

    // If attack card
    if (cardDex[tempCardId].typeId == CT_ATTACK || cardDex[tempCardId].typeId == CT_ATKDEF)
    {
        // Run damage calcs on target
        k = cardDex[tempCardId].pointVal + player.atk - enemy.def;
        if (k < enemy.hpCur)
            enemy.hpCur -= k;
        else
            enemy.hpCur = 0;
        displayEnemyHP();
    }
    if (cardDex[tempCardId].typeId == CT_SHIELD || cardDex[tempCardId].typeId == CT_ATKDEF)
    {
        k = cardDex[tempCardId].pointVal + player.def;
        player.shieldCount += k;
    }
    if (cardDex[tempCardId].typeId == CT_HEAL)
    {
        player.hpCur += cardDex[tempCardId].pointVal;
        if (player.hpCur > player.hpMax)
        {
            player.hpCur = player.hpMax;
        }
        displayHP();
    }
    else if (cardDex[tempCardId].typeId == CT_MANA)
    {
        player.mpCur += cardDex[tempCardId].pointVal;
        displayMP();
    }

    curAnim = cardDex[tempCardId].typeId;

    // Goto PLAYER_ANIM
    substate = PLAYER_ANIM;
}

void phaseAnimatePlayerMove()
{
    if (animTick == 0U)
    {
        // Load appropriate graphics
        if (curAnim == CT_ATTACK)
        {
            for (k = 0; k != 12U; ++k)
            {
                set_bkg_data(battleAnimTileIndex + k, 1U, blankTile8x8);
            }
        }
        if (curAnim == CT_HEAL)
        {
            set_bkg_data(battleAnimTileIndex, 12U, healAnimTiles);
        }
        if (curAnim == CT_SHIELD || curAnim == CT_ATKDEF)
        {
            set_bkg_data(battleAnimTileIndex, 12U, shieldAnimTiles);
        }
        if (curAnim == CT_MANA)
        {
            set_bkg_data(battleAnimTileIndex, 12U, manaAnimTiles);
        }
    }

    if (animTick != maxAnimTick)
    {
        if (curAnim == CT_ATTACK || curAnim == CT_ATKDEF)  // If attacking, blink target
        {
            if ((animTick >> 2U) % 2U == 0U)
                set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, blankEnemyMap);
            else
                set_bkg_tiles(xAnchorEnemy, yAnchorEnemy, 4U, 4U, enemyMap);
        }

        if (curAnim != CT_ATTACK)
        {
            if (animTick == 0U)
            {
                set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, battleAnimMaps[0]);
            }
            else if (animTick>>1U == 2U)
                set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, battleAnimMaps[1]);
            else if (animTick == 6U)
                set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, battleAnimMaps[2]);
            else if (animTick == 7U)
            {
                move_sprite(1U, 72U, 80U);
                move_sprite(2U, 72U, 88U);
            }
            else
            {
                scroll_sprite(1U, 2U, 0U);
                scroll_sprite(2U, 2U, 0U);
            }
        }
        ++animTick;
    }
    else  // Final frame
    {
        if (curAnim == CT_ATTACK || curAnim == CT_ATKDEF)
        {
            // If dead, undraw
            if (enemy.hpCur == 0)
            {
                set_bkg_tiles(8U, 4U, 4U, 4U, blankEnemyMap);
                // TODO: play sfx
            }
        }
        if (curAnim == CT_HEAL)
        {
            set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, blankEnemyMap);
            hideGlintSprites();
            displayHP();
        }
        if (curAnim == CT_SHIELD || curAnim == CT_ATKDEF)
        {
            set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, blankEnemyMap);
            hideGlintSprites();
            displayShields();
        }
        if (curAnim == CT_MANA || curAnim == CT_MANA)
        {
            set_bkg_tiles(xAnchorEnemy+1U, yAnchorEnemy+4U, 2U, 2U, blankEnemyMap);
            hideGlintSprites();
            displayShields();
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

    if (player.shieldCount >= enemy.atk)
    {
        player.shieldCount -= enemy.atk;
        k = 0U;
    }
    else
    {
        k = enemy.atk - player.shieldCount;
    }
    player.hpCur -= k;

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
            // case ANIM_ENEMY_HEAL:
            //     // If ANIM_ENEMY_HEAL, show heart popup
            //     // TODO: This ^ and sfx
            //     break;
            // case ANIM_ENEMY_SHIELD:
            //     // If ANIM_ENEMY_SHIELD, show shield popup
            //     // TODO: This ^ and sfx
            //     break;
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
                displayShields();
                break;
            // case ANIM_ENEMY_HEAL:
            //     // If ANIM_ENEMY_HEAL, show heart popup
            //     // TODO: This ^ and sfx
            //     break;
            // case ANIM_ENEMY_SHIELD:
            //     // If ANIM_ENEMY_SHIELD, show shield popup
            //     // TODO: This ^ and sfx
            //     // displayEnemyShields();
            //     break;
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
        // Hide extra enemy stats and stuff
        set_bkg_tiles( 2U, 5U, 3U, 2U, blankEnemyMap);
        set_bkg_tiles(16U, 5U, 2U, 2U, blankEnemyMap);

        // Display win message
        printLine(1U,  4U, stringWonA, FALSE);
        printLine(1U, 15U, cardDescStrings[20U], FALSE);
        printLine(1U, 16U, cardDescStrings[20U], FALSE);
        printLine(1U,  6U, stringWonB, FALSE);

        // Calc and display paper winnings
        if (255U - enemyDex[enemyId].paperAmount <= player.paper)
            player.paper = 255U;
        else
            player.paper += enemyDex[enemyId].paperAmount;
        displayPaperEarnings();

        // Goto BATTLE_END
        substate = BATTLE_END;

        // Discard what's left of the hand
        if (hand.cardCount != 0U)
        {
            for (i = 0U; i != hand.cardCount;)
            {
                tempCardId = removeCardFromHand(&hand, i);
                discardCard(&deck, tempCardId);
            }
        }

    }
    else
    {
        // Return to CARD_SELECT if more cards can be played
        // Else goto ENEMY_TURN
        substate = ENEMY_TURN;

        for (i = 0U; i != hand.cardCount; ++i)
        {
            if (cardDex[deck.orderedCards[hand.cardIds[i]]].mpCost <= player.mpCur)
            {
                animTick = 0U;
                substate = CARD_SELECT;
                // Reset cursor location
                m = 0U;
                displayCursor(m);

                // Update card description of default selected card
                displayCardDesc();
            }
        }
    }
}

void phaseLoseCheck()
{
    // If player is dead
    if (player.hpCur == 0U)
    {
        gamestate = STATE_TITLE;
        substate = 0U;
    }
    else
    {
        // Goto SHOW_MESSAGES
        substate = TURN_KAISHI;
    }
}

void phaseWinLoop()
{
    if ((curJoypad & J_A && !(prevJoypad & J_A))
        || (curJoypad & J_B && !(prevJoypad & J_B)))
    {
        gamestate = STATE_OVERWORLD;
        substate = OW_INIT_OW;
        move_sprite(0U, 0U, 0U);
        fadeout();
    }
}


/******************************** HELPER METHODS ********************************/


/******************************** DISPLAY METHODS ********************************/
void displayCursor(UINT8 xindex)
{
    // The coords are magic numbers. Fight me.
    move_sprite(0U, 56U + (xindex << 4U), 96U);
}

void displayCard(UINT8 cardId, UINT8 x, UINT8 y)
{
    switch (cardId)
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
        case SHOUZOKU:
            set_bkg_tiles(x, y, 2U, 3U, card5Map);
            break;
        case KABUTO:
            set_bkg_tiles(x, y, 2U, 3U, card6Map);
            break;
        case HAATO:
            set_bkg_tiles(x, y, 2U, 3U, card7Map);
            break;
        case MAKIMONO:
            set_bkg_tiles(x, y, 2U, 3U, card8Map);
            break;
        case FUUSEN:
            set_bkg_tiles(x, y, 2U, 3U, card9Map);
            break;
        case ONIGIRI:
            set_bkg_tiles(x, y, 2U, 3U, card10Map);
            break;
        default:
            set_bkg_tiles(x, y, 2U, 3U, cardBackMap);
            set_bkg_tile_xy(x, y, cardId);
            break;
    }
}

void displayCardDesc()
{
    printLine(1U, 15U, cardDescStrings[deck.orderedCards[hand.cardIds[m]]<<1U], FALSE);
    printLine(1U, 16U, cardDescStrings[(deck.orderedCards[hand.cardIds[m]]<<1U)+1U], FALSE);
}

void displayHand(HandObject* hand, UINT8 x, UINT8 y)
{
    for (i = 0U; i != hand->cardCount; ++i)
    {
        displayCard(deck.orderedCards[hand->cardIds[i]], i*2U + x, y);
    }
    for (; i != 4U; ++i)
    {
        set_bkg_tiles(i*2U + x, y, 2U, 3U, cardEmptyMap);
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

void displayPaperEarnings()
{
    // Paper won
    // set_bkg_tile_xy(xAnchorEnemy, yAnchorEnemy, 0x27U);
    if (enemyDex[enemyId].paperAmount/10U != 0U)
        set_bkg_tile_xy(xAnchorEnemy+1U, yAnchorEnemy+3U, enemyDex[enemyId].paperAmount/10U %10U);
    set_bkg_tile_xy(xAnchorEnemy+2U, yAnchorEnemy+3U, enemyDex[enemyId].paperAmount%10U);
    set_bkg_tile_xy(xAnchorEnemy+3U, yAnchorEnemy+3U, 0x2DU);
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

void displayEnemyHP()
{
    if (enemy.hpCur/10U != 0)
        set_bkg_tile_xy(xAnchorHP, yAnchorEnemyHP, enemy.hpCur/10U);
    else
        set_bkg_tile_xy(xAnchorHP, yAnchorEnemyHP, 0xFFU);
    set_bkg_tile_xy(xAnchorHP+1, yAnchorEnemyHP, enemy.hpCur%10U);
    set_bkg_tile_xy(xAnchorHP+2, yAnchorEnemyHP, 0x28U);

    set_bkg_tile_xy(xAnchorHP, yAnchorEnemyHP+1, 0x27U);
    set_bkg_tile_xy(xAnchorHP+1, yAnchorEnemyHP+1, enemy.hpMax/10U);
    set_bkg_tile_xy(xAnchorHP+2, yAnchorEnemyHP+1, enemy.hpMax%10U);
}

void displayEnemyAtk()
{
    if (enemy.atk/10U != 0)
        set_bkg_tile_xy(xAnchorEnemyAtk, yAnchorEnemyAtk, enemy.atk/10U);
    else
        set_bkg_tile_xy(xAnchorEnemyAtk, yAnchorEnemyAtk, 0xFFU);
    set_bkg_tile_xy(xAnchorEnemyAtk+1, yAnchorEnemyAtk, enemy.atk%10U);
    set_bkg_tile_xy(xAnchorEnemyAtk+2, yAnchorEnemyAtk, 0x2CU);
}

void displayEnemyShields()
{
    if (enemy.shieldCount/10U != 0)
        set_bkg_tile_xy(xAnchorEnemyShield, yAnchorEnemyShield, enemy.shieldCount/10U);
    else
        set_bkg_tile_xy(xAnchorEnemyShield, yAnchorEnemyShield, 0xFFU);
    set_bkg_tile_xy(xAnchorEnemyShield+1, yAnchorEnemyShield, enemy.shieldCount%10U);
    set_bkg_tile_xy(xAnchorEnemyShield+2, yAnchorEnemyShield, 0x29U);
}

void hideGlintSprites()
{
    move_sprite(1U, 0U, 0U);
    move_sprite(2U, 0U, 0U);
}
