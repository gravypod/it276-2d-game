#include <game/states/save/save.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdbool.h>
#include <game/states/save/em.h>
#include <game/entity/definitions/player.h>
#include <game/entity/definitions/world.h>
#include "world.h"
#include "manager.h"

#define GLOBAL_STATE_SAVE "gs.bin"

typedef struct {
    uint32_t current_world_id;
    save_entity_t player;
} global_state_t;

global_state_t save;



void save_gs_dump(const char *file_name, const global_state_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);

    FILE *file = fopen(save_name, "wb");

    fwrite(world, sizeof(global_state_t), 1, file);
    fflush(file);
    fclose(file);
}

bool save_gs_load(const char *file_name, global_state_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);

    FILE *file = fopen(save_name, "r");

    if (!file) {
        return false;
    }

    fread(world, sizeof(global_state_t), 1, file);
    fclose(file);

    return true;
}



uint32_t wid = 0;

void states_world_init()
{
    save.current_world_id = wid ;
}

uint32_t states_world_id_get()
{
    return wid ;
}

void states_world_id_set(uint32_t id)
{
    const uint32_t original_world_id = wid;
    const uint32_t next_world_id = id;

    // Make transition of worlds
    game_state_manager_set(game_state_none);
    {
        wid = save.current_world_id = id;
    }
    game_state_manager_set(game_state_playing);

    if (next_world_id > original_world_id) { // Moving deeper
        player->position = entity_world_position_entrance();
    } else { // Leaving
        player->position = entity_world_position_exit();
    }
}