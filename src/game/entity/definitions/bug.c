#include <game/entity/manager.h>
#include "bug.h"
#include "player.h"
#include "plop.h"

#define ENTITY_BUG_SPEED_NORMAL 1
#define ENTITY_MIN_GLOWSTICK_RADIUS 300

#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128

entity_t *entity_bug_next_possition_collides_with_glowstick(entity_t *entity)
{
    int glowsticks = entity_plop_glowsticks_count();

    if (glowsticks == 0) {
        return NULL;
    }

    Vector2D next = entity->position;
    Vector2D velocity = entity->velocity;
    vector2d_scale(velocity, velocity, entity->speed);
    vector2d_add(next, next, velocity);


    for (int i = 0; i < glowsticks; i++) {
        Vector2D temp;
        entity_t *glowstick = entity_plop_glowsticks_get(i);
        vector2d_sub(temp, next, glowstick->position);

        if (vector2d_magnitude(temp) < ENTITY_MIN_GLOWSTICK_RADIUS)
            return glowstick;
    }

    return NULL;
}

void entity_bug_avoid_glowstick_radius(entity_t *entity)
{
    const Vector2D backup = entity->velocity;

    if (!entity_bug_next_possition_collides_with_glowstick(entity)) {
        return;
    }

    entity->velocity.x = 0;
    entity->velocity.y = backup.y;

    if (!entity_bug_next_possition_collides_with_glowstick(entity)) {
        return;
    }

    entity->velocity.x = backup.x;
    entity->velocity.y = 0;


    entity_t *glowstick = entity_bug_next_possition_collides_with_glowstick(entity);
    if (!glowstick) {
        return;
    }

    // Find the vector that points to the entity from the glowstick and use that as the new velocity
    vector2d_sub(entity->velocity, entity->position, glowstick->position);
    vector2d_normalize(&entity->velocity);
}

entity_t *entity_bug_most_valuable_entity_find(entity_t *us)
{
    int num_bags_of_chips = entity_plop_bagofchips_count();

    if (num_bags_of_chips == 0) {
        return player;
    }

    entity_t *chips = entity_plop_bagofchips_get(0);

    for (int i = 1; i < num_bags_of_chips; i++) {
        entity_t *search = entity_plop_bagofchips_get(i);

        Vector2D temp;
        vector2d_sub(temp, us->position, search->position);
        float search_distance = vector2d_magnitude(temp);
        vector2d_sub(temp, us->position, chips->position);
        float last_distance = vector2d_magnitude(temp);

        if (last_distance > search_distance) {
            chips = search;
        }
    }

    return chips;
}

void entity_bug_init(entity_t *entity)
{
    entity->type = entity_type_bug;
    entity->free = entity_bug_free;
    entity->touching = entity_bug_touching;
    entity->update = entity_bug_update;

    entity->sprite_frame = 0;
    entity->sprite = gf2d_sprite_load_all("images/space_bug_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->size.x = SPRITE_WIDTH - 30; entity->size.y = SPRITE_HEIGHT;

    entity->speed = ENTITY_BUG_SPEED_NORMAL;
    entity->health = 1;
}

void entity_bug_touching(entity_t *entity, entity_t *them)
{
    // If we're dead we can't do anything
    if (entity->health <= 0) {
        return;
    }

    // If we touched a superglue
    if (them->type == entity_type_plop && them->statuses == entity_player_status_superglue) {
        entity->speed = 0;
    }

    if (them->id == player->id) {
        printf("Bug was damaged by player touch (%li -> %li)\n", entity->id, them->id);
        //them->health -= 1;
    }
}

void entity_bug_free(entity_t *entity)
{
}

void entity_bug_update(entity_t *entity)
{
    if (entity->health <= 0) {
        entity->speed = 0.0f;
        return;
    }

    entity_t *following = entity_bug_most_valuable_entity_find(entity);
    vector2d_sub(entity->velocity, following->position, entity->position);
    vector2d_normalize(&entity->velocity);

    entity_bug_avoid_glowstick_radius(entity);
}
