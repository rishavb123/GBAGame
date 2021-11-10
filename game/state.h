#ifndef STATE_H
#define STATE_H

#include "entity.h"
#include "config.h"

enum gamestate
{
    START,
    PLAY,
    DEATH
};

struct state {
    enum gamestate gameState;
    struct entity geralt;
    int numEnemies;
    struct entity enemies[MAX_ENEMIES];
};

extern struct state *cs;
extern struct state *ps;

#endif
