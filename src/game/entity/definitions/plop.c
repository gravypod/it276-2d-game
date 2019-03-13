#include <game/entity/manager.h>
#include "plop.h"
#include "player.h"

void entity_plop_draw(entity_t *entity) {
    if (entity->sprite == NULL && entity->statuses == UINT32_MAX) {
        entity_manager_release(entity);
        return;
    }

    switch (entity->statuses) {
        case entity_player_status_glowstick:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_024.png");
            break;
        default:
            entity->sprite = NULL;
    }
}

void entity_plop_init(entity_t *entity) {
    entity->type = entity_type_plop;
    entity->draw = entity_plop_draw;
    entity->sprite = NULL;
    entity->statuses = UINT32_MAX;
}