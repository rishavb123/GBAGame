#include "main.h"

#include <stdio.h>
// #include <stdlib.h>

#include "game/config.h"
#include "game/state.h"
#include "game/monsters.h"
#include "game/entity.h"
#include "graphics/draw.h"
#include "graphics/gba.h"

#include "utils/misc.h"
#include "utils/rand.h"

#include "images/startScreen/startScreen.h"
#include "images/death/dead.h"
#include "images/geralt/geralt.h"

int main(void)
{

    // Manipulate REG_DISPCNT here to set Mode 3. //
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // draws in black background
    waitForVBlank();
    drawFullScreenImageDMA(startScreen);

    int t = 0;
    cs.gameState = START;

    while (1)
    {
        cs.buttons = BUTTONS; // Load the current state of the buttons

        waitForVBlank();
        if (KEY_JUST_PRESSED(BUTTON_SELECT, cs.buttons, ps.buttons))
        {
            cs.gameState = START;
            drawFullScreenImageDMA(startScreen);
        }

        switch (cs.gameState)
        {
        case START:
            if (KEY_JUST_PRESSED(BUTTON_START, cs.buttons, ps.buttons))
            {
                cs.gameState = PLAY;
                setupGameState();
                ps = cs;
                fillScreenDMA(BACKGROUND_COLOR);
            }
            break;
        case PLAY:

            drawRectDMA(10, 10, 100, 10, BLACK);
            drawRectDMA(10, 10, cs.player.health, 10, GREEN);
            drawRectDMA(10, WIDTH - 200, 200, 20, BLACK);
            int score = t / 100;
            if (score > 999)
                score = 999;
            char s2[11];
            snprintf(s2, 11, "N: %d", score);
            drawCenteredString(10, WIDTH - 200, 200, 20, s2, WHITE);

            if (KEY_JUST_PRESSED(BUTTON_UP, cs.buttons, ps.buttons))
            {
                jump(&cs.player);
            }

            if (!(t % SPAWN_ENEMY))
            {
                cs.enemies[cs.numEnemies] = makeWerewolf();
                cs.numEnemies++;
            }

            if (!(t % PHYSICS_UPDATE))
            {
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

                eraseEntity(&ps.player);
                update(&cs.player);
                drawEntity(&cs.player);

                for (int i = 0; i < ps.numEnemies; i++)
                    eraseEntity(&ps.enemies[i]);

                for (int i = 0; i < cs.numEnemies; i++)
                {
                    update(&cs.enemies[i]);
                    drawEntity(&cs.enemies[i]);

                    if (collide(&cs.player, &cs.enemies[i]) || collide(&cs.enemies[i], &cs.player))
                    {
                        cs.player.health -= 5;
                    }
                    if (cs.enemies[i].x + cs.enemies[i].w > WIDTH || cs.enemies[i].x < 0)
                    {
                        eraseEntity(&cs.enemies[i]);
                        for (int j = i; j < cs.numEnemies; j++)
                            cs.enemies[j] = cs.enemies[j + 1];
                        cs.numEnemies--;
                        i--;
                    }
                }
            }

            if (cs.player.health <= 0)
            {
                cs.gameState = DEATH;
                drawFullScreenImageDMA(dead);
                drawCenteredString(10, 10, WIDTH - 20, HEIGHT - 20, "You Died :(", GREEN);
                cs.initialized = 0;
                t = 0;
            }

            t++;
            break;
        case DEATH:
            break;
        }
        ps = cs;
    }

    return 0;
}
