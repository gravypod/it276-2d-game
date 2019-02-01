#ifndef GF2D_GAME_ENTITY_ENTITY_H
#define GF2D_GAME_ENTITY_ENTITY_H

#include <stddef.h>
#include <stdbool.h>
#include <gf2d_vector.h>

/**
 * Abstract definition of an entity
 */
typedef struct entity_struct
{
    /**
     * Unique ID for every entity
     */
    size_t id;

    /**
     * Movement speed of an entity
     */
    float speed;

    /**
     * Health points of entity
     */
    long health;

    /**
     * The location in world space of the entity
     */
    Vector2D position;

    /**
     * The scale in world space of the entity
     */
    Vector2D scale;

    /**
     * The rotation, per axis, in world space of the entity.
     */
    float rotation;

    /**
     * If this entity is already being used by something
     */
    bool allocated;

    /**
     * Called to free this entity.
     */
    void (*free)(struct entity_struct *);

    /**
     * Called to update this entity
     */
    void (*update)(struct entity_struct *);

    /**
     * Called when touching another entity
     */
    void (*touching)(struct entity_struct *, struct entity_struct *);

    /**
     * Called to draw this entity
     * @param render_pass
     */
    void (*draw)(struct entity_struct *);
} entity_t;

/**
 * Abstract definition of initialization of an entity
 */
typedef void (*entity_initializer_t)(entity_t *);

/**
 * Consume and process an entity
 */
typedef void (*entity_consumer_t)(entity_t *);


/**
 * Initialize an empty entity. This is used to reset an entity to an unused state.
 *
 * @param e - Entity to blank out
 */
void entity_clear(entity_t *e);
void entity_post_init(entity_t *e);

void entity_free(entity_t *entity);
void entity_update(entity_t *entity);
void entity_touching(entity_t *entity, entity_t *other);
void entity_draw(entity_t *entity);

#endif

