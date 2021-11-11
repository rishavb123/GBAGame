#ifndef STATE_H
#define STATE_H

#include "entity.h"
#include "config.h"
#include "../graphics/gba.h"

enum gamestate
{
    START,
    PLAY,
    DEATH
};

struct state {
    enum gamestate gameState;
    struct entity player;
    int numEnemies;
    struct entity enemies[MAX_ENEMIES];
    u32 buttons;
    int initialized;
};

extern struct state cs;
extern struct state ps;

void setupGameState();

#endif
