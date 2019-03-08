#ifndef GF2D_GAME_ENTITY_DEFINITIONS_HEALTHBAR_H
#define GF2D_GAME_ENTITY_DEFINITIONS_HEALTHBAR_H


#include <game/entity/entity.h>

void entity_healthbar_init(entity_t *entity);
void entity_healthbar_update(entity_t *entity);
void entity_healthbar_draw(entity_t *entity);
void entity_healthbar_free(entity_t *entity);


#endif
