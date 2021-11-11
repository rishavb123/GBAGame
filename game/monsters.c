#include "monsters.h"
#include "entity.h"
#include "../utils/rand.h"
#include "../images/monsters/werewolf/werewolf.h"
#include "../graphics/gba.h"
#include "config.h"

struct entity makeWerewolf() {
    struct entity wolf = {
        0,
        HEIGHT - WEREWOLF_HEIGHT,
        WEREWOLF_WIDTH,
        WEREWOLF_HEIGHT,
        SPEED * 2,
        0,
        20,
        0,
        werewolf
    };
    if (randint(0, 2) == 0) {
        wolf.x = WIDTH - WEREWOLF_WIDTH;
        wolf.dx = -wolf.dx;
    }
    return wolf;
}