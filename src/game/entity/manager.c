#include <stdio.h>
#include <simple_logger.h>
#include "manager.h"
#include <game/entity/definitions/player.h>
#include <game/entity/definitions/cursor.h>
#include <game/entity/definitions/bug.h>
#include <game/entity/definitions/background.h>
#include <game/entity/definitions/world.h>
#include <game/entity/definitions/youdied.h>
#include <game/entity/definitions/healthbar.h>
#include <game/entity/definitions/equiptment.h>
#include <game/entity/definitions/pickup.h>
#include <game/entity/definitions/throwing.h>
#include <game/entity/definitions/plop.h>
#include <game/entity/definitions/egg.h>
#include <game/entity/definitions/door.h>

struct
{
    /**
     * Number of entities that have been freed after
     * being allocated
     */
    size_t freed_entities;

    /**
     * Max number of entities within the system
     */
    size_t num_entities;

    /**
     * The next location that is free for the entity to go
     */
    size_t next_allocation_index;

    /**
     * Chunk of memory for entities
     */
    entity_t *entities;
} entity_pool;


const entity_initializer_t constructors[] = {
        NULL,

        // Actors
        entity_player_init,
        entity_bug_init,

        // UI
        entity_cursor_init,

        // Scene
        entity_background_init,
        entity_world_init,

        entity_youdied_init,
        entity_healthbar_init,
        entity_equiptment_init,
        entity_pickup_init,
        entity_throwing_init,

        entity_plop_init,

        entity_egg_init,
        entity_door_init,
};


bool entity_manager_init()
{
    entity_pool.freed_entities = 0;

    entity_pool.num_entities = MAX_NUM_ENTITIES;
    entity_pool.next_allocation_index = 0;
    entity_pool.entities = calloc(sizeof(entity_t), MAX_NUM_ENTITIES);

    for (size_t i = 0; i < entity_pool.num_entities; i++) {
        entity_pool.entities[i].id = i;
    }

    // Pre-allocate null entities
    entity_manager_for_each(entity_clear, false);

    return true;
}

entity_t *entity_manager_take(entity_initializer_t initializer)
{
    entity_t *entity = NULL;

    // We have non-compacted entities. We need to linearly search rather
    // than allocating a new entity
    for (size_t i = 0; i < entity_pool.num_entities; i++) {
        if (entity_pool.entities[i].allocated) {
            continue;
        }

        entity = &entity_pool.entities[i];
        break;
    }

    if (!entity) {
        slog("No entities were free despite freed_entities being marked as %zu", entity_pool.freed_entities);
        return NULL;
    }

    // Call initializer
    entity_clear(entity);
    initializer(entity);
    entity_post_init(entity);
    entity->allocated = true;

    return entity;
}


bool entity_manager_iterate_generator(size_t *last_entity_index, bool only_allocated, entity_t **entity)
{

    while (*last_entity_index < entity_pool.num_entities) {

        *entity = &entity_pool.entities[*last_entity_index];
        *last_entity_index += 1;

        if (only_allocated) {
            if (!(*entity)->allocated) {
                continue;
            }
        }

        return true;
    }

    return false;
}

void entity_manager_release(entity_t *entity)
{
    entity_free(entity);
    entity_pool.freed_entities++;
}

void entity_manager_for_each(entity_consumer_t consumer, bool only_allocated)
{
    size_t remaining_freed_entities = entity_pool.freed_entities;

    for (size_t i = 0; i < entity_pool.num_entities; i++) {

        // If we only want to run against allocated entities stop
        // as soon as we find a non allocated entity
        if (only_allocated) {
            if (!entity_pool.entities[i].allocated) {

                // We expected some freed entities. If we have already hit all of the freed entities
                // that we knew about then we can finally die
                if (!remaining_freed_entities) {
                    return;
                }

                // Otherwise we need to mark that we've seen a freed entity and it skip this one
                remaining_freed_entities -= 1;
                continue;
            }
        }

        // Pass to consumer
        consumer(&entity_pool.entities[i]);
    }
}

void entity_manager_update()
{
    entity_manager_for_each(entity_update, true);
    //entity_manager_collision();
}

void entity_manager_draw()
{
    entity_manager_for_each((entity_consumer_t) entity_draw, true);
}

void entity_manager_free()
{
    entity_manager_for_each((entity_consumer_t) entity_manager_release, true);
    entity_manager_init();
}
