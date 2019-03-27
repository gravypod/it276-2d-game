#ifndef GF2D_GAME_ENTITY_MANAGER_H
#define GF2D_GAME_ENTITY_MANAGER_H

#include <stdbool.h>
#include <stddef.h>
#include "entity.h"

#define MAX_NUM_ENTITIES 128

/**
 * Constructors for entities
 */
extern const entity_initializer_t constructors[];

/**
 * Wrap entity_manager_make with casts for simplicity
 */
#define entity_manager_make(type) entity_manager_take((entity_initializer_t) constructors[type])

/**
 * Initialize the entity pool
 * @return
 */
bool entity_manager_init();

/**
 * Find a free entity
 * @param initializer - Initialization function
 * @return
 */
entity_t *entity_manager_take(entity_initializer_t initializer);

/**
 * Incrementally iterate over the entities allocated within the entity pool. Modifies the entity pointer to contain
 * entities. Only ever look at the value of *entity if this function returns true. Otherwise this will contain bad
 * data.
 *
 * @param last_entity_index - Last index checked by this function. On first call you MUST pass 0.
 * @param only_allocated - Only included allocated entities.
 * @param entity - Pointer to pointer of entity.
 * @return true if we find another entity. False if we didn't.
 */
bool entity_manager_iterate_generator(size_t *last_entity_index, bool only_allocated, entity_t **entity);

/**
 * Release an entity back to the entity manager
 * @param entity  - Entity object
 */
void entity_manager_release(entity_t *entity);

/**
 * Run a function against every allocated entity
 * @param consumer - Consumer of entity
 * @param only_allocated - Filter to only allocated entities
 */
void entity_manager_for_each(entity_consumer_t consumer, bool only_allocated);

/**
 * Update all entities within the entity manager.
 */
void entity_manager_update();

/**
 * Draw all entities
 */
void entity_manager_draw();

/**
 * Free all entities
 */
void entity_manager_free();

#endif
