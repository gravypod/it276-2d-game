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
static inline void entity_touch_wall_to_string(entity_touch_wall_t wall, char sides[5])
{
    // Reset the string's data
    for (size_t i = 0; i < 5; i++) {
        sides[i] = 0;
    }

    int x = 0;

    if (wall & entity_touch_wall_top) {
        sides[x++] = 'T';
    }

    if (wall & entity_touch_wall_bottom) {
        sides[x++] = 'B';
    }

    if (wall & entity_touch_wall_left) {
        sides[x++] = 'L';
    }

    if (wall & entity_touch_wall_right) {
        sides[x++] = 'R';
    }

    sides[x] = 0;
}

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
void entity_touching_wall(entity_t *entity, entity_touch_wall_t wall);
void entity_draw(entity_t *entity);

void draw_centered_around_player(Sprite *sprite, Vector2D entity_size, Vector2D entity_position, Vector4D *entity_color,
                                 Uint32 frame);

#endif

