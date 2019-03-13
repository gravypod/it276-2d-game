#include <game/entity/manager.h>
#include "throwing.h"


void entity_throwing_init(entity_t *entity)
{
    entity->type = entity_type_throwing;

    entity->touching = entity_throwing_touching;
    entity->update = entity_throwing_update;
    entity->free = entity_throwing_free;
    entity->speed = 32;

    // mark error
    entity->statuses = UINT32_MAX;
}

void entity_throwing_touching(entity_t *entity, entity_t *them)
{
    //vector2d_scale(entity->velocity, entity->velocity, 0);
}

void entity_throwing_update(entity_t *entity)
{
    // If there was an error, ignore this
    if (entity->statuses != UINT32_MAX) {
        if (entity->speed >= 0.01) {
            entity->speed *= 0.9f;
            return;
        }
    }

    entity_manager_release(entity);
}

void entity_throwing_free(entity_t *entity)
{
    if (entity->statuses != UINT32_MAX) {
        // Drop the entity
        entity_t *dropped = entity_manager_make(entity->statuses);
        dropped->position = entity->position;
        dropped->roation = entity->roation;
    }
}
