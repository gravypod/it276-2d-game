#include <string.h>
#include <game/game.h>
#include <game/entity/definitions/player.h>
#include <game/entity/definitions/world.h>
#include "entity.h"


void entity_clear(entity_t *e) {
    if (!e) {
        return;
    }

    const size_t id = e->id;
    memset(e, 0, sizeof(entity_t));
    e->id = id;
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
    }

}

void entity_touching_wall(entity_t *entity, entity_touch_wall_t wall) {
    if (entity->touching_wall) {
        entity->touching_wall(entity, wall);
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
