#include <gf2d_sprite.h>
#include "player.h"
#include "bug.h"
#include "world.h"

#include <SDL2/SDL.h>
#include <game/game.h>
#include <simple_logger.h>
#include <game/entity/manager.h>
#include <game/collision/raytrace.h>

#define NUM_FRAMES 148
#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128

#define ENTITY_PLAYER_SPEED_SLOW    3
#define ENTITY_PLAYER_SPEED_NORMAL  5
#define ENTITY_PLAYER_SPEED_FAST   10

entity_t *player = NULL;


void entity_player_init(entity_t *entity)
{
    entity->type = entity_type_player;
    entity->free = entity_player_free;
    entity->update = entity_player_update;
    entity->draw = entity_player_draw;
    entity->touching_wall = entity_player_touching_wall;
    entity->sprite = gf2d_sprite_load_all("images/ed210_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->position.x = 10;
    entity->position.y = 10;

    entity->size.x = SPRITE_WIDTH - 20; entity->size.y = SPRITE_HEIGHT - 10;
    entity->statuses = entity_player_status_none;

    entity->position = world_first_open_position;
    entity->position.x *= TILE_SIZE_X;
    entity->position.y *= TILE_SIZE_Y;

    entity->health = 100;

    player = entity;
}

void entity_player_touching_wall(entity_t *entity, entity_touch_wall_t wall)
{
    if (entity_bug_alive_count() > 0) {
        printf("Couldn't change stages. Player still has bugs to crush\n");
        return;
    }

    printf("Player is touching wall!\n");
    Vector2D player_next_stage_pos = entity->position;

    if (wall & entity_touch_wall_top) {
        player_next_stage_pos.y = (state.view_height - entity->size.y) - 1;
    } else if (wall & entity_touch_wall_bottom) {
        player_next_stage_pos.y = 1;
    }

    if (wall & entity_touch_wall_left) {
        player_next_stage_pos.x = (state.view_width - entity->size.x) - 1;
    } else if (wall & entity_touch_wall_right) {
        player_next_stage_pos.x = 1;
    }

    entity->position = player_next_stage_pos;
}

void entity_player_free(entity_t *entity)
{
    entity_manager_make(entity_type_youdied);
}

void entity_player_update_position(Vector2D *velocity)
{
    velocity->x = velocity->y = 0;

    if (state.keys[SDL_SCANCODE_W]) {
        velocity->y -= 1;
    }

    if (state.keys[SDL_SCANCODE_S]) {
        velocity->y += 1;
    }

    if (state.keys[SDL_SCANCODE_A]) {
        velocity->x -= 1;
    }

    if (state.keys[SDL_SCANCODE_D]) {
        velocity->x += 1;
    }
}

void entity_player_update_keyboard(entity_t *entity)
{
    static bool shooting_debounce = false;

    if (state.keys[SDL_SCANCODE_SPACE]) {
        entity->statuses |= entity_player_status_speedup;
    }


    // Process shooting
    if (shooting_debounce) {
        if (!state.keys[SDL_SCANCODE_F]) {
            shooting_debounce = false;
        }
    } else if (state.keys[SDL_SCANCODE_F]) {
        shooting_debounce = true;

        int steps = 20;
        double distance = 256;
        Vector2D direction = vector2d_unit_vector_from_angle(0);
        entity_t *entity_collision;
        Vector2D tile_collision;

        entity_raytrace_collision_type type = raytrace(
                entity, entity->position, direction,
                distance, steps,
                &entity_collision, &tile_collision
        );

        switch (type) {
            case entity_raytrace_collision_entity: {
                slog("Entity was hit during a raytrace");
                break;
            }
            case entity_raytrace_collision_world: {
                Vector2D tile = entity_world_point_to_tile(&entity->position);
                printf("   Player Tile: %lf, %lf\n", tile.x, tile.y);
                printf("Collision Tile: %lf, %lf\n", tile_collision.x, tile_collision.y);
                slog("World was hit during a raytrace");
                break;
            }
            case entity_raytrace_collision_none:
            default: {
                slog("Nothing was hit during a raytrace");
                break;
            }
        }
    }
}

void entity_player_update_powerups(entity_t *entity)
{
    // Handle speed up, slow down, and normal walk speed
    if (entity->statuses & entity_player_status_slowdown) {
        entity->speed = ENTITY_PLAYER_SPEED_SLOW;
    } else if (entity->statuses & entity_player_status_speedup) {
        entity->speed = ENTITY_PLAYER_SPEED_FAST;
    } else {
        entity->speed = ENTITY_PLAYER_SPEED_NORMAL;
    }
}

void entity_player_update(entity_t *entity)
{
    entity_player_update_keyboard(entity);
    entity_player_update_powerups(entity);
    entity_player_update_position(&entity->velocity);


    if (entity->health <= 0) {
        entity_manager_release(entity);
    }
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
