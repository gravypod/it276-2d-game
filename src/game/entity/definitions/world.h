#ifndef GF2D_GAME_ENTITY_DEFINITIONS_WORLD_H
#define GF2D_GAME_ENTITY_DEFINITIONS_WORLD_H

#include <game/entity/entity.h>

void entity_world_init(entity_t *entity);
void entity_world_free(entity_t *entity);
void entity_world_update(entity_t *entity);
void entity_world_draw(entity_t *entity);
void entity_world_touch(entity_t *entity, entity_t *other);

#endif
