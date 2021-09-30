#include <gb/gb.h>
#include <gb/metasprites.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"
#include "../ram.h"

#include "../database/RoomData.h"

#include "../maps/cardDescStrings.h"
#include "../maps/textWindowMap.h"

#include "../objects/EventObject.h"
#include "../objects/PlayerObject.h"
#include "../objects/RoomObject.h"
#include "../objects/TileObject.h"

#include "../sprites/player.h"


#define PLAYER_SPR_NUM_START 1U
#define PLAYER_TILE_NUM_START 3U

extern const unsigned char forestTiles[];
extern const unsigned char forestMetaTiles[][4U];

const UINT8 forestTileIndex = 0xA0U;

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
extern UINT8 enemyId;
extern UINT8 roomId;
extern UINT8 shopId;
extern UINT8 dialogId;
extern UINT8 dialogQueue[];
extern UINT8 dialogQueueCount;

UINT8 playerstate;

TileObject playGrid[30U][30U];
TileObject* tilePtr;
const char * roomMapPtr;
const EventObject * roomEventsPtr;
const EventObject * roomAEventsPtr;
RoomObject room;

UINT8 encounterCounter = 10U;
UINT8 encounterRate = 10U;

UINT8 gridW = 20U;
UINT8 gridH = 18U;
UINT16 camera_max_x = 10U * 16U;
UINT16 camera_max_y = 9U * 16U;

UINT8 shouldHidePlayer = FALSE;
const UINT8 PLAYER_X_LEFT   = 16U;  // 8 offset due to GB specs, 8 offset due to metatile centering
const UINT8 PLAYER_X_CENTER = 96U;
const UINT8 PLAYER_X_RIGHT  = 160U;
const UINT8 PLAYER_Y_UP     = 24U;
const UINT8 PLAYER_Y_CENTER = 88U;
const UINT8 PLAYER_Y_DOWN   = 152U;
const UINT8 playerSpeed     = 4U;

#define STARTPOS 0U
#define STARTCAM 0U

// current and new positions of the camera in pixels
WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
// redraw flag, indicates that camera position was changed
UBYTE redraw;

extern UINT8 animTick;
extern UINT8 animFrame;

/* SUBSTATE METHODS */
void phaseInitOverworld();
void phaseInitMap();
void phasePlayerInputs();

/* HELPER METHODS */
void loadRoom();
void checkUnderfootTile();
void openBattle();
void openShop();

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
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = MM_INIT;
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
    set_bkg_data(forestTileIndex, 60U, forestTiles);

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    HIDE_WIN;

    initrand(DIV_REG);
    redraw = FALSE;

    substate = OW_INIT_MAP;
}

void phaseInitMap()
{
    // Check levelId, pull appropriate level
    loadRoom();

    // Check player coords/dir, draw player appropriately
    SCX_REG = camera_x; SCY_REG = camera_y;

    // Load room map into playGrid
    UINT16 c = 0U;
    for (j = 0U; j != gridH; j++)
    {
        for (i = 0U; i != gridW; i++)
        {
            playGrid[j][i].face = *(roomMapPtr +c);
            ++c;
        }
    }

    // Draw grid
    for (i = 0U; i != 10U; i++)
    {
        for (j = 0U; j != 9U; j++)
        {
            drawBkgTile((map_pos_x+(i<<1U))%32U, (map_pos_y+(j<<1U))%32U, &playGrid[(map_pos_y>>1U)+j][(map_pos_x>>1U)+i]);
        }
    }

    // Spawn player
    set_sprite_data(PLAYER_TILE_NUM_START, sizeof(player_data) >> 4U, player_data);
    move_metasprite(player_metasprites[player.dir*3 + 1U], PLAYER_TILE_NUM_START, PLAYER_SPR_NUM_START, player.x, player.y);

    substate = OW_PLAYER_INPUTS;

    fadein();
}

