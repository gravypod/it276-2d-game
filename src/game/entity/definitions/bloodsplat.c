#include <game/entity/manager.h>
#include "bloodsplat.h"

#define NUM_BLOODSPLATS 7

char *bloodsplat_file_names[NUM_BLOODSPLATS] = {
        "images/blood/bloodsplats/bloodsplats_0001.png",
        "images/blood/bloodsplats/bloodsplats_0002.png",
        "images/blood/bloodsplats/bloodsplats_0003.png",
        "images/blood/bloodsplats/bloodsplats_0004.png",
        "images/blood/bloodsplats/bloodsplats_0005.png",
        "images/blood/bloodsplats/bloodsplats_0006.png",
        "images/blood/bloodsplats/bloodsplats_0007.png",
};
Sprite *bloodsplat_sprites[NUM_BLOODSPLATS] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL};


void entity_bloodsplat_spawn(entity_t *target)
{
    entity_t *entity = entity_manager_make(entity_type_bloodsplat);
    entity->position = target->position;
    entity->position.x -= target->size.x / 2;
    entity->position.y -= target->size.y / 2;
}

void entity_bloodsplat_ensure_images_loaded()
{
    for (int i = 0; i < 7; i++) {
        if (bloodsplat_sprites[i]) {
            continue;
        }
        bloodsplat_sprites[i] = gf2d_sprite_load_image(bloodsplat_file_names[i]);
    }
}

void entity_bloodsplat_init(entity_t *entity)
{
    entity->type = entity_type_bloodsplat;
    entity->update = entity_bloodsplat_update;

    entity_bloodsplat_ensure_images_loaded();
}

void entity_bloodsplat_update(entity_t *entity)
{
    if (entity->statuses == 0) {
        // Randomly select a bloodsplat
        entity->statuses = (rand() % 6) + 1;
    }

    if (entity->sprite == NULL) {
        entity->sprite = bloodsplat_sprites[entity->statuses - 1];
    }

    // Make sure we're never moving
    entity->velocity.x = 0;
    entity->velocity.y = 0;
}