#include <simple_logger.h>
#include <game/entity/definitions/world.h>
#include "point.h"

bool point_collision_with_entity(entity_t *entity, Vector2D *point)
{
    if (!entity) {
        slog("Attempted point in entity collision test with NULL pointer");
        return false;
    }

    if (!entity->allocated) {
        slog("Attempted point in entity collision test with unallocated entity");
        return false;
    }

    // If the entity has no size we don't need to test against it. It can't be collided with
    if (entity->size.x == 0 && entity->size.y == 0) {
        return false;
    }

    const Vector2D top_left = entity_position_top_left(entity);
    const bool within_x_range = (top_left.x < point->x) && (point->x < top_left.x + entity->size.x);
    const bool within_y_range = (top_left.y < point->y) && (point->y < top_left.y + entity->size.y);

    return within_x_range && within_y_range;
}

bool point_collision_with_world(Vector2D *point)
{
    Vector2D tile = entity_world_point_to_tile(point);
    return entity_world_tile_full(&tile);
}