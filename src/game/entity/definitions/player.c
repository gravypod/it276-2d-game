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

#define DEG2RAD (3.14159f / 180.0f)

entity_t *player = NULL;
SDL_GameController *controller = NULL;

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


    entity->roation = 0;
    entity->size.x = SPRITE_WIDTH; entity->size.y = SPRITE_HEIGHT;
    entity->statuses = entity_player_status_none;

    entity->position = world_first_open_position;
    entity->position.x *= TILE_SIZE_X;
    entity->position.y *= TILE_SIZE_Y;

    entity->health = 100;

    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    printf("The names of the joysticks are:\n");

    if (!controller) {
        controller = SDL_GameControllerOpen(0);
        const char *name = SDL_GameControllerName(controller);
        if (name) {
            printf("Player loaded control to controller: %s\n", name);
        }
    }

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

bool entity_player_controller_pressed()
{
    const int right_trigger_dead_zone = 3000;

    static bool previously_pressed = false;

    Sint16 right_trigger_depression = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    bool currently_pressed = right_trigger_depression > right_trigger_dead_zone;

    if (currently_pressed && !previously_pressed) {
        return (previously_pressed = currently_pressed);
    }

    if (!currently_pressed && previously_pressed) {
        return (previously_pressed = false);
    }

    return false;
}

double entity_player_controller_angle()
{
    static double last_angle = 0;

    const int x_dead_zone = 3000;
    const int y_dead_zone = 3000;
    Vector2D aim_direction = {
            .x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX),
            .y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY)
    };

    if (aim_direction.x < x_dead_zone && aim_direction.x > -x_dead_zone)
        aim_direction.x = 0;

    if (aim_direction.y < y_dead_zone && aim_direction.y > -y_dead_zone)
        aim_direction.y = 0;

    vector2d_normalize(&aim_direction);


    if (aim_direction.x == 0 && aim_direction.y == 0) {
        return last_angle;
    }

    return last_angle = (vector2d_angle(aim_direction) + 90);
}

Vector2D entity_player_controller_walk_direction()
{
    const int x_dead_zone = 3000;
    const int y_dead_zone = 3000;
    Vector2D walk_direction = {
            .x = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX),
            .y = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY)
    };

    if (walk_direction.x < x_dead_zone && walk_direction.x > -x_dead_zone)
        walk_direction.x = 0;

    if (walk_direction.y < y_dead_zone && walk_direction.y > -y_dead_zone)
        walk_direction.y = 0;

    vector2d_normalize(&walk_direction);
    return walk_direction;
}

/*

    int16_t LeftTrigger = SDL_GameControllerGetAxis(p.ControllerHandle, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
*/

void entity_player_update_interactions(entity_t *entity)
{

    if (state.keys[SDL_SCANCODE_SPACE]) {
        entity->statuses |= entity_player_status_speedup;
    }


    if (entity_player_controller_pressed()) {
        Vector2D pos = entity->position;
        int steps = 10;
        Vector2D direction = vector2d_unit_vector_from_angle(
                (entity_player_controller_angle() - 90) * DEG2RAD
                );
        entity_t *entity_collision;
        Vector2D tile_collision;

        Vector2D tile_size = {TILE_SIZE_X, TILE_SIZE_Y};
        float magnitude = vector2d_magnitude(tile_size);
        raytrace_collision_t type = raytrace(
                entity, pos, direction,
                2 * magnitude, steps,
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
    entity_player_update_interactions(entity);
    entity_player_update_powerups(entity);
    entity->velocity = entity_player_controller_walk_direction();
    entity->roation = entity_player_controller_angle();

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
