#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/config.h"
#include "game/state.h"
#include "graphics/draw.h"
#include "graphics/gba.h"

#include "utils/misc.h"

#include "images/startScreen/startScreen.h"

int main(void)
{

    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // Save current and previous state of button input.

    setupInitialState();

    // draws in black background
    waitForVBlank();
    drawFullScreenImageDMA(startScreen);

    int t = 0;

    while (1)
    {
        cs.buttons = BUTTONS; // Load the current state of the buttons

        waitForVBlank();

        switch (cs.gameState)
        {
        case START:
            if (KEY_JUST_PRESSED(BUTTON_START, cs.buttons, ps.buttons))
            {
                cs.gameState = PLAY;
                fillScreenDMA(BACKGROUND_COLOR);
            }
            break;
        case PLAY:

            if (KEY_JUST_PRESSED(BUTTON_UP, cs.buttons, ps.buttons))
            {
                jump(&cs.player);
            }

            if (t % PHYSICS_UPDATE == 0) {
                if (KEY_DOWN(BUTTON_LEFT, cs.buttons))
                {
                    cs.player.dx = -SPEED;
                }
                else if (KEY_DOWN(BUTTON_RIGHT, cs.buttons))
                {
                    cs.player.dx = SPEED;
                }
                else
                {
                    cs.player.dx = 0;
                }

                update(&cs.player);
                eraseEntity(&ps.player);
                drawEntity(&cs.player);
            }
            t++;
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
