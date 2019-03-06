#include <string.h>
#include <game/game.h>
#include <game/entity/definitions/player.h>
#include <game/entity/definitions/world.h>
#include "entity.h"
#include "manager.h"


void entity_clear(entity_t *e) {
    if (!e) {
        return;
    }

    const size_t id = e->id;
    memset(e, 0, sizeof(entity_t));
    e->id = id;
}

Vector2D entity_position_top_left(entity_t *e)
{
    const Vector2D top_left_entity = {
            .x = e->position.x - (e->size.x / 2.0f),
            .y = e->position.y - (e->size.y / 2.0f),
    };
    return top_left_entity;
}

void entity_post_init(entity_t *e) {
    e->allocated = true;
}

void entity_free(entity_t *entity) {
    if (entity->free) {
        entity->free(entity);
    }

    if (entity->sprite) {
        gf2d_sprite_free(entity->sprite);
    }

    entity->allocated = false;
}

void entity_update_collision(entity_t *entity)
{
    size_t entity_id = 0;
    entity_t *other;

    while (entity_manager_iterate_generator(&entity_id, true, &other)) {
        if (entity_id == entity->id) {
            continue;
        }


        const Vector2D top_left_entity = entity_position_top_left(entity);
        const Vector2D top_left_other = {
                .x = other->position.x - (other->size.x / 2.0f),
                .y = other->position.y - (other->size.y / 2.0f),
        };

        if (top_left_other.x < top_left_entity.x + entity->size.x &&
            top_left_other.x + other->size.x > top_left_entity.x &&
            top_left_other.y < top_left_entity.y + entity->size.y &&
            top_left_other.y + other->size.y > top_left_entity.y) {

            entity_touching(entity, other);
        }
    }
}

void entity_update(entity_t *entity) {
    static Vector2D position;
    static Vector2D velocity;

    if (entity->update) {
        entity->update(entity);
    }

    velocity = entity->velocity;

    vector2d_normalize(&velocity);
    vector2d_scale(velocity, velocity, entity->speed);

    // Add the velocity of the player to the position to enable motion
    vector2d_add(position, entity->position, velocity);

    if (entity_world_entity_is_colliding(entity, &position)) {
        Vector2D velocity_no_x = {.x = 0, .y = velocity.y};
        Vector2D velocity_no_y = {.x = velocity.x, .y = 0};

        // Try to cancel x movement.
        vector2d_add(position, entity->position, velocity_no_x);
        if (entity_world_entity_is_colliding(entity, &position)) {
            vector2d_add(position, entity->position, velocity_no_y);
        }
    }

    // Set the position into the entity position.
    if (!entity_world_entity_is_colliding(entity, &position)) {
        vector2d_scale(entity->position, position, 1.0f);
        entity_update_collision(entity);
    }

}

void entity_touching(entity_t *entity, entity_t *other) {
    if (entity->touching) {
        entity->touching(entity, other);
    }

    if (other->touching) {
        other->touching(other, entity);
    }
}

void draw_centered_around_player(Sprite *sprite, Vector2D entity_size, Vector2D entity_position, Vector4D *entity_color,
                                 Uint32 frame) {
    static Vector2D position;

    vector2d_sub(position, entity_position, player->position);
    position.x += state.render_width / 2.0f;
    position.y += state.render_height / 2.0f;

    position.x -= entity_size.x / 2.0f;
    position.y -= entity_size.y / 2.0f;

    gf2d_sprite_draw(
            sprite,
            position,
            NULL,
            NULL,
            NULL,
            NULL,
            entity_color,
            frame
    );
}

void entity_draw(entity_t *entity) {

    if (entity->draw) {
        entity->draw(entity);
    }

    if (entity->sprite) {
        draw_centered_around_player(entity->sprite, entity->size, entity->position,
                                    entity->has_color ? &entity->color : NULL,
                                    entity->sprite_frame);
    }
}
