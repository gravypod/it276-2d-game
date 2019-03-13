#ifndef GF2D_GLOWSTICK_H
#define GF2D_GLOWSTICK_H

#include <game/entity/entity.h>

void entity_glowstick_init(entity_t *entity);
void entity_glowstick_free(entity_t *entity);

int entity_glowsticks_deployed();
entity_t *entity_glowsticks_get(int deployed);

#endif
