#ifndef GF2D_WORLD_H
#define GF2D_WORLD_H

#include <gf2d_vector.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct
{
    Vector2D position;
    double rotation;
    uint32_t statuses;
    long health;
} save_player_t;

void save_player_dump(const char *file_name, const save_player_t *world);

bool save_player_load(const char *file_name, save_player_t *world);

#endif
