#ifndef GBA_H
#define GBA_H

#include "colors.h"
#include "dma.h"
#include "input.h"
#include "../utils/misc.h"
#include "../utils/rand.h"
#include "../utils/types.h"

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------
#define OFFSET(row, col, width) ((col)+(width)*(row))

#define REG_DISPCNT (*(volatile unsigned short *) 0x4000000)
#define MODE3 3
#define BG2_ENABLE (1<<10)

// The size of the GBA Screen
#define WIDTH 240
#define HEIGHT 160

// This is initialized in gba.c
extern volatile unsigned short *videoBuffer;

// ---------------------------------------------------------------------------
//                       VBLANK
// ---------------------------------------------------------------------------
#define SCANLINECOUNTER (*(volatile unsigned short *) 0x4000006)

// Use this variable to count vBlanks. Initialized in gba.c and to be
// manipulated by waitForVBlank()
extern u32 vBlankCounter;

/*
 * Runs a blocking loop until the start of next VBlank.
 */
void waitForVBlank(void);

/* Contains the pixels of each character from a 6x8 font */
// This is in the font.c file. You can replace the font if you want.
extern const unsigned char fontdata_6x8[12288];

#endif
