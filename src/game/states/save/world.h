#ifndef GF2D_WORLD_H
#define GF2D_WORLD_H

#include <gf2d_vector.h>
#include <stdbool.h>


#define WORLD_TILES_X 10
#define WORLD_TILES_Y 10
#define WORLD_TILES_COUNT (WORLD_TILES_X * WORLD_TILES_Y)


typedef struct
{
    Vector2D first_open_position;
    Vector2D last_open_position;
    bool filled[WORLD_TILES_COUNT];
} save_world_t;

void save_world_dump(const char *file_name, const save_world_t *world);

bool save_world_load(const char *file_name, save_world_t *world);

#endif
