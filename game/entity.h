#ifndef ENTITY_H
#define ENTITY_H

/**
 * @brief any entity within the game
 */
struct entity
{
    int x;
    int y;
    int w;
    int h;
    int dx;
    int dy;
    int health;
    int onGround;
    short *image;
};

/**
 * @brief draws an entity
 * 
 * @param e the entity to draw
 */
void drawEntity(struct entity *e);

/**
 * @brief causes an entity to jump
 * 
 * @param e the entity that will jump
 */
void jump(struct entity *e);

/**
 * @brief updates the entity each frame
 * 
 * @param e the entity to update
 */
void update(struct entity *e);

#endif