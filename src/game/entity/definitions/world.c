#include "world.h"
#include <game/game.h>
#include <game/collision/bbox.h>

void entity_world_init(entity_t *entity)
{
    entity->type = entity_type_world;
    entity->free = entity_world_free;
    entity->update = entity_world_update;
    entity->draw = entity_world_draw;
    entity->touching = entity_world_touch;
    entity->size.x = entity->size.y = 0;
}

void entity_world_free(entity_t *entity)
{

}

void entity_world_update(entity_t *entity)
{

}

void entity_world_draw(entity_t *entity)
{

}

void entity_world_touch(entity_t *entity, entity_t *other)
{

}