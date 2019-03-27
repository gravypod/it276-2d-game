#ifndef GF2D_STATE_SAVE_EM_H
#define GF2D_STATE_SAVE_EM_H

#include <stdint.h>
#include <stddef.h>
#include <game/entity/entity.h>
#include <game/entity/manager.h>

typedef struct {
    /**
     * If this entity is already being used by something
     */
    bool allocated;

    /**
     * A static unique ID
     */
    uint8_t static_id;

    /**
     * Type of entity that is in this entity_t
     */
    entity_type_t type;

    /**
     * Generic bitflags for entities
     */
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

    /**
     * What frame of the sprite sheet to render
     */
    Uint32 sprite_frame;

    /**
     * Velocity of this entity.
     */
    Vector2D velocity;

    /**
     * The location in world space of the entity
     */
    Vector2D position;

    /**
     * Rotation of this entity. Misspelled it and never had time to change
     */
    double roation;

    // Size in width and height of this entity
    Vector2D size;
} save_entity_t;

typedef struct {
    /**
     * Persisted version of entities
     */
    save_entity_t entities[MAX_NUM_ENTITIES];
} save_em_t;

/**
 * Save entity manager entity into a real entity
 * @param saved - Saved entity structure
 * @param entity - Runtime entity structure
 */
void save_em_save_entity_to_entity(save_entity_t *saved, entity_t *entity);

/**
 * Entity manager entity into save entity.
 * @param entity - Runtime entity structure
 * @param save_entity - Saved entity structure
 */
void save_em_entity_to_save_entity(entity_t *entity, save_entity_t *save_entity);

/**
 * Save the persistent EM structure to file
 * @param file_name - Filename to save into
 * @param em - Entity manager to save
 */
void save_em_dump(const char *file_name, const save_em_t *em);

/**
 * Load the persistent EM structure to file
 * @param file_name - Filename to load from
 * @param em - Entity manager to load into
 * @return if we were able to load from this file
 */
bool save_em_load(const char *file_name, save_em_t *em);

#endif
