#include "glowstick.h"

#define MAX_NUM_GLOWSTICKS 32
int num_glowsticks = 0;
entity_t *glowsticks[MAX_NUM_GLOWSTICKS];

void entity_glowsticks_add(entity_t *entity)
{
    glowsticks[num_glowsticks++] = entity;
}

void entity_glowsticks_remove(entity_t *entity)
{
    int i;
    for (i = 0; i < entity_glowsticks_deployed(); i++) {
        if (entity->id == entity_glowsticks_get(i)->id) {
            break;
        }
    }

    for (int move = i; move < MAX_NUM_GLOWSTICKS - 1; move++) {
        glowsticks[move] = glowsticks[move + 1];
    }

    glowsticks[MAX_NUM_GLOWSTICKS - 1] = NULL;
}

void entity_glowstick_init(entity_t *entity) {
    entity->type = entity_type_glowstick;
    entity->free = entity_glowstick_free;
    entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_024.png");

    entity_glowsticks_add(entity);
}

void entity_glowstick_free(entity_t *entity) {
    entity_glowsticks_remove(entity);
}

int entity_glowsticks_deployed() {
    return num_glowsticks;
}

entity_t *entity_glowsticks_get(int deployed) {
    return glowsticks[deployed];
}
