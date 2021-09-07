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

void printLine(UINT8 xCoord, UINT8 yCoord, unsigned char* line)
{
    UINT8 size = 0U;
    while (*line)
    {
        *line -= (0x37);
        line++;
        size++;
    }
    
    set_bkg_tiles(xCoord, yCoord, size, 1U, line-size);
}

void setBlankBg()
{
    for (i = 0U; i != 20U; i++)
    {
        for (j = 0U; j != 18U; j++)
        {
            set_bkg_tile_xy(i, j, 0xFF);
        }
    }
}
