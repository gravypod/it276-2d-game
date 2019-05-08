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
    entity->sprite = gf2d_sprite_load_image(KENNY_NL_EGG);
    entity->statuses = entity_egg_random_spawn_offset();
}
