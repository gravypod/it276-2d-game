#ifndef GF2D_STATE_SAVE_EM_H
#define GF2D_STATE_SAVE_EM_H

#include <stdint.h>
#include <stddef.h>
#include <game/entity/entity.h>
#include <game/entity/manager.h>

typedef struct
{
    /**
     * If this entity is already being used by something
     */
    bool allocated;
    uint8_t static_id;

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

    Uint32 sprite_frame;

    Vector2D velocity;

    /**
     * The location in world space of the entity
     */
    Vector2D position;
    double roation;

    // Size in width and height of this entity
    Vector2D size;

} save_entity_t;

typedef struct
{
    save_entity_t entities[MAX_NUM_ENTITIES];
} save_em_t;


void save_em_dump(const char *file_name, const save_em_t *em);

bool save_em_load(const char *file_name, save_em_t *em);

#endif
