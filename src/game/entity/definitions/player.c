#include <gf2d_sprite.h>
#include "player.h"
#include "bug.h"
#include "world.h"
#include "equiptment.h"
#include "pickup.h"
#include "bloodsplat.h"

#include <SDL2/SDL.h>
#include <game/game.h>
#include <simple_logger.h>
#include <game/entity/manager.h>
#include <game/collision/raytrace.h>
#include <game/graphics/animation.h>
#include <game/states/world.h>
#include <game/sound/orchestra.h>

#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128

entity_t *player = NULL;
size_t touched_bug = SIZE_MAX, touched_pickup = SIZE_MAX;

void entity_player_init(entity_t *entity)
{
    entity->type = entity_type_player;
    entity->free = entity_player_free;
    entity->update = entity_player_update;
    //entity->draw = entity_player_draw;
    entity->touching = entity_player_touching;
    entity->sprite = gf2d_sprite_load_image("images/crosshairs/crosshair010.png");
    entity->position.x = 10;
    entity->position.y = 10;


    entity->roation = 0;
    entity->size.x = 64;
    entity->size.y = 64;
    entity->statuses = entity_player_status_none;

    entity->position = world_first_open_position;
    entity->position.x *= TILE_SIZE_X;
    entity->position.y *= TILE_SIZE_Y;

    entity->health = PLAYER_MAX_HEALTH;

    entity->speed = 10;
    player = entity;
}

bool key_pressed_debounced(SDL_Scancode scancode)
{
    static bool was[255] = {0};

    bool is = state.keys[scancode];

    if (was[scancode]) {
        if (!is) {
            was[scancode] = false;
        }
        return false;
    }

    was[scancode] = is;
    return is;
}

bool entity_player_interaction_drop_depressed()
{
    return key_pressed_debounced(SDL_SCANCODE_1);
}

bool entity_player_interaction_bug_depressed()
{
    return key_pressed_debounced(SDL_SCANCODE_2);
}


bool entity_player_interaction_tile_depressed()
{
    return key_pressed_debounced(SDL_SCANCODE_3);
}


bool entity_player_interaction_use_depressed()
{
    return key_pressed_debounced(SDL_SCANCODE_SPACE);
}

void entity_player_touching(entity_t *entity, entity_t *them)
{
    if (them->type == entity_type_door) {
        if (entity_player_interaction_use_depressed()) {
            printf("Setting world id: %d\n", them->statuses);
            states_world_id_set(them->statuses);
        }
    }

    if (them->type == entity_type_bug) {
        touched_bug = them->id;
    }

    if (them->type == entity_type_pickup) {
        touched_pickup = them->id;
    }
}

void entity_player_free(entity_t *entity)
{
}

Vector2D entity_player_walk_direction()
{
    const bool up = state.keys[SDL_SCANCODE_W];
    const bool left = state.keys[SDL_SCANCODE_A];
    const bool right = state.keys[SDL_SCANCODE_D];
    const bool down = state.keys[SDL_SCANCODE_S];

    Vector2D walk_direction = {0, 0};

    if (up ^ down) {
        walk_direction.y = up ? -1 : 1;
    }

    if (left ^ right) {
        walk_direction.x = right ? 1 : -1;
    }

    return walk_direction;
}

void entity_player_update_interactions(entity_t *entity)
{
    if (state.keys[SDL_SCANCODE_ESCAPE]) {
        state.running = false;
    }
}

void entity_player_update(entity_t *entity)
{
    static Vector2D last_tile = {-1, -1};
    Vector2D current_tile = entity_world_point_to_tile(&entity->position);

    if (last_tile.x != current_tile.x || last_tile.y != current_tile.y) {
        last_tile = current_tile;
        printf("Player entered tile %f, %f\n", current_tile.x, current_tile.y);
    }

    entity->velocity = entity_player_walk_direction();
    entity_player_update_interactions(entity);


    bool spawn_bug = false, spawn_pickup = false;

    touched_bug = touched_pickup = SIZE_MAX;
    if (entity_player_interaction_tile_depressed()) {
        int idx = entity_world_point_to_tile_index(&player->position);
        entity_world_toggle_index(idx);
    }

    if (entity_player_interaction_drop_depressed()) {
        entity_update_collision(entity);

        if (touched_pickup != SIZE_MAX) {
            size_t i = 0;
            entity_t *e = NULL;
            while (entity_manager_iterate_generator(&i, true, &e)) {
                if (e->id == touched_pickup) {
                    entity_manager_release(e);
                    break;
                }
            }
        } else {
            spawn_pickup = true;
        }
    }

    if (entity_player_interaction_bug_depressed()) {
        entity_update_collision(entity);

        if (touched_bug != SIZE_MAX) {
            size_t i = 0;
            entity_t *e = NULL;
            while (entity_manager_iterate_generator(&i, true, &e)) {
                if (e->id == touched_bug) {
                    entity_manager_release(e);
                    break;
                }
            }
        } else {
            spawn_bug = true;
        }
    }

    if (spawn_bug || spawn_pickup) {
        entity_t *e = NULL;

        if (spawn_bug) {
            e = entity_manager_make(entity_type_bug);
        }

        if (spawn_pickup) {
            e = entity_manager_make(entity_type_pickup);
        }

        if (e) {
            e->position = entity->position;
        }
    }
}
