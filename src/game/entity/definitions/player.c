#include <gf2d_sprite.h>
#include "player.h"

#include <SDL2/SDL.h>
#include <game/game.h>
#include <simple_logger.h>

#define NUM_FRAMES 148
Sprite *sprite_player = NULL;
Uint32 frame = 0;

void entity_player_init(entity_t *entity)
{
    entity->free = entity_player_free;
    entity->update = entity_player_update;
    entity->draw = entity_player_draw;
    if (!sprite_player) {
        sprite_player = gf2d_sprite_load_all("images/ed210_top.png", 128, 128, 16);
    }
    entity->position.x = 10;
    entity->position.y = 10;
}

void entity_player_free(entity_t *entity)
{
    if (sprite_player) {
        gf2d_sprite_free(sprite_player);
    }
}

/**
 * State machine for deciding what frame we're on
 */
void entity_player_update_animation_frame()
{
    static int i = 0;

    if (i < 3) {
        i += 1;
    } else {
        frame += 1;
        if (frame == NUM_FRAMES) {
            frame = 0;
        }
        i = 0;
    }
}

void entity_player_update_position(Vector2D *position)
{
    int move_speed = 10;

    if (state.keys[SDL_SCANCODE_W]) {
        position->y -= move_speed;
    }

    if (state.keys[SDL_SCANCODE_S]) {
        position->y += move_speed;
    }

    if (state.keys[SDL_SCANCODE_A]) {
        position->x -= move_speed;
    }

    if (state.keys[SDL_SCANCODE_D]) {
        position->x += move_speed;
    }
}

void entity_player_update(entity_t *entity)
{
    entity_player_update_animation_frame();
    entity_player_update_position(&entity->position);
}

void entity_player_draw(entity_t *entity)
{
    gf2d_sprite_draw(
            sprite_player,
            vector2d(entity->position.x, entity->position.y),
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            frame
    );
}
