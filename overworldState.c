#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "common.h"
#include "enums.h"
#include "fade.h"

// #include "CardObject.h"
// #include "DeckObject.c"
#include "EnemyObject.h"
// #include "HandObject.c"
#include "PlayerObject.h"
#include "sprites/player.h"

// #include "maps/textWindowMap.c"
// #include "maps/blankTileMap.c"
// #include "maps/cardMaps.c"
// #include "maps/enemyMap.c"
// #include "maps/cardDescStrings.c"
// // #include "maps/scoreNumMaps.c"

#define PLAYER_SPR_NUM_START 0U
#define PLAYER_TILE_NUM_START 0U

// extern const unsigned char borderTiles[];
// extern const unsigned char cardTiles[];
// extern const unsigned char cursorTiles[];
// extern const unsigned char emptyTiles[];
// extern const unsigned char enemyHorseTiles[];
// extern const unsigned char fontTiles[];
// // extern const unsigned char scorenumTiles[];

// const UINT8 borderTileIndex = 0x30;
// const UINT8 cardsTileIndex  = 0x40;
// const UINT8 enemyTileIndex  = 0xB0;
// // const UINT8 scoreNumsTileIndex = 0xB0;

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

// CardObject* tempCardPtr;
// DeckObject deck;
// EnemyObject enemy;
// HandObject hand;
extern PlayerObject player;
extern UINT8 levelId;

UINT8 playerX = 80U;
UINT8 playerY = 88U;
UINT8 playerstate;
UINT8 playerDir = 0U;

const UINT8 PLAYER_X_LEFT   = 16U;  // 8 offset due to GB specs, 8 offset due to metatile centering
const UINT8 PLAYER_X_CENTER = 80U;
const UINT8 PLAYER_X_RIGHT  = 144U;
const UINT8 PLAYER_Y_UP     = 24U;
const UINT8 PLAYER_Y_CENTER = 88U;
const UINT8 PLAYER_Y_DOWN   = 152U;
UINT8 camera_max_x          = 9U * 16U;
UINT8 camera_max_y          = 9U * 16U;
#define STARTPOS 4U
#define STARTCAM 0U

// current and new positions of the camera in pixels
WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
// redraw flag, indicates that camera position was changed
UBYTE redraw;

extern UINT8 animTick;
UINT8 animFrame = 0U;
// const UINT8 maxAnimTick = 16U;
// ANIMTYPE curAnim = ANIM_ENEMY_ATTACK;

// const unsigned char blankEnemyMap[16U] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

// /* SUBSTATE METHODS */
void phaseInitOverworld();
void phaseInitMap();
void phasePlayerInputs();
void phasePlayerMove();
void phaseCheckSquare();
void phasePause();

// /* HELPER METHODS */
void checkUnderfootTile();
// void queueMessage(UINT8, UINT8);

// /* DISPLAY METHODS */
void draw_new_bkg();
// void drawBkgTile(UINT8, UINT8, TileObject*);


void overworldStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case OW_INIT_OW:
            phaseInitOverworld();
            break;
        case OW_INIT_MAP:
            phaseInitMap();
            break;
        // case OW_PLAYER_INPUTS:
        //     phasePlayerInputs();
        //     break;
        // case OW_PLAYER_MOVE:
        //     phasePlayerMove();
        //     break;
        // case OW_CHECK_SQUARE:
        //     phaseCheckSquare();
        //     break;
        // case OW_PAUSE:
        //     phasePause();
        //     break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = 0U;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
void phaseInitOverworld()
{

}

void phaseInitMap()
{
    // Check levelId, pull appropriate level
    // Check player coords/dir, draw player appropriately
    // Reset camera
    // 
}

