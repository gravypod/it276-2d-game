#include <simple_logger.h>
#include <game/entity/manager.h>
#include <game/kennynl.h>
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
            entity_pickup_fire,
            entity_pickup_chest,
    };
    int i = rand() % ((sizeof(types) / sizeof(entity_pickup_type)));
    return types[i];
}


void entity_pickup_update(entity_t *entity)
{
    switch (entity->statuses) {
        case entity_pickup_glowstick:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(024));
            break;
        case entity_pickup_superglue:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(103));
            break;
        case entity_pickup_bagofchips:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(078));
            break;
        case entity_pickup_leftovercoffee:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(003));
            break;
        case entity_pickup_wettowel:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(031));
            break;
        case entity_pickup_brokenglass:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(044));
            break;
        case entity_pickup_fire:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(027));
            break;
        case entity_pickup_chest:
            entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(036));
            break;
        default:
            slog("Bad pickup status selected.");
            break;
    }

    entity->size.x = entity->sprite->frame_w;
    entity->size.y = entity->sprite->frame_h;
    entity->update = NULL;
}

void entity_pickup_init(entity_t *entity) {
    entity->type = entity_type_pickup;
    entity->free = entity_pickup_free;
    entity->update = entity_pickup_update;

    // Set the type of entity to add into the player's inventory
    entity->statuses = entity_pickup_random_type();
    entity->sprite = NULL;


}

void entity_pickup_free(entity_t *entity) {
}
