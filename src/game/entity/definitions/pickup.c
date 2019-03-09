#include <simple_logger.h>
#include <game/entity/manager.h>
#include "pickup.h"
#include "player.h"

entity_pickup_type entity_pickup_random_type() {
    entity_pickup_type types[] = {
            entity_pickup_glowstick,
            entity_pickup_superglue,
            entity_pickup_bagofchips,
            entity_pickup_leftovercoffee
    };
    int i = rand() % ((sizeof(types) / sizeof(entity_pickup_type)));
    return types[i];
}

void entity_pickup_init(entity_t *entity) {
    entity->type = entity_type_pickup;
    entity->touching = entity_pickup_touching;
    entity->free = entity_pickup_free;

    // Set the type of entity to add into the player's inventory
    entity->statuses = entity_pickup_random_type();

    switch (entity->statuses) {
        case entity_pickup_glowstick:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_024.png");
            break;
        case entity_pickup_superglue:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_103.png");
            break;
        case entity_pickup_bagofchips:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_078.png");
            break;
        case entity_pickup_leftovercoffee:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_003.png");
            break;
        default:
            slog("Bad pickup status selected.");
            break;
    }

    entity->size.x = entity->sprite->frame_w;
    entity->size.y = entity->sprite->frame_h;

}

void entity_pickup_touching(entity_t *entity, entity_t *them) {
    if (them->id != player->id) {
        return;
    }

    entity_player_status_t status;

    if (entity->statuses == entity_pickup_glowstick) {
        status = entity_player_status_glowstick;
    } else if (entity->statuses == entity_pickup_superglue) {
        status = entity_player_status_superglue;
    } else if (entity->statuses == entity_pickup_bagofchips) {
        status = entity_player_status_bagofchips;
    } else if (entity->statuses == entity_pickup_leftovercoffee) {
        status = entity_player_status_speedup;
    } else {
        return;
    }

    // Does this player already have my status?
    if (them->statuses & status) {
        return;
    }

    them->statuses |= status;
    entity_manager_release(entity);
}

void entity_pickup_free(entity_t *entity) {
}
