#include <string.h>
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
    if (entity->update) {
        entity->update(entity);
    }

    // Add the velocity of the player to the position to enable motion
    vector2d_add(entity->position, entity->position, entity->velocity);
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
    if (entity->draw) {
        entity->draw(entity);
    }

    if (entity->sprite) {
        gf2d_sprite_draw(
                entity->sprite,
                vector2d(entity->position.x, entity->position.y),
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                entity->sprite_frame
        );
    }
}
