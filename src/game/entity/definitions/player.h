#ifndef GF2D_GAME_ENTITY_DEFINITIONS_PLAYER_H
#define GF2D_GAME_ENTITY_DEFINITIONS_PLAYER_H

#include <game/entity/entity.h>

void entity_player_init(entity_t *entity);
void entity_player_touching_wall(entity_t *entity, entity_touch_wall_t wall);
void entity_player_free(entity_t *entity);
void entity_player_update(entity_t *entity);
void entity_player_draw(entity_t *entity);

#endif
