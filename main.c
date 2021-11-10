#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "graphics/draw.h"
#include "graphics/gba.h"

#include "utils/misc.h"

#include "images/garbage/garbage.h"

enum gba_state {
    START,
    PLAY,
    WIN,
    LOSE,
};

int main(void) {
    
    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // Save current and previous state of button input.
    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    // Load initial application state
    enum gba_state state = START;

    // draws in black background
    waitForVBlank();
    fillScreenDMA(BLACK);

    while (1) {
        currentButtons = BUTTONS; // Load the current state of the buttons

        waitForVBlank();

        drawImageDMA(0, 0, GARBAGE_WIDTH, GARBAGE_HEIGHT, garbage);

        switch (state)
        {
            case START:

                // state = ?
                break;
            case PLAY:

                // state = ?
                break;
            case WIN:

                // state = ?
                break;
            case LOSE:

                // state = ?
                break;
        }

        previousButtons = currentButtons; // Store the current state of the buttons
    }

    UNUSED(previousButtons); // You can remove this once previousButtons is used

    return 0;
}
