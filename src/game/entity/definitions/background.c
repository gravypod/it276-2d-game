#include <simple_logger.h>
#include <gf2d_sprite.h>
#include "background.h"

entity_t *background;
Sprite *sprites[entity_background_image_last] = {NULL};

void entity_background_switch(entity_background_image_id id)
{
    if (id == entity_background_image_last) {
        slog("Attempted to set entity background to not valid value of _last");
        return;
    }

    if (!sprites[id]) {
        sprites[id] = gf2d_sprite_load_image(entity_image_files[id]);
    }

    background->sprite = sprites[id];
}

void entity_background_init(entity_t *entity)
{
    entity->type = entity_type_background;

    entity->free = entity_background_free;

    entity->position.x = 0;
    entity->position.y = 0;

    background = entity;


    entity_background_switch(entity_background_image_default);
}

void entity_background_free(entity_t *entity)
{
    for (size_t i = 0; i < entity_background_image_last; i++) {
        if (sprites[i] == NULL) {
            continue;
        }

        gf2d_sprite_free(sprites[i]);
        sprites[i] = NULL;
    }
}
