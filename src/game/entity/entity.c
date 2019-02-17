#include <string.h>
#include <game/game.h>
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

entity_touch_wall_t entity_check_touching_screen_edge(Vector2D *position, entity_t *entity, bool include_on_boarder)
{
    if (entity->size.x == 0 && entity->size.y == 0) {
        return entity_touch_wall_none;
    }

    float min_y = 0, max_y = state.view_height;
    float min_x = 0, max_x = state.view_width;

    if (include_on_boarder) {
        min_y += 1;
        min_x += 1;

        max_x -= 1;
        max_y -= 1;
    }

    Vector2D top_left = *position;
    Vector2D bottom_right = top_left;
    vector2d_add(bottom_right, bottom_right, entity->size);

    entity_touch_wall_t touching = entity_touch_wall_none;

    if (top_left.y < min_y) {
        touching |= entity_touch_wall_top;
    }

    if (top_left.x < min_x) {
        touching |= entity_touch_wall_left;
    }

    if (bottom_right.y > max_y) {
        touching |= entity_touch_wall_bottom;
    }

    if (bottom_right.x > max_x) {
        touching |= entity_touch_wall_right;
    }

    return touching;
}

void entity_clamp_within_screen(Vector2D *position, entity_t *entity)
{
    if (entity->size.x == 0 && entity->size.y == 0) {
        return;
    }

    const entity_touch_wall_t touching = entity_check_touching_screen_edge(position, entity, false);

    if (touching & entity_touch_wall_top) {
        position->y = 0.0f;
    }
    if (touching & entity_touch_wall_left) {
        position->x = 0.0f;
    }

    if (touching & entity_touch_wall_bottom) {
        position->y = state.view_height - entity->size.y;
    }

    if (touching & entity_touch_wall_right) {
        position->x = state.view_width - entity->size.x;
    }
}

void entity_update(entity_t *entity)
{
    static int i = 0;
    static Vector2D position;

    if (entity->update) {
        entity->update(entity);
    }

    // Add the velocity of the player to the position to enable motion
    vector2d_add(position, entity->position, entity->velocity);

    // TODO: Check if out of world. Then call entity_touching_wall()
    const entity_touch_wall_t touching = entity_check_touching_screen_edge(&position, entity, true);

    if (touching) {
        entity_clamp_within_screen(&position, entity);
    }

    // Set the position into the entity position.
    vector2d_scale(entity->position, position, 1.0f);

    if (touching) {
        entity_touching_wall(entity, touching);
    }
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
                entity->has_color ? &entity->color : NULL,
                entity->sprite_frame
        );
    }
}