void phasePlayerInputs()
{
    shouldHidePlayer = FALSE;

    // Player movements and inputs
    if (playerstate == WALKING)
    {
        if (player.dir == N)
        {
            if (camera_y == 0U || player.y != PLAYER_Y_CENTER)
            {
                player.y -= playerSpeed;
                if ((player.y + 8U) % 16U == 0U)  // +8 because of the annoying metatiles center + 16 vert offset for sprites
                {
                    player.yTile--;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_y -= playerSpeed;
                if (camera_y % 16U == 0U)
                {
                    player.yTile--;
                    checkUnderfootTile();
                }
            }
        }
        else if (player.dir == S)
        {
            if (camera_y == camera_max_y || player.y != PLAYER_Y_CENTER)
            {
                player.y += playerSpeed;
                if ((player.y - 8U) % 16U == 0U)
                {
                    player.yTile++;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_y += playerSpeed;
                if (camera_y % 16U == 0U)
                {
                    player.yTile++;
                    checkUnderfootTile();
                }
            }
        }
        else if (player.dir == W)
        {
            if (camera_x == 0U || player.x != PLAYER_X_CENTER)
            {
                player.x -= playerSpeed;
                if (player.x % 16U == 0U)
                {
                    player.xTile--;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_x -= playerSpeed;
                if (camera_x % 16U == 0U)
                {
                    player.xTile--;
                    checkUnderfootTile();
                }
            }
        }
        else if (player.dir == E)
        {
            if (camera_x == camera_max_x || player.x != PLAYER_X_CENTER)
            {
                player.x += playerSpeed;
                if (player.x % 16U == 0U)
                {
                    player.xTile++;
                    checkUnderfootTile();
                }
            }
            else
            {
                camera_x += playerSpeed;
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
            hide_metasprite(player_metasprites[player.dir*3 + animFrame], PLAYER_SPR_NUM_START);
            return;
        }
        else if (curJoypad & J_A && !(prevJoypad & J_A))
        {
            // Determine coords of square player is facing
            i = player.xTile;
            j = player.yTile;
            switch (player.dir)
            {
                case N: --j; break;
                case S: ++j; break;
                case W: --i; break;
                case E: ++i; break;
            }
            // Interact with A-event if present
            for (l = 0U; l != room.aEventsLen; l++)
            {
                if (i == (roomAEventsPtr+l)->x && j == (roomAEventsPtr+l)->y)
                {
                    if ((roomAEventsPtr+l)->type == EV_DIALOG)
                    {
                        dialogQueue[dialogQueueCount] = (roomAEventsPtr+l)->value << 1U;
                        ++dialogQueueCount;
                        oldGamestate = STATE_OVERWORLD;
                        oldSubstate = OW_PLAYER_INPUTS;
                        gamestate = STATE_DIALOG;
                        substate = DIALOG_INIT;
                    }
                    else if ((roomAEventsPtr+l)->type == EV_OPEN_SHOP)
                    {
                        shopId = (roomAEventsPtr+l)->value;
                        openShop();
                        return;
                    }
                    else if ((roomAEventsPtr+l)->type == EV_BATTLE)
                    {
                        enemyId = (roomAEventsPtr+l)->value;
                        openBattle();
                        return;
                    }
                    else if ((roomAEventsPtr+l)->type == EV_SAVE)
                    {
                        player.hpCur = player.hpMax;

                        ENABLE_RAM_MBC1;
                        SWITCH_RAM_MBC1(0U);
                        saveGameData();
                        DISABLE_RAM_MBC1;

                        fadeout();
                        fadein();

                        dialogQueue[dialogQueueCount] = 16U;
                        ++dialogQueueCount;
                        oldGamestate = STATE_OVERWORLD;
                        oldSubstate = OW_PLAYER_INPUTS;
                        gamestate = STATE_DIALOG;
                        substate = DIALOG_INIT;
                    }
                }
            }
        }
        // Cardinal movement
        else if ((curJoypad == J_UP) && (prevJoypad == J_UP))
        {
            player.dir = N;

            if (player.y != 0U && playGrid[player.yTile-1U][player.xTile].face < 3U)
            {
                // Move sprite, not camera
                if (camera_y == 0U || player.y > PLAYER_Y_CENTER)
                {
                    if (player.y != PLAYER_Y_UP)
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
        }
        else if ((curJoypad == J_DOWN) && (prevJoypad == J_DOWN))
        {
            player.dir = S;

            if (player.y != 0U && playGrid[player.yTile+1U][player.xTile].face < 3U)
            {
                // Move sprite, not camera
                if (camera_y == camera_max_y || player.y < PLAYER_Y_CENTER)
                {
                    if (player.y != PLAYER_Y_DOWN)
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
        } 
        else if ((curJoypad == J_LEFT) && (prevJoypad == J_LEFT))
        {
            player.dir = W;

            if (player.y != 0U && playGrid[player.yTile][player.xTile-1U].face < 3U)
            {
                // Move sprite, not camera
                if (camera_x == 0U || player.x > PLAYER_X_CENTER)
                {
                    if (player.x != PLAYER_X_LEFT)
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
        }
        else if ((curJoypad == J_RIGHT) && (prevJoypad == J_RIGHT))
        {
            player.dir = E;

            if (player.y != 0U && playGrid[player.yTile][player.xTile+1U].face < 3U)
            {
                // Move sprite, not camera
                if (camera_x == camera_max_x || player.x < PLAYER_X_CENTER)
                {
                    if (player.x != PLAYER_X_RIGHT)
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
    } 

    if (playerstate == WALKING)
    {
        animFrame = animTick % 16U;
        animFrame /= 4U;
        if (animFrame == 3U)
            animFrame = 1U;
        ++animTick;
    }
    else
        animFrame = 1U;
    
    if (shouldHidePlayer == TRUE)
        hide_metasprite(player_metasprites[player.dir*3 + animFrame], PLAYER_SPR_NUM_START);
    else
        move_metasprite(player_metasprites[player.dir*3 + animFrame], PLAYER_TILE_NUM_START, PLAYER_SPR_NUM_START, player.x, player.y);

    if (redraw && playerstate == WALKING)
    {
        wait_vbl_done();
        draw_new_bkg();
        redraw = FALSE;
    }
    else
        wait_vbl_done();
}


/******************************** HELPER METHODS *********************************/
void loadRoom()
{
    room = roomDict[roomId];
    gridW = room.w;
    gridH = room.h;
    camera_max_x = (((gridW - 20U) * 2U) + 20U) * 8U;
    camera_max_y = (((gridH - 18U) * 2U) + 18U) * 8U;
    roomMapPtr = room.roomMap;
    roomEventsPtr = room.events;
    roomAEventsPtr = room.aEvents;
    encounterRate = room.encounterRate;
    encounterCounter = encounterRate;
    
    // Slightly randomize encounter rate
    if (room.encounterRate != 0U)
    {
        encounterCounter -= room.encounterRate >> 1U;
        r = getRandUint(encounterRate);
        encounterCounter += r;
    }

    // Reset camera and player position
    if (player.xTile > 5)  // 5 is the x offset from left to center
    {
        // If on the far right side
        if (player.xTile > (gridW - 5U))  // 5 is the x offset from right to center
        {
            camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.x = PLAYER_X_RIGHT - ((gridW - player.xTile) * 16U) + 16U;  // Classic annoying padding
        }
        else
        {
            camera_x = (player.xTile-5U)*16U;
            if (camera_x > camera_max_x)
                camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.x = PLAYER_X_CENTER;
        }
    }
    else
    {
        map_pos_x = 0U;
        camera_x = 0U;
        new_camera_x = camera_x;
        player.x = player.xTile % 20U * 16U + 16U;  // Classic annoying padding
    }
    if (player.yTile > 4)  // 4 is the y offset from top to center
    {
        // If on the far bottom
        if (player.yTile > (gridH - 5U))  // 4 is the y offset from bottom to center; - 1 extra for index adjustments
        {
            camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            player.y = PLAYER_Y_DOWN - ((gridH - player.yTile) * 16U) + 16U;  // Classic annoying padding
        }
        else
        {
            camera_y = (player.yTile-4U)*16U;
            if (camera_y > camera_max_y)
                camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            player.y = PLAYER_Y_CENTER;
        }
    }
    else
    {
        map_pos_y = 0U;
        camera_y = 0U;
        new_camera_y = camera_y;
        player.y = player.yTile % 18U * 16U + 24U;  // Classic annoying padding
    }

}

void checkUnderfootTile()
{
    playerstate = IDLE;
    UINT8 didEvent = FALSE;

    for (l = 0U; l != room.eventsLen; l++)
    {
        if (player.xTile == (roomEventsPtr+l)->x && player.yTile == (roomEventsPtr+l)->y)
        {
            if ((roomEventsPtr+l)->type == EV_DIALOG)
            {
                didEvent = TRUE;
                dialogQueue[dialogQueueCount] = (roomEventsPtr+l)->value << 1U;
                ++dialogQueueCount;
                oldGamestate = STATE_OVERWORLD;
                oldSubstate = OW_PLAYER_INPUTS;
                gamestate = STATE_DIALOG;
                substate = DIALOG_INIT;
            }
            else if ((roomEventsPtr+l)->type == EV_LOADROOM)
            {
                didEvent = TRUE;
                fadeout();
                roomId = spawnLocations[(roomEventsPtr+l)->value][0];
                player.xTile = spawnLocations[(roomEventsPtr+l)->value][1];
                player.yTile = spawnLocations[(roomEventsPtr+l)->value][2];
                player.dir = spawnLocations[(roomEventsPtr+l)->value][3];

                gamestate = STATE_OVERWORLD;
                substate = OW_INIT_OW;
            }
            else if ((roomEventsPtr+l)->type == EV_BATTLE)
            {
                enemyId = (roomEventsPtr+l)->value;
                openBattle();
                return;
            }
        }
    }

    // Encounter check, but only if we didn't trigger an event flag above
    if (didEvent == FALSE)
    {
        --encounterCounter;
        if (encounterCounter == 0U && encounterRate != 0U)
        {
            encounterCounter = encounterRate;
            enemyId = room.encounterSet[getRandUint(4U)];
            openBattle();
        }
    }
}

void openBattle()
{
    oldGamestate = STATE_OVERWORLD;
    oldSubstate = OW_PLAYER_INPUTS;
    gamestate = STATE_BATTLE;
    substate = GAME_KAISHI;
    shouldHidePlayer = TRUE;
    fadeout();
}

void openShop()
{
    oldSubstate = substate;
    oldGamestate = gamestate;
    gamestate = STATE_SHOP;
    substate = SHOP_INIT;
    hide_metasprite(player_metasprites[player.dir*3 + animFrame], PLAYER_SPR_NUM_START);
}

/******************************** DISPLAY METHODS ********************************/
void draw_new_bkg() {
    // Vertical
    new_map_pos_y = (BYTE)(new_camera_y >> 3U);
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