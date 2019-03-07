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


#define NUM_ATTACKS 1

typedef struct {
    int steps;
    float distance;
    long damage;
} attack_t;

attack_t attacks[NUM_ATTACKS] = {
        {
            .steps = 30,
            .distance = ((SPRITE_HEIGHT * 1.2f) / 4.0f),
            .damage = 40
        }
};


entity_t *entity_player_attack(float distance, const int steps) {
    entity_t *hit;
    const raytrace_collision_t type = raytrace(
            player, player->position,
            vector2d_unit_vector_from_angle((player->roation - 90) * DEG2RAD),
            distance, steps,
            &hit,
            NULL
    );

    if (type != entity_raytrace_collision_entity) {
        return NULL;
    }

    printf("Attack and hit %zu\n", hit->id);

    return hit;
}

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
}

void entity_player_free(entity_t *entity)
{
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
    static bool initialized = false;
    static double last_angle = 0;

    if (!initialized) {
        last_angle = player->roation;
        initialized = true;
    }

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

void entity_player_update_interactions(entity_t *entity)
{

    if (state.keys[SDL_SCANCODE_ESCAPE]) {
        state.running = false;
    }

    if (state.keys[SDL_SCANCODE_SPACE]) {
        entity->statuses |= entity_player_status_speedup;
    }


    if (entity_player_controller_pressed()) {
        const int current_attack = 0;
        const attack_t attack = attacks[current_attack];
        entity_t *hit = entity_player_attack(attack.distance, attack.steps);

        if (hit) {
            hit->health -= attack.damage;
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
    entity_player_update_powerups(entity);
    entity->velocity = entity_player_controller_walk_direction();
    entity->roation = entity_player_controller_angle();
    entity_player_update_interactions(entity);

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
