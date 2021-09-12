#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"
#include "../database/RoomData.h"
#include "../maps/room1Map.c"
#include "../maps/room2Map.c"
#include "../objects/EventObject.h"
#include "../objects/PlayerObject.h"
#include "../objects/TileObject.h"
#include "../sprites/player.h"

#define PLAYER_SPR_NUM_START 1U
#define PLAYER_TILE_NUM_START 3U

// extern const unsigned char borderTiles[];
// extern const unsigned char cardTiles[];
// extern const unsigned char cursorTiles[];
// extern const unsigned char emptyTiles[];
// extern const unsigned char fontTiles[];
extern const unsigned char forestMetaTiles[][4U];

// extern const EventObject room1Events[];

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
extern UINT8 oldGamestate;
extern UINT8 oldSubstate;

// CardObject* tempCardPtr;
// DeckObject deck;
// EnemyObject enemy;
// HandObject hand;
extern PlayerObject player;
extern UINT8 roomId;

UINT8 playerstate;
UINT8 playerDir = 0U;

TileObject playGrid[30U][30U];
TileObject* tilePtr;
const char * roomMapPtr;
const EventObject * roomEventsPtr;

UINT8 gridW = 20U;
UINT8 gridH = 18U;
UINT16 camera_max_x = 10U * 16U;
UINT16 camera_max_y = 9U * 16U;

const UINT8 PLAYER_X_LEFT   = 16U;  // 8 offset due to GB specs, 8 offset due to metatile centering
const UINT8 PLAYER_X_CENTER = 96U;
const UINT8 PLAYER_X_RIGHT  = 160U;
const UINT8 PLAYER_Y_UP     = 24U;
const UINT8 PLAYER_Y_CENTER = 88U;
const UINT8 PLAYER_Y_DOWN   = 152U;
#define STARTPOS 4U
#define STARTCAM 0U

// current and new positions of the camera in pixels
WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
// redraw flag, indicates that camera position was changed
UBYTE redraw;

extern UINT8 animTick;
extern UINT8 animFrame;
// const UINT8 maxAnimTick = 16U;
// ANIMTYPE curAnim = ANIM_ENEMY_ATTACK;

// const unsigned char blankEnemyMap[16U] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

/* SUBSTATE METHODS */
void phaseInitOverworld();
void phaseInitMap();
void phasePlayerInputs();
void phasePlayerMove();
void phaseCheckSquare();
void phasePause();

/* HELPER METHODS */
void loadRoom();
void checkUnderfootTile();

/* DISPLAY METHODS */
void draw_new_bkg();
void drawBkgTile(UINT8, UINT8, TileObject*);


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
        case OW_PLAYER_INPUTS:
            phasePlayerInputs();
            break;
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
    // Initialize graphics
    animTick = 0U;
    animFrame = 0U;
    setBlankBg();
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    HIDE_WIN;

    // Initiatlize window
    for (i = 0U; i != 2U; ++i)
    {
        for (j = 0U; j != 18U; ++j)
        {
            set_win_tile_xy(i, j, 0x32U);
        }
    }
    // Draw pause window data: deck, hp, mp, paper

    // set_bkg_data(0U, 40U, fontTiles);

    initrand(DIV_REG);
    SCX_REG = camera_x; SCY_REG = camera_y; 
    redraw = FALSE;

    substate = OW_INIT_MAP;
}

void phaseInitMap()
{
    // Check levelId, pull appropriate level
    loadRoom();
    // Check player coords/dir, draw player appropriately
    // Reset camera
    // 

    UINT16 c = 0U;
    for (j = 0U; j != gridH; j++)
    {
        for (i = 0U; i != gridW; i++)
        {
            playGrid[j][i].face = *(roomMapPtr +c);
            c++;
        }
    }

    // Draw grid
    for (i = 0U; i != 10U; i++)
    {
        for (j = 0U; j != 9U; j++)
        {
            drawBkgTile(i<<1U, j<<1U, &playGrid[j][i]);
        }
    }

    // Spawn player
    set_sprite_data(PLAYER_TILE_NUM_START, sizeof(player_data) >> 4U, player_data);

    substate = OW_PLAYER_INPUTS;

    fadein();
}

