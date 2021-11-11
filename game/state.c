#include "state.h"
#include "../images/geralt/geralt.h"
#include "../graphics/gba.h"

struct entity player = {
    WIDTH / 2 - GERALT_WIDTH / 2,
    HEIGHT - GERALT_HEIGHT,
    GERALT_WIDTH,
    GERALT_HEIGHT,
    0,
    0,
    100,
    0,
    geralt
};

struct state cs;
struct state ps;

void setupGameState() {
    cs.player = player;
    cs.numEnemies = 0;
    cs.initialized = 1;
    ps = cs;
}