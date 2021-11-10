#include "state.h"
#include "../images/geralt/geralt.h"

const struct entity player = {
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

struct state *cs = {
    START
};


struct state *ps;