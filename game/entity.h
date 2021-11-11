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
    const unsigned short *image;
};

/**
 * @brief erases an entity
 * 
 * @param e the entity to erase
 */
void eraseEntity(struct entity *e);

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

/**
 * @brief checks if two entities collide
 * 
 * @param e1 the first entity
 * @param e2 the second entity
 * @return int whether or not it collides
 */
int collide(struct entity *e1, struct entity *e2);

#endif