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