void phasePlayerInputs()
{
    // Player movements and inputs
    if (playerstate == WALKING)
    {
        if (playerDir == N)
        {
            if (camera_y == 0U || player.y != PLAYER_Y_CENTER)
            {
                player.y -= 4U;
                if ((player.y + 8U) % 16U == 0U)  // +8 because of the annoying metatiles center + 16 vert offset for sprites
                {
                    player.yTile--;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_y -= 4U;
                if (camera_y % 16U == 0U)
                {
                    player.yTile--;
                    checkUnderfootTile();
                }
            }
        }
        else if (playerDir == S)
        {
            if (camera_y == camera_max_y || player.y != PLAYER_Y_CENTER)
            {
                player.y += 4U;
                if ((player.y - 8U) % 16U == 0U)
                {
                    player.yTile++;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_y += 4U;
                if (camera_y % 16U == 0U)
                {
                    player.yTile++;
                    checkUnderfootTile();
                }
            }
        }
        else if (playerDir == W)
        {
            if (camera_x == 0U || player.x != PLAYER_X_CENTER)
            {
                player.x -= 4U;
                if (player.x % 16U == 0U)
                {
                    player.xTile--;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_x -= 4U;
                if (camera_x % 16U == 0U)
                {
                    player.xTile--;
                    checkUnderfootTile();
                }
            }
        }
        else if (playerDir == E)
        {
            if (camera_x == camera_max_x || player.x != PLAYER_X_CENTER)
            {
                player.x += 4U;
                if (player.x % 16U == 0U)
                {
                    player.xTile++;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_x += 4U;
                if (camera_x % 16U == 0U)
                {
                    player.xTile++;
                    checkUnderfootTile();
                }
            }
        }
        SCX_REG = camera_x; SCY_REG = camera_y; 
    }
    else
    {
        if (curJoypad & J_START && !(prevJoypad & J_START))
        {
            oldSubstate = substate;
            oldGamestate = gamestate;
            gamestate = STATE_PAUSEMENU;
            substate = PM_INIT;
            hide_metasprite(player_metasprites[playerDir*3 + animFrame], PLAYER_SPR_NUM_START);
            return;
        }
        else if (curJoypad & J_A && !(prevJoypad & J_A))
        {
            // Check for NPC in front of player
            // Interact with NPC if present
        }
        // Cardinal movement
        else if ((curJoypad == J_UP) && (prevJoypad == J_UP))
        {
            playerDir = N;
            // Move sprite, not camera
            if (camera_y == 0U || player.y > PLAYER_Y_CENTER)
            {
                if (player.y != PLAYER_Y_UP)  // Bomb/covered check goes here
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
            if (camera_y == camera_max_y || player.y < PLAYER_Y_CENTER)
            {
                if (player.y != PLAYER_Y_DOWN)  // Bomb/covered check goes here
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
            if (camera_x == 0U || player.x > PLAYER_X_CENTER)
            {
                if (player.x != PLAYER_X_LEFT)  // Bomb/covered check goes here
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
            if (camera_x == camera_max_x || player.x < PLAYER_X_CENTER)
            {
                if (player.x != PLAYER_X_RIGHT)  // Bomb/covered check goes here
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
    animFrame = animTick % 16U;
    animFrame /= 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    if (curJoypad == 0U && playerstate == IDLE)
        animFrame = 1U;
    move_metasprite(player_metasprites[playerDir*3 + animFrame], PLAYER_TILE_NUM_START, PLAYER_SPR_NUM_START, player.x, player.y);

    if (redraw && playerstate == WALKING)
    {
        wait_vbl_done();
        draw_new_bkg();
        redraw = FALSE;
    }
    else
        wait_vbl_done();

}

void phasePlayerMove();
void phaseCheckSquare();
void phasePause();


/******************************** HELPER METHODS *********************************/
void loadRoom()
{
    switch (roomId)
    {
        case 1U:
            roomMapPtr = room1Map;
            gridW = room1MapWidth;
            gridH = room1MapHeight;
            camera_max_x = (((room1MapWidth  - 20U) * 2U) + 20U) * 8U;
            camera_max_y = (((room1MapHeight - 18U) * 2U) + 18U) * 8U;
            roomEventsPtr = room1Events;
            break;
        case 2U:
            roomMapPtr = room2Map;
            gridW = room2MapWidth;
            gridH = room2MapHeight;
            camera_max_x = (((room2MapWidth  - 20U) * 2U) + 20U) * 8U;
            camera_max_y = (((room2MapHeight - 18U) * 2U) + 18U) * 8U;
            roomEventsPtr = room2Events;
            break;
        default:
            roomId = 1U;  // Eventually, I'll make a roomId = 0U default room. ...Maybe.
            loadRoom();
            break;
    }
}

void checkUnderfootTile()
{
    playerstate = IDLE;

    for (l = 0U; l != 2U; l++)
    {
        if (player.xTile == (roomEventsPtr+l)->x && player.yTile == (roomEventsPtr+l)->y)
        {
            set_bkg_tile_xy(5, 5, 0x28 + (roomEventsPtr+l)->value);
        }
    }
}


/******************************** DISPLAY METHODS ********************************/
void draw_new_bkg() {
    // Vertical
    new_map_pos_y = (BYTE)(new_camera_y >> 3u);
    if (map_pos_y != new_map_pos_y) { 
        if (new_camera_y < camera_y) 
        {
            for (k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, new_map_pos_y%32U, &playGrid[new_map_pos_y>>1U][(map_pos_x>>1U)+k]);
            }
        } else
        {
            for (UINT8 k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, &playGrid[((new_map_pos_y+16U)>>1U)][(map_pos_x>>1U)+k]);
            }
        }
        map_pos_y = new_map_pos_y; 
    }
    // Horizontal 
    new_map_pos_x = (BYTE)(new_camera_x >> 3U);
    if (map_pos_x != new_map_pos_x) {
        if (new_camera_x < camera_x) 
        {
            for (UINT8 k = 0U; k != 9U; ++k)
            {
                drawBkgTile(new_map_pos_x%32U, (map_pos_y+(k<<1U))%32U, &playGrid[(map_pos_y>>1U)+k][new_map_pos_x>>1U]);
            }
        } else 
        {
            for (UINT8 k = 0U; k != 9U; ++k)
            {
                drawBkgTile((new_map_pos_x + 18U)%32U, (map_pos_y+(k<<1U))%32U, &playGrid[(map_pos_y>>1U)+k][(new_map_pos_x+18U)>>1U]);
            }
        }
        map_pos_x = new_map_pos_x;
    }
}

void drawBkgTile(UINT8 x, UINT8 y, TileObject *tile)
{
    set_bkg_tiles(x, y, 2U, 2U, forestMetaTiles[tile->face]);
}
