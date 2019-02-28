#include <string.h>
#include <game/game.h>
#include <game/entity/definitions/player.h>
#include "entity.h"


void entity_clear(entity_t *e)
{
    if (!e) {
        return;
    }

    const size_t id = e->id;
    memset(e, 0, sizeof(entity_t));
    e->id = id;
}

void entity_post_init(entity_t *e)
{
    e->allocated = true;
}

void entity_free(entity_t *entity)
{
    if (entity->free) {
        entity->free(entity);
    }

    if (entity->sprite) {
        gf2d_sprite_free(entity->sprite);
    }
}

void entity_update(entity_t *entity)
{
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

    // Set the position into the entity position.
    vector2d_scale(entity->position, position, 1.0f);
}

void entity_touching_wall(entity_t *entity, entity_touch_wall_t wall)
{
    if (entity->touching_wall) {
        entity->touching_wall(entity, wall);
    }
}

void entity_touching(entity_t *entity, entity_t *other)
{
    if (entity->touching) {
        entity->touching(entity, other);
    }

    if (other->touching) {
        other->touching(other, entity);
    }
}

void entity_draw(entity_t *entity)
{
    static Vector2D position;

    if (entity->draw) {
        entity->draw(entity);
    }

    if (entity->sprite) {
        vector2d_sub(position, entity->position, player->position);
        position.x += state.render_width / 2.0f;
        position.y += state.render_height / 2.0f;

        position.x -= entity->size.x / 2.0f;
        position.y -= entity->size.y / 2.0f;

        gf2d_sprite_draw(
                entity->sprite,
                position,
                NULL,
                NULL,
                NULL,
                NULL,
                entity->has_color ? &entity->color : NULL,
                entity->sprite_frame
        );
    }
}
