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

#define ENTITY_PLAYER_SPEED_SLOW    3
#define ENTITY_PLAYER_SPEED_NORMAL  5
#define ENTITY_PLAYER_SPEED_FAST   10

#define DEG2RAD (3.14159f / 180.0f)

entity_t *player = NULL;
SDL_GameController *controller = NULL;
Sprite *flare = NULL;
int flare_frames_left = 0;

#define NUM_ATTACKS 4

typedef struct {
    uint32_t type;
    int steps;
    float distance;
    long damage;
} attack_t;

attack_t attacks[NUM_ATTACKS] = {
        {
            .type = 0,
            .steps = 30,
            .distance = 120.0,
            .damage = 40
        },
        {
                .type = entity_player_status_weapon_2,
                .steps = 30,
                .distance = 120.0,
                .damage = 40
        },
        {
                .type = entity_player_status_weapon_3,
                .steps = 50,
                .distance = 600.0,
                .damage = 100
        },
        {
                .type = entity_player_status_weapon_4,
                .steps = 70,
                .distance = 1024.0,
                .damage = 100
        },
};

bool entity_player_should_spawn_egg_chance()
{
    const int percent_change = 25;
    const int out_of = 100;

    return (rand() % out_of) > (out_of - percent_change);
}

size_t num_bits_on(uint32_t n)
{
    size_t num = 0;
    while (n) {
        num += n & 1;
        n >>= 1;
    }
    return num;
}


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
    entity->touching = entity_player_touching;
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

    if (flare  == NULL) {
        flare = gf2d_sprite_load_image("images/muzzle/m_7.png");
    }

    player = entity;
}



bool entity_player_controller_interaction_depressed()
{
    static bool last = false;
    bool now = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);

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

void entity_player_touching(entity_t *entity, entity_t *them)
{
    if (them->type == entity_type_bug) {
        if (them->health > 0) {
            // Damage bug
            them->health -= 1;

            // If that damage killed the bug
            if (them->health <= 0) {
                entity->health -= 50; // Lose one health point for stepping on a bug
                entity->statuses |= entity_player_status_stepedon_1;

                // Spawn a bloodsplat effect on this entity.
                entity_bloodsplat_spawn(them);
            }
        }
    }

    bool interaction_depressed = entity_player_controller_interaction_depressed();

    if (them->type == entity_type_door) {
        if (interaction_depressed) {
            printf("Setting world id: %d\n", them->statuses);
            states_world_id_set(them->statuses);
        }
    }

    if (them->type == entity_type_pickup && them->statuses == entity_pickup_chest) {
        const bool has_superglue = (entity->statuses & entity_player_status_superglue) != 0;
        const bool has_bagofchips = (entity->statuses & entity_player_status_bagofchips) != 0;
        const bool has_glowstick = (entity->statuses & entity_player_status_glowstick) != 0;

        if (!(has_superglue && has_bagofchips && has_glowstick) && interaction_depressed) {
            printf("Opening a chest\n");

            if (!has_superglue) {
                entity->statuses |= entity_player_status_superglue;
            } else if (!has_bagofchips) {
                entity->statuses |= entity_player_status_bagofchips;
            } else {
                entity->statuses |= entity_player_status_glowstick;
            }

            entity_manager_release(them);
        }
    }
}

