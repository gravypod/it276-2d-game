#ifndef GF2D_GAME_ENTITY_DEFINITIONS_BACKGROUND_H
#define GF2D_GAME_ENTITY_DEFINITIONS_BACKGROUND_H

#include <game/entity/entity.h>

typedef enum
{
    entity_background_image_default = 0,
    entity_background_image_last = 1
} entity_background_image_id;

static char *entity_image_files[entity_background_image_last] = {
        "images/backgrounds/bg_flat.png"
};

void entity_background_switch(entity_background_image_id id);
void entity_background_init(entity_t *entity);
void entity_background_free(entity_t *entity);
void entity_background_draw(entity_t *entity);

#endif
