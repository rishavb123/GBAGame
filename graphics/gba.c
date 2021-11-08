#include "gba.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
u32 vBlankCounter = 0;

void waitForVBlank(void)
{
    // (1)
    // Write a while loop that loops until we're NOT in vBlank anymore:
    // (This prevents counting one VBlank more than once if your app is too fast)
    while (SCANLINECOUNTER > HEIGHT)
        ;

    // (2)
    // Write a while loop that keeps going until we're in vBlank:
    while (SCANLINECOUNTER < HEIGHT)
        ;

    // (3)
    // Finally, increment the vBlank counter:
    vBlankCounter++;
}

void setPixel(int row, int col, u16 color)
{
    videoBuffer[OFFSET(row, col, WIDTH)] = color;
}

void drawRectDMA(int row, int col, int width, int height, volatile u16 color)
{
    for (int r = row; r < row + height; r++)
    {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(r, col, WIDTH)];
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
    }
}

void drawFullScreenImageDMA(const u16 *image)
{
    DMA[3].src = image;
    DMA[3].dst = videoBuffer;
    DMA[3].cnt = (WIDTH * HEIGHT) | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
}

void drawImageDMA(int row, int col, int width, int height, const u16 *image)
{
    for (int r = 0; r < height; r++)
    {
        DMA[3].src = &image[OFFSET(r, 0, width)]
        ;
        DMA[3].dst = &videoBuffer[OFFSET(r + row, col, WIDTH)];
        DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
    }
}

void fillScreenDMA(volatile u16 color)
{
    drawRectDMA(0, 0, WIDTH, HEIGHT, color);
}

void drawChar(int row, int col, char ch, u16 color)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (fontdata_6x8[OFFSET(j, i, 6) + ch * 48])
            {
                setPixel(row + j, col + i, color);
            }
        }
    }
}

void drawString(int row, int col, char *str, u16 color)
{
    while (*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}

void drawCenteredString(int row, int col, int width, int height, char *str, u16 color)
{
    u32 len = 0;
    char *strCpy = str;
    while (*strCpy)
    {
        len++;
        strCpy++;
    }

    u32 strWidth = 6 * len;
    u32 strHeight = 8;

    int new_row = row + ((height - strHeight) >> 1);
    int new_col = col + ((width - strWidth) >> 1);
    drawString(new_row, new_col, str, color);
}
