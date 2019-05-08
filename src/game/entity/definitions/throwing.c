#include <game/entity/manager.h>
#include "throwing.h"


void entity_throwing_init(entity_t *entity)
{
    entity->type = entity_type_throwing;

    entity->free = entity_throwing_free;
    entity->speed = 32;

    // mark error
    entity->statuses = UINT32_MAX;
}


void entity_throwing_free(entity_t *entity)
{
    if (entity->statuses != UINT32_MAX) {
        // Drop the entity
        entity_t *dropped = entity_manager_make(entity_type_plop);
        dropped->statuses = entity->statuses;
        dropped->position = entity->position;
        dropped->roation = entity->roation;
    }
}