void phasePlayerInputs()
{
    // Player movements and inputs
    if (playerstate == WALKING)
    {
        if (playerDir == N)
        {
            if (camera_y == 0U || playerY != PLAYER_Y_CENTER)
            {
                playerY -= 4U;
                if ((playerY+8U) % 16U == 0U)  // +8 because of the annoying metatiles center + 16 vert offset for sprites
                    checkUnderfootTile();
            }
            else
            {
                camera_y -= 4U;
                if (camera_y % 16U == 0U)
                    checkUnderfootTile();
            }
        }
        else if (playerDir == S)
        {
            if (camera_y == camera_max_y || playerY != PLAYER_Y_CENTER)
            {
                playerY += 4U;
                if ((playerY-8U) % 16U == 0U)
                    checkUnderfootTile();
            }
            else
            {
                camera_y += 4U;
                if (camera_y % 16U == 0U)
                    checkUnderfootTile();
            }
        }
        else if (playerDir == W)
        {
            if (camera_x == 0U || playerX != PLAYER_X_CENTER)
            {
                playerX -= 4U;
                if (playerX % 16U == 0U)
                    checkUnderfootTile();
            }
            else
            {
                camera_x -= 4U;
                if (camera_x % 16U == 0U)
                    checkUnderfootTile();
            }
        }
        else if (playerDir == E)
        {
            if (camera_x == camera_max_x || playerX != PLAYER_X_CENTER)
            {
                playerX += 4U;
                if (playerX % 16U == 0U)
                    checkUnderfootTile();
            }
            else
            {
                camera_x += 4U;
                if (camera_x % 16U == 0U)
                    checkUnderfootTile();
            }
        }
        SCX_REG = camera_x; SCY_REG = camera_y; 
    }
    else
    {
        // Uncover tile
        if (curJoypad & J_A && !(prevJoypad & J_A))
        {
            // Check for NPC in front of player
            // Interact with NPC if present
        }
        // Cardinal movement
        else if ((curJoypad == J_UP) && (prevJoypad == J_UP))
        {
            playerDir = N;
            // Move sprite, not camera
            if (camera_y == 0U || playerY > PLAYER_Y_CENTER)
            {
                if (playerY != PLAYER_Y_UP)  // Bomb/covered check goes here
                {
                    playerstate = WALKING;
                }
            }
            else  // Move camera
            {
                new_camera_y -= 16;
                playerstate = WALKING;
                redraw = TRUE;
            }
        }
        else if ((curJoypad == J_DOWN) && (prevJoypad == J_DOWN))
        {
            playerDir = S;
            // Move sprite, not camera
            if (camera_y == camera_max_y || playerY < PLAYER_Y_CENTER)
            {
                if (playerY != PLAYER_Y_DOWN)  // Bomb/covered check goes here
                {
                    playerstate = WALKING;
                }
            }
            else  // Move camera
            {
                new_camera_y += 16;
                playerstate = WALKING;
                redraw = TRUE;
            }
        } 
        else if ((curJoypad == J_LEFT) && (prevJoypad == J_LEFT))
        {
            playerDir = W;
            // Move sprite, not camera
            if (camera_x == 0U || playerX > PLAYER_X_CENTER)
            {
                if (playerX != PLAYER_X_LEFT)  // Bomb/covered check goes here
                {
                    playerstate = WALKING;
                }
            }
            else  // Move camera
            {
                new_camera_x -= 16;
                playerstate = WALKING;
                redraw = TRUE;
            }
        }
        else if ((curJoypad == J_RIGHT) && (prevJoypad == J_RIGHT))
        {
            playerDir = E;
            // Move sprite, not camera
            if (camera_x == camera_max_x || playerX < PLAYER_X_CENTER)
            {
                if (playerX != PLAYER_X_RIGHT)  // Bomb/covered check goes here
                {
                    playerstate = WALKING;
                }
            }
            else  // Move camera
            {
                new_camera_x += 16;
                playerstate = WALKING;
                redraw = TRUE;
            }
        }
    } 

    ++animTick;
    animFrame = animTick % 32U;
    animFrame /= 8U;
    if (animFrame == 3U)
        animFrame = 1U;
    if (curJoypad == 0U && playerstate == IDLE)
        animFrame = 1U;
    move_metasprite(player_metasprites[playerDir*3 + animFrame], PLAYER_TILE_NUM_START, PLAYER_SPR_NUM_START, playerX, playerY);

    if (redraw && playerstate == WALKING)
    {
        wait_vbl_done();
        // draw_new_bkg();
        redraw = FALSE;
    }
    else
        wait_vbl_done();

}

void phasePlayerMove();
void phaseCheckSquare();
void phasePause();


/******************************** HELPER METHODS *********************************/
void checkUnderfootTile()
{
    playerstate = IDLE;

    // tilePtr = &playGrid[(map_pos_y>>1U) + ((playerY-16U)>>4U)][(map_pos_x>>1U) + ((playerX-8U)>>4U)];
    // if (tilePtr->face == KEY)
    // {
    //     ++heldKeys;
    //     updateUIKeys();
    //     tilePtr->face = tilePtr->numAdjacent;
    //     drawBkgTile(((map_pos_x) + ((playerX-16U)>>3U))%32U, ((map_pos_y) + ((playerY-24U)>>3U))%32U, tilePtr);
    // }
    // else if (tilePtr->face == CHEST_C)
    // {
    //     if (heldKeys != 0U)
    //     {
    //         --heldKeys;
    //         updateUIKeys();
    //         tilePtr->face = tilePtr->numAdjacent;
    //         drawBkgTile(((map_pos_x) + ((playerX-16U)>>3U))%32U, ((map_pos_y) + ((playerY-24U)>>3U))%32U, tilePtr);
    //     }
    // }
    // else if (tilePtr->face == STAIRS)
    // {
    //     fadeout();
    //     initFloor();
    // }
}


/******************************** DISPLAY METHODS ********************************/
// void draw_new_bkg() {
//     // Vertical
//     new_map_pos_y = (BYTE)(new_camera_y >> 3u);
//     if (map_pos_y != new_map_pos_y) { 
//         if (new_camera_y < camera_y) 
//         {
//             for (k = 0U; k != 10U; ++k)
//             {
//                 drawBkgTile((map_pos_x+(k<<1U))%32U, new_map_pos_y%32U, &playGrid[new_map_pos_y>>1U][(map_pos_x>>1U)+k]);
//             }
//         } else
//         {
//             for (UINT8 k = 0U; k != 10U; ++k)
//             {
//                 drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, &playGrid[((new_map_pos_y+16U)>>1U)][(map_pos_x>>1U)+k]);
//             }
//         }
//         map_pos_y = new_map_pos_y; 
//     }
//     // Horizontal 
//     new_map_pos_x = (BYTE)(new_camera_x >> 3U);
//     if (map_pos_x != new_map_pos_x) {
//         if (new_camera_x < camera_x) 
//         {
//             for (UINT8 k = 0U; k != 9U; ++k)
//             {
//                 drawBkgTile(new_map_pos_x%32U, (map_pos_y+(k<<1U))%32U, &playGrid[(map_pos_y>>1U)+k][new_map_pos_x>>1U]);
//             }
//         } else 
//         {
//             for (UINT8 k = 0U; k != 9U; ++k)
//             {
//                 drawBkgTile((new_map_pos_x + 18U)%32U, (map_pos_y+(k<<1U))%32U, &playGrid[(map_pos_y>>1U)+k][(new_map_pos_x+18U)>>1U]);
//             }
//         }
//         map_pos_x = new_map_pos_x;
//     }
// }

// void drawBkgTile(UINT8 x, UINT8 y, TileObject *tile)
// {
//     set_bkg_tiles(x, y, 2U, 2U, wallMetaTiles[tile->face]);
// }