void entity_player_free(entity_t *entity)
{
    if (flare != NULL) {
        gf2d_sprite_free(flare);
        flare = NULL;
    }
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


    if (state.keys[SDL_SCANCODE_SPACE]) {
        entity->statuses |= entity_player_status_stepedon_1;
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


void entity_player_stepon_update(entity_t *entity)
{

#define NUM_TICKS_TO_TRANISITION_STEPON 1000

    static int ticks_since_step_on = 0;
    const uint32_t step_on_bits = entity_player_status_stepedon_1 | entity_player_status_stepedon_2 | entity_player_status_stepedon_3;

    const uint32_t shared_step_on_bits = entity->statuses & step_on_bits;

    // If the player hasn't steped on anything, ignore
    if (shared_step_on_bits == 0) {
        ticks_since_step_on = 0;
        return;
    }

    // More than one stepon state was set.
    // Force back to stepon 1
    if (num_bits_on(shared_step_on_bits) > 1) {
        entity->statuses |= (entity->statuses & ~step_on_bits) | entity_player_status_stepedon_1;
        return;
    }

    // The player has stepped on a bug but enough time hasn't passed to transition states yet
    if (ticks_since_step_on < NUM_TICKS_TO_TRANISITION_STEPON) {
        ticks_since_step_on += 1;
        return;
    }

    ticks_since_step_on = 0;

    // Update state machine
    switch (shared_step_on_bits) {
        case entity_player_status_stepedon_1:
            // Transition states 1->2
            entity->statuses &= ~entity_player_status_stepedon_1;
            entity->statuses |= entity_player_status_stepedon_2;
            printf("Player Stepped On 1->2\n");
            break;
        case entity_player_status_stepedon_2:
            // Transition states 2->3
            entity->statuses &= ~entity_player_status_stepedon_2;
            entity->statuses |= entity_player_status_stepedon_3;
            printf("Player Stepped On 2->3\n");
            break;
        case entity_player_status_stepedon_3:
            entity->statuses &= ~entity_player_status_stepedon_3;
            printf("Player Stepped On 3->nothing\n");
            break;
        default:
            printf("Player Stepped On Error. Shouldn't be able to get into state machine update with no initial bit\n");
            // Recover from magic error. Shouldn't ever reach this case
            entity->statuses &= ~step_on_bits;
            return;
    }

    if (entity_player_should_spawn_egg_chance()) {
        // Make an egg in the player's position
        entity_t *egg = entity_manager_make(entity_type_egg);
        egg->position = player->position;
        printf("Player: Tracking bug because of state change.\n");
    } else {
        printf("Player: Not tracking a bug.\n");
    }
}

void entity_player_update(entity_t *entity)
{
    entity->statuses |= entity_player_status_weapon_4;
    entity_player_update_powerups(entity);
    entity->velocity = entity_player_controller_walk_direction();
    entity->roation = entity_player_controller_angle();
    entity_player_update_interactions(entity);
    entity_player_stepon_update(entity);

    if (entity->health <= 0) {
        entity_manager_release(entity);
    }


    // Remove slowdown effect after applying update.
    // This will be reapplied if the player is still on broken glass
    entity->statuses &= ~entity_player_status_slowdown;

    orchestra_instrument_set(ORCHESTRA_FOOTSTEPS, fabsf(vector2d_magnitude(entity->velocity)) > 0);

    if (entity_player_controller_attack_depressed()) {
        if (entity->statuses & entity_player_status_weapon_4) {
            orchestra_instrument_set(ORCHESTRA_MACHINE_GUNSHOT, true);
        } else if (entity->statuses & entity_player_status_weapon_3) {
            orchestra_instrument_set(ORCHESTRA_GUNSHOT, true);
        }
    } else {
        orchestra_instrument_set(ORCHESTRA_MACHINE_GUNSHOT, false);
        orchestra_instrument_set(ORCHESTRA_GUNSHOT, false);
    }
}



void entity_player_fight()
{
    attack_t attack = attacks[0];

    for (int i = 0; i < NUM_ATTACKS; i++) {
        if (player->statuses & attacks[i].type) {
            attack = attacks[i];
        }
    }

    if (player->statuses & entity_player_status_weapon_4) {
        flare_frames_left = 25;
    } else if (player->statuses & entity_player_status_weapon_3) {
        flare_frames_left = 25;
    }

    entity_t *hit = entity_player_attack(attack.distance, attack.steps);

    if (hit && hit->type == entity_type_bug && hit->health > 0) {

        hit->health -= attack.damage;

        if (hit->health <= 0) {
            hit->health = 0;

            // Spawn a bloodsplat effect on this entity.
            entity_bloodsplat_spawn(hit);

            Vector4D color = {0,0,0,255};

            if (player->statuses & entity_player_status_weapon_4) {
                color.x = 255;
                hit->has_color = true;
                hit->color = color;
            } else if (player->statuses & entity_player_status_weapon_3) {
                color.y = 255;
                hit->has_color = true;
                hit->color = color;
            } else if (player->statuses & entity_player_status_weapon_2) {
                color.z = 255;
                hit->has_color = true;
                hit->color = color;
            }

            // After 1 kill, get weapon 2. After 1 more kill get weapon 3.
            if (!(player->statuses & entity_player_status_weapon_2)) {
                player->statuses |= entity_player_status_weapon_2;
            } else if (!(player->statuses & entity_player_status_weapon_3)) {
                player->statuses |= entity_player_status_weapon_3;
            } else if (!(player->statuses & entity_player_status_weapon_4)) {
                player->statuses |= entity_player_status_weapon_4;
            }
        }

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

    uint32_t player_status = entity_equiptment_slot_type(slot);

    if (!(player->statuses & player_status)) {
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
    thrown->statuses = player_status;

    // Remove from inventory
    player->statuses &= ~player_status;

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
    static animation_t *torso_attack_animation = &player_body_punch_walk;
    static animation_t *torso_walking_animation = &player_body_flashlight_walk;
    static animation_t *torso_idle_animation = &player_body_flashlight_idle;

    // Chose the right animation set for the player
    if (player->statuses & entity_player_status_weapon_4) {
        torso_attack_animation = &player_body_rifle_shoot;
        torso_walking_animation = &player_body_rifle_move;
        torso_idle_animation = &player_body_rifle_idle;
    } else if (player->statuses & entity_player_status_weapon_3) {
        torso_attack_animation = &player_body_handgun_shoot;
        torso_walking_animation = &player_body_handgun_move;
        torso_idle_animation = &player_body_handgun_idle;
    } else if (player->statuses & entity_player_status_weapon_2) {
        torso_attack_animation = &player_body_knife_meleeattack;
        torso_walking_animation = &player_body_knife_move;
        torso_idle_animation = &player_body_knife_idle;
    } else {
        torso_attack_animation = &player_body_punch_walk;
        torso_walking_animation = &player_body_flashlight_walk;
        torso_idle_animation = &player_body_flashlight_idle;
    }

    {
        const animation_t *current = moving ? torso_walking_animation : torso_idle_animation;
        void (*action)() = NULL;

        if (entity_player_controller_throw_depressed()) {
            action = entity_player_throw;
            current = torso_attack_animation;
        } else if (entity_player_controller_attack_depressed()) {
            current = torso_attack_animation;
            action = entity_player_fight;
        }

        animation_render(entity, current, &torso, action);

        if (flare_frames_left > 0) {
            flare_frames_left -= 1;
            Vector2D size = {flare->frame_w, flare->frame_h};


            Vector2D position = player->position;
            Vector2D direction = vector2d_unit_vector_from_angle((player->roation - 90) * DEG2RAD);
            vector2d_scale(direction, direction, 230);
            vector2d_add(position, position, direction);

            Vector2D correction = vector2d_unit_vector_from_angle((player->roation) * DEG2RAD);
            vector2d_scale(correction, correction, 55);
            vector2d_add(position, position, correction);

            Vector4D color_shift = {
                    255, 255, 255, (255 * (((float)flare_frames_left) / 10.0f))
            };

            draw_centered_around_player(flare, size, position, &color_shift, 0, player->roation - 90);
        }
    }

}
