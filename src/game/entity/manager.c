#include <stdio.h>
#include <simple_logger.h>
#include "manager.h"

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

bool entity_manager_init()
{
    // Before exit, call entity_manager_free
    atexit(entity_manager_free);

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

    if (entity_pool.freed_entities) {
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

        entity_pool.freed_entities -= 1;
    } else {
        // All of our entities are compactly allocated. We can take from the end
        // of our preallocated set and avoid a linear search
        if (entity_pool.num_entities < entity_pool.next_allocation_index) {
            // TODO: Slab allocation?
            slog("Ran out of entities to allocate");
            return NULL;
        }
        entity = &entity_pool.entities[entity_pool.next_allocation_index++];
    }

    // Call initializer
    entity_clear(entity);
    initializer(entity);
    entity_post_init(entity);

    return entity;
}


bool entity_manager_iterate_generator(size_t *last_entity_index, bool only_allocated, entity_t **entity)
{

    while (*last_entity_index < entity_pool.next_allocation_index) {
        *entity = &entity_pool.entities[*last_entity_index += 1];

        if (only_allocated) {
            if (!(*entity)->allocated) {
                continue;
            }
        }

        return true;
    }

    return false;
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

/*void entity_manager_collision()
{
    for (size_t self_i = 0; self_i < entity_pool.num_entities; self_i++) {
        entity_t *self = &entity_pool.entities[self_i];

        if (!self->allocated || !self->touching) {
            continue;
        }


        for (size_t checking_i = 0; checking_i < entity_pool.num_entities; checking_i++) {
            entity_t *them = &entity_pool.entities[checking_i];

            if (!them->allocated || !them->touching || self_i == checking_i) {
                continue;
            }

            if (!gf3d_collide_is_entity_touching(self, them)) {
                continue;
            }

            entity_touch(self, them);
        }
    }
}*/

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
    entity_manager_for_each((entity_consumer_t) entity_free, true);
}
