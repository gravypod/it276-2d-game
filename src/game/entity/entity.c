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

Vector2D entity_position_center(Vector2D size, Vector2D top_left)
{
    const Vector2D top_left_entity = {
            .x = top_left.x + (size.x / 2.0f),
            .y = top_left.y + (size.y / 2.0f),
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

    // Editor change. Only player can move
    if (entity->id != player->id)
        return;

    velocity = entity->velocity;

    vector2d_normalize(&velocity);
    vector2d_scale(velocity, velocity, entity->speed);

    position = entity_position_top_left(entity);
    // Add the velocity of the player to the position to enable motion
    vector2d_add(position, position, velocity);


    double min_x_pos = 0;
    double min_y_pos = 0;

    double max_x_pos = (((TILES_X - 1) * TILE_SIZE_X));
    double max_y_pos = (((TILES_Y - 1) * TILE_SIZE_Y));


    if (position.x < min_x_pos) {
        position.x = min_x_pos;
    }

    if (position.y < min_y_pos) {
        position.y = min_y_pos;
    }

    if (position.x > max_x_pos) {
        position.x = max_x_pos;
    }

    if (position.y > max_y_pos) {
        position.y = max_y_pos;
    }
    
    entity->position = entity_position_center(entity->size, position);
    
    entity_update_collision(entity);
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
                                 Uint32 frame, double rotation) {
    static Vector2D position;

    vector2d_sub(position, entity_position, player->position);
    position.x += state.render_width / 2.0f;
    position.y += state.render_height / 2.0f;

    position.x -= entity_size.x / 2.0f;
    position.y -= entity_size.y / 2.0f;

    Vector3D rotation_vector = {
            .x = entity_size.x / 2.0f,
            .y = entity_size.y / 2.0f,
            .z = rotation
    };

    gf2d_sprite_draw(
            sprite,
            position,
            NULL,
            NULL,
            &rotation_vector,
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
                                    entity->sprite_frame, entity->roation);
    }
}
