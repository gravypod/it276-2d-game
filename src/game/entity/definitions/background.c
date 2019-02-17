#include <simple_logger.h>
#include <gf2d_sprite.h>
#include "background.h"


Sprite *sprites[entity_background_image_last] = {NULL};
entity_background_image_id current;
bool loaded = false;

void entity_background_switch(entity_background_image_id id)
{
    if (id == entity_background_image_last) {
        slog("Attempted to set entity background to not valid value of _last");
        return;
    }

    if (!sprites[id]) {
        sprites[id] = gf2d_sprite_load_image(entity_image_files[id]);
    }
    current = id;
}

void entity_background_init(entity_t *entity)
{
    entity->type = entity_type_background;
    if (!loaded) {
        entity_background_switch(entity_background_image_default);
        loaded = true;
    }

    entity->free = entity_background_free;
    entity->draw = entity_background_draw;
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


void entity_background_draw(entity_t *entity)
{
    gf2d_sprite_draw_image(sprites[current], vector2d(0, 0));
}
