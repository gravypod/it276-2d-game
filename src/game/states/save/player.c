#include <bits/types/FILE.h>
#include <stdio.h>
#include "save.h"
#include "player.h"


void save_player_dump(const char *file_name, const save_player_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);

    FILE* file = fopen(save_name, "wb");

    fwrite(world, sizeof(save_player_t), 1, file);
    fflush(file);
    fclose(file);
}

bool save_player_load(const char *file_name, save_player_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);

    FILE* file = fopen(save_name, "r");

    if (!file) {
        return false;
    }

    fread(world, sizeof(save_player_t), 1, file);
    fclose(file);

    return true;
}
