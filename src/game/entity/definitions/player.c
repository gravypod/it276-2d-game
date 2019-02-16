#include <gf2d_sprite.h>
#include "player.h"

#include <SDL2/SDL.h>
#include <game/game.h>
#include <simple_logger.h>

#define NUM_FRAMES 148

void entity_player_init(entity_t *entity)
{
    entity->free = entity_player_free;
    entity->update = entity_player_update;
    entity->draw = entity_player_draw;
    entity->sprite = gf2d_sprite_load_all("images/ed210_top.png", 128, 128, 16);
    entity->position.x = 10;
    entity->position.y = 10;
}

void entity_player_free(entity_t *entity)
{
}

void entity_player_update_position(Vector2D *velocity)
{
    int move_speed = 10;

    velocity->x = velocity->y = 0;

    if (state.keys[SDL_SCANCODE_W]) {
        velocity->y -= move_speed;
    }

    if (state.keys[SDL_SCANCODE_S]) {
        velocity->y += move_speed;
    }

    if (state.keys[SDL_SCANCODE_A]) {
        velocity->x -= move_speed;
    }

    if (state.keys[SDL_SCANCODE_D]) {
        velocity->x += move_speed;
    }
}

void entity_player_update(entity_t *entity)
{
    entity_player_update_position(&entity->velocity);
}

void entity_player_draw(entity_t *entity)
{
    static int i = 0;

    if (i++ < 3) {
        return;
    }

    if (++entity->sprite_frame == NUM_FRAMES) {
        entity->sprite_frame = 0;
    }

    i = 0;
}
