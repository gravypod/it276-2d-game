#include <game/kennynl.h>
#include <game/entity/manager.h>
#include "egg.h"

#define ENTITY_EGG_MAX_SPAWN_TIME 2000

uint32_t entity_egg_random_spawn_offset()
{
    const int min = 1000;
    const int max = ENTITY_EGG_MAX_SPAWN_TIME;
    return (uint32_t) (rand() % max + min);
}

void entity_egg_init(entity_t *entity)
{
    entity->type = entity_type_egg;
    entity->update = entity_egg_update;
    entity->sprite = gf2d_sprite_load_image(KENNY_NL_EGG);
    entity->statuses = entity_egg_random_spawn_offset();
}

void entity_egg_update(entity_t *entity)
{
    if (entity->statuses == 0 || entity->statuses > (2 * ENTITY_EGG_MAX_SPAWN_TIME)) {
        printf("Spawning bug from egg\n");
        entity_t *bug = entity_manager_make(entity_type_bug);
        bug->position = entity->position;

        entity_manager_release(entity);
    } else {
        entity->statuses -= 1;
    }
}