#include <gb/gb.h>
// #include "songPlayer.h"

//#include "graphics/statsTextMap.c"

UINT8 isFadedOut;
// UINT8 shouldStartMusic;

UINT8 getIsFadedOut()
{
    return isFadedOut;
}

// UINT8 getShouldStartMusic()
// {
//     if (shouldStartMusic != 1)
//     {
//         shouldStartMusic = 1;
//         return 0;
//     }
//     else
//         return 1;
// }

// void setShouldStartMusic(UINT8 val)
// {
//     shouldStartMusic = val;
// }

void performantdelay(UINT8 numloops)
{
    UINT8 j;
    for (j = 0U; j != numloops; j++)
    {
        wait_vbl_done();
    }     
}

void fadein() 
{
    UINT8 i;
    for (i = 0U; i != 3U; i++) 
    {
        switch(i) 
        {
            case 0U:
                // OBP0_REG = 0x40;  // sprites
                OBP0_REG = 0x40;  // dark grey as transparent
                BGP_REG = 0x40;  // bkg
                break;
            case 1U:
                // OBP0_REG = 0x90;
                OBP0_REG = 0x81;  // dark grey as transparent
                BGP_REG = 0x90;
                break;
            case 2U:
                // OBP0_REG = 0xE4;  // white as transparent
                // OBP0_REG = 0xE1;  // light grey as transparent
                OBP0_REG = 0xD2;  // dark grey as transparent  11010010
                BGP_REG = 0xE4;
                break;
        }
        performantdelay(1U);
    }
    isFadedOut = 0U;
    // pauseSong(0U);
}

void fadeout() 
{
    UINT8 i;
    // pauseSong(1U);
    for (i = 0U; i != 4U; i++) 
    {
        switch(i) 
        {
            case 0U:
                // OBP0_REG = 0xE4;
                OBP0_REG = 0xD2;  // dark grey as transparent  11010010
                BGP_REG = 0xE4;
                break;
            case 1U:
                // OBP0_REG = 0x90;
                OBP0_REG = 0x81;  // dark grey as transparent
                BGP_REG = 0x90;
                break;
            case 2U:
                // OBP0_REG = 0x40;
                OBP0_REG = 0x40;  // dark grey as transparent
                BGP_REG = 0x40;
                break;
            case 3U:
                OBP0_REG = 0x00;
                BGP_REG = 0x00;
                break;
        }
        performantdelay(1U);
    }

    // TODO: change the 20 if more sprites get added
    // I'm sure there's a better way to remove sprites
    for (i = 0U; i != 20U; i++)
    {
        move_sprite(i, 0U, 0U);
    }

    isFadedOut = 1U;
}


