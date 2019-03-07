#ifndef GF2D_GAME_STATE_MANAGER_H
#define GF2D_GAME_STATE_MANAGER_H

#include <game/entity/entity.h>

typedef enum  {
    game_state_none = 0,
    game_state_playing = 1,
} game_state_type;

typedef struct {
    char *save_file_name;
    size_t num_initializers;
    entity_type_t initializers[];
} game_state;


void game_state_manager_set(game_state_type type);

#endif
