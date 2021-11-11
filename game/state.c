#include "state.h"
#include "../images/geralt/geralt.h"

struct entity player = {
    0,
    0,
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

void setupInitialState() {
    cs.gameState = START;
    cs.player = player;
    cs.numEnemies = 0;
    ps = cs;
}