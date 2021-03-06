#include <game/entity/manager.h>
#include <game/states/save/em.h>
#include <game/entity/definitions/player.h>
#include "manager.h"


game_state playing = {
        .playing = true,
        .num_initializers = 6,
        .initializers = {
                entity_type_world,
                entity_type_cursor,
                entity_type_player,
                entity_type_youdied,
                entity_type_healthbar,
                entity_type_equiptment,
        }
};

game_state *game_states[] = {
        NULL,
        &playing
};

void game_state_persist_entities()
{
    save_em_t save;
    size_t i = 0;

    memset(&save, 0, sizeof(save));

    size_t entity_id = 0;
    entity_t *entity;

    while (entity_manager_iterate_generator(&entity_id, true, &entity)) {
        printf("\tPersisting %d\n", entity->type);
        save_entity_t *save_entity = &save.entities[i++];
        save_em_entity_to_save_entity(entity, save_entity);
    }

    save_em_dump("entites-%d.bin", &save);
}


bool game_state_load_entities()
{
    save_em_t save;
    if (!save_em_load("entites-%d.bin", &save)) {
        return false;
    }

    bool made_a_player = false, made_a_world = false;

    for (size_t i = 0; i < MAX_NUM_ENTITIES; i++) {
        save_entity_t *saved = &save.entities[i];

        if (!saved->allocated) {
            continue;
        }

        printf("\tMaking %d - %d @ (%f, %f)\n", saved->type, saved->statuses, saved->position.x, saved->position.y);

        if (saved->type == entity_type_player) {
            made_a_player = true;
        }

        if (saved->type == entity_type_world) {
            made_a_world = true;
        }

        entity_t *entity = entity_manager_make(saved->type);

        save_em_save_entity_to_entity(saved, entity);
    }

    if (!made_a_world) {
        entity_manager_make(entity_type_world);
    }
    if (!made_a_player) {
        entity_manager_make(entity_type_player);
    }


    return true;
}

bool game_state_should_save(game_state_type current, game_state_type next) {
    if (current == game_state_playing && PLAYER_ALIVE()) {
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
    if (current != NULL && current->playing) {
        if (game_state_should_save(current_type, type)) {
            game_state_persist_entities();
        }
    }

    current_type = type;

    // Clear out every entity in the system
    entity_manager_free();


    if (next == NULL) {
        return;
    }

    if (next->playing) {
        printf("Loading all entities from file\n");
        if (game_state_load_entities()) {
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