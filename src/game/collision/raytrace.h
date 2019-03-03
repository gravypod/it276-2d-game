#ifndef GF2D_RAYTRACE_H
#define GF2D_RAYTRACE_H

#include <gf2d_vector.h>
#include <game/entity/entity.h>

typedef enum {
    entity_raytrace_collision_none = 0,
    entity_raytrace_collision_entity = 1,
    entity_raytrace_collision_world = 2,
} entity_raytrace_collision_type;

entity_raytrace_collision_type raytrace(
        entity_t *shooter, Vector2D position, Vector2D direction,
        double distance, int steps,
        entity_t **entity, Vector2D *tile
);

#endif

