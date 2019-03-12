#include <simple_logger.h>
#include <game/entity/manager.h>
#include "pickup.h"
#include "player.h"

entity_pickup_type entity_pickup_random_type() {
    entity_pickup_type types[] = {
            entity_pickup_glowstick,
            entity_pickup_superglue,
            entity_pickup_bagofchips,
            entity_pickup_leftovercoffee,
            entity_pickup_wettowel,
            entity_pickup_brokenglass,
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
        case entity_pickup_wettowel:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_031.png");
            break;
        case entity_pickup_brokenglass:
            entity->sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_044.png");
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

    bool release = true;

    if (entity->statuses == entity_pickup_wettowel) {
        long increment = PLAYER_MAX_HEALTH / 10;

        if (them->health + increment > PLAYER_MAX_HEALTH) {
            return;
        }

        them->health += increment;
    } else {
        entity_player_status_t status;

        if (entity->statuses == entity_pickup_glowstick) {
            status = entity_player_status_glowstick;
        } else if (entity->statuses == entity_pickup_superglue) {
            status = entity_player_status_superglue;
        } else if (entity->statuses == entity_pickup_bagofchips) {
            status = entity_player_status_bagofchips;
        } else if (entity->statuses == entity_pickup_leftovercoffee) {
            status = entity_player_status_speedup;
        } else if (entity->statuses == entity_pickup_brokenglass) {
            status = entity_player_status_slowdown;
            // Broken glass will remain on the floor even after a player walks over it
            release = false;
        } else {
            return;
        }

        // Does this player already have my status?
        if (them->statuses & status) {
            return;
        }

        them->statuses |= status;
    }

    if (release) {
        entity_manager_release(entity);
    }
}

void entity_pickup_free(entity_t *entity) {
}
