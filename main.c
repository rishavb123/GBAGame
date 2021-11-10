#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "graphics/draw.h"
#include "graphics/gba.h"

#include "utils/misc.h"

#include "images/startScreen/startScreen.h"

enum gba_state
{
    START,
    PLAY,
    DEATH
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
    drawFullScreenImageDMA(startScreen);

    while (1) {
        currentButtons = BUTTONS; // Load the current state of the buttons

        waitForVBlank();

        switch (state)
        {
            case START:
                if(KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                    state = PLAY;
                    fillScreenDMA(BLACK);
                }
                break;
            case PLAY:

                break;
            case DEATH:

                break;
            }

        previousButtons = currentButtons; // Store the current state of the buttons
    }

    UNUSED(previousButtons); // You can remove this once previousButtons is used

    return 0;
}
