#ifndef GF2D_GAME_ENTITY_DEFINITIONS_EQUIPTMENT_H
#define GF2D_GAME_ENTITY_DEFINITIONS_EQUIPTMENT_H


#include <game/entity/entity.h>

void entity_equiptment_init(entity_t *entity);
void entity_equiptment_draw(entity_t *entity);
void entity_equiptment_free(entity_t *entity);

void entity_equiptment_selection_left();
void entity_equiptment_selection_right();

int entity_equiptment_selection();
uint32_t entity_equiptment_slot_type(int slot);
Sprite *entity_equiptment_slot_sprite(int slot);

#endif
