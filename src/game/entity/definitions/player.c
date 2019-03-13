#include <gf2d_sprite.h>
#include "player.h"
#include "bug.h"
#include "world.h"
#include "equiptment.h"

#include <SDL2/SDL.h>
#include <game/game.h>
#include <simple_logger.h>
#include <game/entity/manager.h>
#include <game/collision/raytrace.h>
#include <game/graphics/animation.h>

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
            .distance = 120.0,
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
    //entity->sprite = gf2d_sprite_load_all("images/ed210_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->position.x = 10;
    entity->position.y = 10;


    entity->roation = 0;
    entity->size.x = SPRITE_WIDTH; entity->size.y = SPRITE_HEIGHT;
    entity->statuses = entity_player_status_none;

    entity->position = world_first_open_position;
    entity->position.x *= TILE_SIZE_X;
    entity->position.y *= TILE_SIZE_Y;

    entity->health = PLAYER_MAX_HEALTH;

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

bool entity_player_controller_lb_depressed()
{
    static bool last = false;
    bool now = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);

    if (now ^ last) {
        if (last) {
            last = false;
            return false;
        }

        if (now) {
            last = true;
            return true;
        }
    } else {
        return false;
    }
}


bool entity_player_controller_rb_depressed()
{
    static bool last = false;
    bool now = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    if (now ^ last) {
        if (last) {
            last = false;
            return false;
        }

        if (now) {
            last = true;
            return true;
        }
    } else {
        return false;
    }
}

bool entity_player_controller_throw_depressed()
{
    const int trigger_dead_zone = 3000;

    Sint16 right_trigger_depression = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    bool currently_pressed = right_trigger_depression > trigger_dead_zone;

    return currently_pressed;
}

bool entity_player_controller_attack_depressed()
{
    const int trigger_dead_zone = 3000;

    Sint16 right_trigger_depression = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    bool currently_pressed = right_trigger_depression > trigger_dead_zone;

    return currently_pressed;
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

    if (entity_player_controller_rb_depressed()) {
        entity_equiptment_selection_right();
    }

    if (entity_player_controller_lb_depressed()) {
        entity_equiptment_selection_left();
    }
}

void entity_player_update_powerups(entity_t *entity)
{
    // Handle speed up, slow down, and normal walk speed
    const bool slow = (entity->statuses & entity_player_status_slowdown) != 0;
    const bool fast = (entity->statuses & entity_player_status_speedup) != 0;

    if (slow ^ fast) {
        if (slow) {
            entity->speed = ENTITY_PLAYER_SPEED_SLOW;
        }
        if (fast) {
            entity->speed = ENTITY_PLAYER_SPEED_FAST;
        }
    }  else {
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


    // Remove slowdown effect after applying update.
    // This will be reapplied if the player is still on broken glass
    entity->statuses &= ~entity_player_status_slowdown;
}



void entity_player_fight()
{
    const int current_attack = 0;
    const attack_t attack = attacks[current_attack];
    entity_t *hit = entity_player_attack(attack.distance, attack.steps);

    if (hit) {
        hit->health -= attack.damage;
    }

    printf("Player is fighting\n");
}

void entity_player_throw()
{
    const int slot = entity_equiptment_selection();
    if (slot == -1) {
        printf("Player doesn't have any equiptment\n");
        return;
    }

    Vector2D direction = vector2d_unit_vector_from_angle((player->roation - 90) * DEG2RAD);
    Vector2D position;
    vector2d_scale(position, direction, 128);
    vector2d_add(position, player->position, position);

    entity_t *thrown = entity_manager_make(entity_type_throwing);
    thrown->position = position;
    thrown->velocity = direction;
    thrown->sprite = entity_equiptment_slot_sprite(slot);
    thrown->statuses = entity_type_bug;

    printf("Player is throwing\n");
}


void entity_player_draw(entity_t *entity)
{
    const bool moving = vector2d_magnitude(entity->velocity) > 0;

    // Animation feet
    static animation_state_t feet = {0};
    static const animation_t *feet_walking_animation = &player_feet_walk;
    static const animation_t *feet_idle_animation = &player_feet_idle;

    {
        const animation_t *current = moving ? feet_walking_animation : feet_idle_animation;
        animation_render(entity, current, &feet, NULL);
    }

    // Animate torso
    static animation_state_t torso = {0};
    static const animation_t *torso_punch_animation = &player_body_punch_walk;
    static const animation_t *torso_walking_animation = &player_body_flashlight_walk;
    static const animation_t *torso_idle_animation = &player_body_flashlight_idle;

    {
        const animation_t *current = moving ? torso_walking_animation : torso_idle_animation;
        void (*action)() = NULL;

        if (entity_player_controller_throw_depressed()) {
            action = entity_player_throw;
            current = torso_punch_animation;
        } else if (entity_player_controller_attack_depressed()) {
            action = entity_player_fight;
            current = torso_punch_animation;
        }

        animation_render(entity, current, &torso, action);
    }

}
