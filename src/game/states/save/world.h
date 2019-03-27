#ifndef GF2D_STATES_SAVE_WORLD_H
#define GF2D_STATES_SAVE_WORLD_H

#include <gf2d_vector.h>
#include <stdbool.h>


#define WORLD_TILES_X 10
#define WORLD_TILES_Y 10
#define WORLD_TILES_COUNT (WORLD_TILES_X * WORLD_TILES_Y)


typedef struct {
    /**
     * First world position we borrowed to
     */
    Vector2D first_open_position;
    /**
     * Last world position we borrowed to
     */
    Vector2D last_open_position;
    /**
     * A tile map. Exists or not exists
     */
    bool filled[WORLD_TILES_COUNT];
} save_world_t;

/**
 * Save the world to disk
 * @param file_name - File to save to
 * @param world - Instance of a world save to persist
 */
void save_world_dump(const char *file_name, const save_world_t *world);

/**
 * Load the world from disk
 * @param file_name - File to load from
 * @param world - Instance of a world in memory
 * @return If the load was successful
 */
bool save_world_load(const char *file_name, save_world_t *world);

#endif
