#include <game/states/world.h>
#include "em.h"
#include "save.h"

void save_em_save_entity_to_entity(save_entity_t *saved, entity_t *entity)
{
    // Reload entity contents
    entity->type = saved->type;
    entity->health = saved->health;
    entity->statuses = saved->statuses;
    entity->size = saved->size;
    entity->sprite_frame = saved->sprite_frame;
    entity->has_color = saved->has_color;
    entity->color = saved->color;
    entity->position = saved->position;
    entity->roation = saved->roation;
    entity->velocity = saved->velocity;
    entity->speed = saved->speed;
}

void save_em_entity_to_save_entity(entity_t *entity, save_entity_t *save_entity)
{
    // Entity manager metadata
    save_entity->allocated = true;
    save_entity->type = entity->type;

    save_entity->health = entity->health;
    save_entity->statuses = entity->statuses;

    save_entity->size = entity->size;
    save_entity->sprite_frame = entity->sprite_frame;
    save_entity->has_color = entity->has_color;
    save_entity->color = entity->color;

    save_entity->position = entity->position;
    save_entity->roation = entity->roation;
    save_entity->velocity = entity->velocity;
    save_entity->speed = entity->speed;
}

void save_em_dump(const char *file_name, const save_em_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);
    sprintf(save_name, save_name, states_world_id_get());

    printf("Saving entities for world id '%d' into file '%s'\n", states_world_id_get(), save_name);

    FILE *file = fopen(save_name, "wb");



    fwrite(world, sizeof(save_em_t), 1, file);
    fflush(file);
    fclose(file);
}

bool save_em_load(const char *file_name, save_em_t *world)
{
    static char save_name[512];
    save_folder_name(file_name, save_name);
    sprintf(save_name, save_name, states_world_id_get());

    printf("Loading entities for world id '%d' from file '%s'\n", states_world_id_get(), save_name);

    FILE *file = fopen(save_name, "r");

    if (!file) {
        return false;
    }

    fread(world, sizeof(save_em_t), 1, file);
    fclose(file);

    return true;
}

