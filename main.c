#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/config.h"
#include "game/state.h"
#include "graphics/draw.h"
#include "graphics/gba.h"

#include "utils/misc.h"

#include "images/startScreen/startScreen.h"

int main(void) {
    
    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // Save current and previous state of button input.
    
    setupInitialState();

    // draws in black background
    waitForVBlank();
    drawFullScreenImageDMA(startScreen);

    while (1) {
        cs.buttons = BUTTONS; // Load the current state of the buttons

        waitForVBlank();

        switch (cs.gameState)
        {
            case START:
                if(KEY_JUST_PRESSED(BUTTON_START, cs.buttons, ps.buttons)) {
                    cs.gameState = PLAY;
                    fillScreenDMA(BACKGROUND_COLOR);
                }
                break;
            case PLAY:
                
                break;
            case DEATH:
                if (KEY_JUST_PRESSED(BUTTON_START, cs.buttons, ps.buttons))
                {
                    cs.gameState = PLAY;
                    fillScreenDMA(BACKGROUND_COLOR);
                }
                else if (KEY_JUST_PRESSED(BUTTON_SELECT, cs.buttons, ps.buttons))
                {
                    cs.gameState = START;
                    drawFullScreenImageDMA(startScreen);
                }
                break;
        }
        ps = cs;
    }

    return 0;
}
