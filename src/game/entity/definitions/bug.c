#include "bug.h"
#include "player.h"

#define BUG_SPEED 1.0f

#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128

size_t bugs_alive;

void entity_bug_init(entity_t *entity)
{
    entity->type = entity_type_bug;
    entity->free = entity_bug_free;
    entity->update = entity_bug_update;

    entity->sprite_frame = 0;
    entity->sprite = gf2d_sprite_load_all("images/space_bug_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->size.x = SPRITE_WIDTH; entity->size.y = SPRITE_HEIGHT;

    bugs_alive++;
}

void entity_bug_free(entity_t *entity)
{
    bugs_alive--;
}

void entity_bug_update(entity_t *entity)
{
    vector2d_sub(entity->velocity, player->position, entity->position);
    vector2d_normalize(&entity->velocity);
    vector2d_scale(entity->velocity, entity->velocity, BUG_SPEED);
}

size_t entity_bug_alive_count()
{
    return bugs_alive;
}