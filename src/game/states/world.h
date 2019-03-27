#ifndef GF2D_GAME_STATES_WORLD_H
#define GF2D_GAME_STATES_WORLD_H

#include <stdint.h>

/**
 * Initialize the world state
 */
void     states_world_init();

/**
 * Change the game world state we are in
 * @param id - World ID to go to
 */
void     states_world_id_set(uint32_t id);

/**
 * Get the current World ID
 * @return id
 */
uint32_t states_world_id_get();

#endif
