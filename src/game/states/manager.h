#ifndef GF2D_GAME_STATE_MANAGER_H
#define GF2D_GAME_STATE_MANAGER_H

#include <game/entity/entity.h>

typedef enum  {
    game_state_none = 0,
    game_state_playing = 1,
} game_state_type;

typedef struct {
    /**
     * If we are playing within this state. Playing decides if we need to save
     */
    bool playing;
    /**
     * Number of entities needed to initialize this state
     */
    size_t num_initializers;
    /**
     * Entities to spawn.
     */
    entity_type_t initializers[];
} game_state;


/**
 * Set the game to a specific game state.
 * @param type - Game state to transition to
 */
void game_state_manager_set(game_state_type type);

#endif
