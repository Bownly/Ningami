#include <gb/gb.h>
#include <rand.h>

#include "../common.h"
#include "../enums.h"
#include "../fade.h"

#include "../maps/textWindowMap.h"

extern const unsigned char dialogStrings[][20];

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

extern UINT8 dialogId;
extern UINT8 dialogQueue[];
extern UINT8 dialogQueueCount;

extern UINT8 animTick;
extern UINT8 animFrame;

const UINT8 xAnchorDialogCursor = 156U;
const UINT8 yAnchorDialogCursor = 148U;


/* SUBSTATE METHODS */
void phaseInitDialogbox();
void phaseDialogboxLoop();

/* HELPER METHODS */

/* DISPLAY METHODS */

void dialogStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case DIALOG_INIT:
            phaseInitDialogbox();
            break;
        case DIALOG_LOOP:
            phaseDialogboxLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = MM_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
void phaseInitDialogbox()
{
    // Draw window dialog box and text
    set_win_tiles(0U, 0U, 20U, 4U, textWindowMap);

    if (dialogQueueCount != 0)
    {
        --dialogQueueCount;
        printLine(1U, 1U, dialogStrings[dialogQueue[dialogQueueCount]], TRUE);
        printLine(1U, 2U, dialogStrings[dialogQueue[dialogQueueCount]+1], TRUE);

        // Show window
        move_win(7U, 112U);
        SHOW_WIN;

        // Draw cursor
        move_sprite(0U, xAnchorDialogCursor, yAnchorDialogCursor);
    }
    
    substate = DIALOG_LOOP;
}

void phaseDialogboxLoop()
{
    ++animTick;
    animFrame = animTick / 8U % 4U;
    if (animFrame == 3U)
        animFrame = 1U;
    set_sprite_tile(0U, animFrame);

    // If B or Start, hide window
    if ((curJoypad & J_A && !(prevJoypad & J_A)) || (curJoypad & J_B && !(prevJoypad & J_B)))
    {
        if (dialogQueueCount != 0U)
        {
            substate = DIALOG_INIT;
        }
        else
        {
            animTick = 0U;
            animFrame = 0U;
            move_sprite(0U, 0U, 0U);
            gamestate = oldGamestate;
            substate = oldSubstate;
            HIDE_WIN;
        }
    }
  
}


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/

