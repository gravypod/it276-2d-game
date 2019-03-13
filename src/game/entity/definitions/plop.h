#ifndef GF2D_GLOWSTICK_H
#define GF2D_GLOWSTICK_H

#include <game/entity/entity.h>

void entity_plop_init(entity_t *entity);

int entity_plop_glowsticks_count();
int entity_plop_bagofchips_count();
int entity_plop_superglues_count();

entity_t *entity_plop_glowsticks_get(int slot);
entity_t *entity_plop_bagofchips_get(int slot);
entity_t *entity_plop_superglues_get(int slot);

#endif
