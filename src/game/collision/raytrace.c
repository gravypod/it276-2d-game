#include <game/entity/definitions/world.h>
#include <game/entity/manager.h>
#include "raytrace.h"
#include "point.h"

bool raytrace_collision_world(Vector2D *position, Vector2D *tile)
{
    if (!point_collision_with_world(position)) {
        return false;
    }

    if (tile) {
        *tile = entity_world_point_to_tile(position);
    }

    return true;
}

bool raytrace_collision_entity(entity_t *shooter, Vector2D *position, entity_t **e)
{
    size_t i = 0;
    entity_t *test;

    while (entity_manager_iterate_generator(&i, true, &test)) {

        if (shooter) {
            // Don't test against myself.
            if (test->id == shooter->id) {
                continue;
            }
        }

        if (!point_collision_with_entity(test, position)) {
            continue;
        }

        if (e) {
            *e = test;
        }
        return true;
    }

    return false;
}

entity_raytrace_collision_type raytrace(
        entity_t *shooter, Vector2D position, Vector2D direction,
        double distance, int steps,
        entity_t **entity, Vector2D *tile
)
{
    Vector2D step;
    vector2d_normalize(&direction);
    vector2d_scale(step, direction, distance / (double) steps);

    for (int i = 0; i <= steps; i++) {
        if (raytrace_collision_world(&position, tile)) {
            return entity_raytrace_collision_world;
        }

        if (raytrace_collision_entity(shooter, &position, entity)) {
            return entity_raytrace_collision_entity;
        }

        vector2d_add(position, position, step);
    }

    return entity_raytrace_collision_none;
}