#include <game/entity/manager.h>
#include "plop.h"
#include "player.h"
#include "equiptment.h"

void entity_plop_draw(entity_t *entity) {
    if (entity->sprite == NULL && entity->statuses == UINT32_MAX) {
        entity_manager_release(entity);
        return;
    }

    int slot = entity_equiptment_status_to_slot(entity->statuses);
    entity->sprite = entity_equiptment_slot_sprite(slot);
}

void entity_plop_init(entity_t *entity) {
    entity->type = entity_type_plop;
    entity->draw = entity_plop_draw;
    entity->sprite = NULL;
    entity->statuses = UINT32_MAX;
}