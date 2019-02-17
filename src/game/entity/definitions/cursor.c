#include <gf2d_sprite.h>
#include <game/game.h>
#include <simple_logger.h>
#include "cursor.h"

#define ENTITY_CURSOR_IMAGE "images/pointer.png"

size_t references = 0;
Sprite *mouse = NULL;
Vector4D mouse_color = {255, 100, 255, 200};
float mouse_rotation = 0.0f;


void entity_cursor_init(entity_t *entity)
{
    entity->type = entity_type_cursor;
    entity->free = entity_cursor_free;
    entity->update = entity_cursor_update;
    entity->draw = entity_cursor_draw;

    slog("entity.cursor(%ul): Init", entity->id);

    if (!mouse) {
        slog("entity.cursor(%ul): Loading sprite", entity->id);
        mouse = gf2d_sprite_load_all(ENTITY_CURSOR_IMAGE, 32, 32, 16);
    }
    references += 1;
}

void entity_cursor_free(entity_t *entity)
{
    slog("entity.cursor(%ul): Freeing", entity->id);
    references -= 1;
    if (mouse && !references) {
        gf2d_sprite_free(mouse);
    }
}

void entity_cursor_update(entity_t *entity)
{
    mouse_rotation += 0.1f;

    if (mouse_rotation >= 16.0f) {
        mouse_rotation = 0.0f;
    }
}

void entity_cursor_draw(entity_t *entity)
{
    gf2d_sprite_draw(
            mouse,
            vector2d(state.mouse_x, state.mouse_y),
            NULL,
            NULL,
            NULL,
            NULL,
            &mouse_color,
            (Uint32) mouse_rotation
    );
}