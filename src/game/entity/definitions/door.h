#ifndef GF2D_DOOR_H
#define GF2D_DOOR_H

#include <game/entity/manager.h>
#include <game/kennynl.h>

void entity_door_init(entity_t *entity);
void entity_door_world_new(uint32_t world_id, Vector2D back_position, Vector2D forward_position);

#endif
