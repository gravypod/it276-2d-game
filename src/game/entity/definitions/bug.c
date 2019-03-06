#include <game/entity/manager.h>
#include "bug.h"
#include "player.h"

#define ENTITY_BUG_SPEED_NORMAL 1

#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128

size_t bugs_alive;

void entity_bug_init(entity_t *entity)
{
    entity->type = entity_type_bug;
    entity->free = entity_bug_free;
    entity->touching = entity_bug_touching;
    entity->update = entity_bug_update;

    entity->sprite_frame = 0;
    entity->sprite = gf2d_sprite_load_all("images/space_bug_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->size.x = SPRITE_WIDTH - 30; entity->size.y = SPRITE_HEIGHT;

    entity->speed = 0; //ENTITY_BUG_SPEED_NORMAL;
    bugs_alive++;
}

void entity_bug_touching(entity_t *entity, entity_t *them)
{
    if (them->id != player->id) {
        return;
    }

    printf("Bug is touching entity (%li -> %li)\n", entity->id, them->id);
    them->health -= 999;
    entity_manager_release(entity);
}

void entity_bug_free(entity_t *entity)
{
    bugs_alive--;
}

void entity_bug_update(entity_t *entity)
{
    vector2d_sub(entity->velocity, player->position, entity->position);
    vector2d_normalize(&entity->velocity);
}

size_t entity_bug_alive_count()
{
    return bugs_alive;
}