#ifndef GF2D_GAME_ENTITY_DEFINITIONS_PICKUP_H
#define GF2D_GAME_ENTITY_DEFINITIONS_PICKUP_H


#include <game/entity/entity.h>

typedef enum {
    entity_pickup_none = 0,
    entity_pickup_glowstick,
    entity_pickup_superglue,
    entity_pickup_bagofchips,
} entity_pickup_type;

void entity_pickup_init(entity_t *entity);
void entity_pickup_touching(entity_t *entity, entity_t *them);
void entity_pickup_free(entity_t *entity);

#endif
