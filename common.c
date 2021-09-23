#include <gb/gb.h>
#include <rand.h>

extern const unsigned char borderTiles[];
extern const unsigned char cardTiles[];

const UINT8 borderTileIndex = 0x30U;
const UINT8 cardsTileIndex  = 0x40U;

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
        if (*line == ' ')
            diff = 0x21;
        else if (*line == '.')
            diff = 0x0A;
        else if (*line == ',')
            diff = 0x06;
        else if (*line == '?')
            diff = 0x1A;
        else if (*line <= 0x39)  // 0-9... and anything lower in index than 0
            diff = 0x30;
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

void loadOverworldGraphics()
{
    UINT8 cb = _current_bank;
    SWITCH_ROM_MBC1(1U);
    set_bkg_data(borderTileIndex, 8U, borderTiles);
    set_bkg_data(cardsTileIndex, 66U, cardTiles);
    SWITCH_ROM_MBC1(cb);
}
