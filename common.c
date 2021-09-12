#include <gb/gb.h>
#include <rand.h>

extern UINT8 i;
extern UINT8 j;
extern UINT8 r;
UINT8 getRandUint(UINT8 modulo)
{
    r = 201U;
    while (r >= 200U) {
        r = rand() % modulo;
    }
    return r;
}

void printLine(UINT8 xCoord, UINT8 yCoord, unsigned char* line, UINT8 printToWindow)
{
    unsigned char tempLine[18U];
    unsigned char* tempLinePtr = tempLine;
    UINT8 size = 0U;
    UINT8 diff = 0x37;
    while (*line)
    {

        if (*line <= 0x39) // 0-9
            diff = 0x30;
        else if (*line == 0x20)  // Space
            diff = 0xFF;
        else  // A-Z
            diff = 0x37;

        *tempLinePtr = *line - diff;
        tempLinePtr++;
        line++;
        size++;
    }
    
    if (printToWindow == FALSE)
        set_bkg_tiles(xCoord, yCoord, size, 1U, tempLinePtr-size);
    else
        set_win_tiles(xCoord, yCoord, size, 1U, tempLinePtr-size);
}

void setBlankBg()
{
    for (i = 0U; i != 21U; i++)
    {
        for (j = 0U; j != 18U; j++)
        {
            set_bkg_tile_xy(i, j, 0xFF);
        }
    }
}

void setBlankWin()
{
    for (i = 0U; i != 21U; i++)
    {
        for (j = 0U; j != 18U; j++)
        {
            set_win_tile_xy(i, j, 0xFF);
        }
    }
}
