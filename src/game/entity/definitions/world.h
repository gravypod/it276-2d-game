#ifndef GF2D_GAME_ENTITY_DEFINITIONS_WORLD_H
#define GF2D_GAME_ENTITY_DEFINITIONS_WORLD_H

#include <game/entity/entity.h>

#define TILES_X 10
#define TILES_Y 10
#define TILES_COUNT (TILES_X * TILES_Y)

#define TILE_SIZE_X (128 * 3)
#define TILE_SIZE_Y (128 * 3)

#define WORLD_X (TILE_SIZE_X * TILES_X)
#define WORLD_Y (TILE_SIZE_Y * TILES_Y)

extern entity_t *world;

extern Vector2D world_first_open_position, world_last_open_position;


Vector2D entity_world_position_entrance();
Vector2D entity_world_position_exit();

bool entity_world_point_collides(Vector2D *point);

Vector2D entity_world_point_to_tile(Vector2D *point);

void entity_world_init(entity_t *entity);

void entity_world_free(entity_t *entity);

void entity_world_update(entity_t *entity);

void entity_world_draw(entity_t *entity);

void entity_world_touch(entity_t *entity, entity_t *other);

bool entity_world_entity_is_colliding(entity_t *entity, Vector2D *position);

#endif
