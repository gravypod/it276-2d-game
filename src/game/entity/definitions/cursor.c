#include <gf2d_sprite.h>
#include <game/game.h>
#include <simple_logger.h>
#include "cursor.h"



void entity_cursor_init(entity_t *entity)
{
    const Vector4D color = {255, 100, 255, 200};

    entity->type = entity_type_cursor;
    entity->update = entity_cursor_update;

    slog("entity.cursor(%ul): Init", entity->id);

    entity->has_color = true;
    entity->color = color;
    entity->sprite = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
}

void entity_cursor_update(entity_t *entity)
{
    static int i = 0;

    if (i++ == 10) {
        entity->sprite_frame += 1;

        if (entity->sprite_frame >= 16) {
            entity->sprite_frame = 0;
        }
        i = 0;
    }

    entity->position.x = state.mouse_x;
    entity->position.y = state.mouse_y;

}
