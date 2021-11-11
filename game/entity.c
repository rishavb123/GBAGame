#include "../graphics/draw.h"
#include "entity.h"
#include "config.h"

void eraseEntity(struct entity *e)
{
    drawRectDMA(e->y, e->x, e->w, e->h, BACKGROUND_COLOR);
}

void drawEntity(struct entity *e)
{
    drawImageDMA(e->y, e->x, e->w, e->h, e->image);
}

void jump(struct entity *e)
{
    if (e->onGround)
    {
        e->dy = JUMP_SPEED;
    }
}

void update(struct entity *e)
{
    e->x += e->dx;
    if (e->onGround)
    {
        if (e->dy < 0) {
            e->y += e->dy;
            e->onGround = 0;
        }
        else
            e->dy = 0;
    }
    else
    {
        e->y += e->dy;
        e->dy += G;
        if (e->y + e->h >= HEIGHT) {
            e->y = HEIGHT - e->h;
            e->onGround = 1;
        }
    }
}