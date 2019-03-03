#include <game/entity/manager.h>
#include "manager.h"


game_state playing = {
        .num_initializers = 3,
        .initializers = {
                entity_type_world,
                entity_type_cursor,
                entity_type_player,
        }
};

game_state *game_states[] = {
        NULL,
        &playing
};

void game_state_manager_set(game_state_type type)
{
        // Clear out every entity in the system
        entity_manager_free();

        // Find the state we want to go to
        game_state *next = game_states[type];

        if (next == NULL) {
                return;
        }

        // Create all of the entities
        for (int i = 0; i < next->num_initializers; i++) {
                entity_manager_make(next->initializers[i]);
        }
}