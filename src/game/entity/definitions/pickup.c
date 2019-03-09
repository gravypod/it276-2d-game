#include <simple_logger.h>
#include <game/entity/manager.h>
#include "pickup.h"
#include "player.h"

Sprite *glowstick = NULL;

void entity_pickup_init(entity_t *entity)
{
    entity->type = entity_type_pickup;
    entity->touching = entity_pickup_touching;
    entity->free = entity_pickup_free;

    // Set the type of entity to add into the player's inventory
    entity->statuses = entity_pickup_glowstick;

    switch (entity->statuses) {
        case entity_pickup_glowstick:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_024.png");
            break;
        default:
            slog("Bad pickup status selected.");
            break;
    }

    entity->size.x = entity->sprite->frame_w;
    entity->size.y = entity->sprite->frame_h;

}

void entity_pickup_touching(entity_t *entity, entity_t *them)
{
    if (them->id != player->id) {
        return;
    }

    entity_player_status_t status = entity_player_status_none;

    if (entity->statuses == entity_pickup_glowstick) {
        status = entity_player_status_glowstick;
    } else {
        return;
    }

    // Does this player already have my status?
    if (them->statuses & status) {
        return;
    }

    printf("Giving stat\n");
    them->statuses |= status;
    entity_manager_release(entity);
}

void entity_pickup_free(entity_t *entity)
{
}
