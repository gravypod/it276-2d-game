#ifndef GF2D_GAME_ENTITY_DEFINITIONS_CURSOR_H
#define GF2D_GAME_ENTITY_DEFINITIONS_CURSOR_H

#include <game/entity/entity.h>

void entity_cursor_init(entity_t *entity);
void entity_cursor_free(entity_t *entity);
void entity_cursor_update(entity_t *entity);
void entity_cursor_draw(entity_t *entity);

#endif
