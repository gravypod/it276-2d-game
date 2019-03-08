#include <game/entity/manager.h>
#include <game/states/save/em.h>
#include <game/entity/definitions/player.h>
#include "manager.h"


game_state playing = {
        .save_file_name = "game.bin",
        .num_initializers = 5,
        .initializers = {
                entity_type_world,
                entity_type_cursor,
                entity_type_player,
                entity_type_youdied,
                entity_type_healthbar
        }
};

game_state *game_states[] = {
        NULL,
        &playing
};

void game_state_persist_entities(char *file_name)
{
    save_em_t save;
    size_t i = 0;

    memset(&save, 0, sizeof(save));

    size_t entity_id = 0;
    entity_t *entity;

    while (entity_manager_iterate_generator(&entity_id, true, &entity)) {
        printf("\tPersisting %d\n", entity->type);
        save_entity_t *save_entity = &save.entities[i++];

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

    save_em_dump(file_name, &save);
}


bool game_state_load_entities(char *file_name)
{
    save_em_t save;
    if (!save_em_load(file_name, &save)) {
        return false;
    }

    for (size_t i = 0; i < MAX_NUM_ENTITIES; i++) {
        const save_entity_t *saved = &save.entities[i];

        if (!saved->allocated) {
            continue;
        }

        printf("\tMaking %d\n", saved->type);

        entity_t *entity = entity_manager_make(saved->type);

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

    return true;
}

bool game_state_should_save(game_state_type current, game_state_type next) {
    if (current == game_state_playing && player->health > 0) {
        return true;
    }
    return false;
}

void game_state_manager_set(game_state_type type)
{
    static game_state_type current_type = game_state_none;

    // Find the state we want to go to
    game_state *current = game_states[current_type];
    game_state *next = game_states[type];

    // Save current state
    if (current != NULL && current->save_file_name != NULL) {
        if (game_state_should_save(current_type, type)) {
            game_state_persist_entities(current->save_file_name);
        }
    }

    current_type = type;

    // Clear out every entity in the system
    entity_manager_free();


    if (next == NULL) {
        return;
    }

    if (next->save_file_name) {
        printf("Loading all entities from file\n");
        if (game_state_load_entities(next->save_file_name)) {
            printf("Loaded all entities from file\n");
            // loaded entities from file.
            return;
        }
    }

    // Create all of the entities
    for (int i = 0; i < next->num_initializers; i++) {
        entity_manager_make(next->initializers[i]);
    }
}