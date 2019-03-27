#ifndef GF2D_GAME_ENTITY_ENTITY_H
#define GF2D_GAME_ENTITY_ENTITY_H

#include <stddef.h>
#include <stdbool.h>
#include <gf2d_vector.h>
#include <gf2d_sprite.h>

typedef enum {
    entity_touch_wall_none = 0,
    entity_touch_wall_top  = 1,
    entity_touch_wall_bottom = 2,
    entity_touch_wall_left = 4,
    entity_touch_wall_right = 8
} entity_touch_wall_t;

typedef enum {
    entity_type_none,

    // Actors
    entity_type_player,
    entity_type_bug,

    // UI
    entity_type_cursor,

    // Scene
    entity_type_background,
    entity_type_world,

    entity_type_youdied,
    entity_type_healthbar,
    entity_type_equiptment,
    entity_type_pickup,
    entity_type_throwing,
    entity_type_plop,

    entity_type_egg,
    entity_type_door,

} entity_type_t;

/**
 * Abstract definition of an entity
 */
typedef struct entity_struct
{
    /**
     * Unique ID for every entity
     */
    size_t id;

    entity_type_t type;

    uint32_t statuses;

    /**
     * Movement speed of an entity
     */
    float speed;

    /**
     * Health points of entity
     */
    long health;

    // Rendering the player/entity
    bool has_color;
    Vector4D color;
    Sprite *sprite;
    Uint32 sprite_frame;

    Vector2D velocity;

    /**
     * The location in world space of the entity
     */
    Vector2D position;
    double roation;

    // Size in width and height of this entity
    Vector2D size;

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

    void (*touching_wall)(struct entity_struct *, entity_touch_wall_t);

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
 * Entity position top left coordinate
 * @param e - Entity structure
 * @return Vector that points to the top left of the entity
 */
Vector2D entity_position_top_left(entity_t *e);

/**
 * Initialize an empty entity. This is used to reset an entity to an unused state.
 *
 * @param e - Entity to blank out
 */
void entity_clear(entity_t *e);

/**
 * Post-init handler for creating an entity. Setup different entity fields that are required
 * @param e - Entity
 */
void entity_post_init(entity_t *e);

/**
 * Free an entity's resources
 * @param entity - Entity
 */
void entity_free(entity_t *entity);

/**
 * Update an entity
 * @param entity - Entity
 */
void entity_update(entity_t *entity);

/**
 * Entity touching
 * @param entity - Entity A
 * @param other - Entity A
 */
void entity_touching(entity_t *entity, entity_t *other);

/**
 * Draw an entity
 * @param entity - Entity
 */
void entity_draw(entity_t *entity);

/**
 * Draw an image centered around a player
 * @param sprite - Sprite to draw
 * @param entity_size - Size of the entity
 * @param entity_position - Position of the entity's center
 * @param entity_color - Color shift to apply
 * @param frame - Frame to draw
 * @param rotation - Rotation to apply to image
 */
void draw_centered_around_player(
        Sprite *sprite,
        Vector2D entity_size,
        Vector2D entity_position,
        Vector4D *entity_color,
        Uint32 frame,
        double rotation
);

#endif

