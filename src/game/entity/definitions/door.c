#include <game/entity/entity.h>
#include "door.h"


void entity_door_init(entity_t *entity)
{
    entity->type = entity_type_door;

    entity->sprite = gf2d_sprite_load_image(KENNY_NL_IMAGE(032));
    entity->size.x = entity->sprite->frame_w;
    entity->size.y = entity->sprite->frame_h;

    printf("Spawning door\n");
}


void entity_door_world_new(uint32_t world_id, Vector2D back_position, Vector2D forward_position)
{
    if (world_id != 0) {
        entity_t *backward = entity_manager_make(entity_type_door);
        backward->position = back_position;
        backward->statuses = world_id;
    }


    entity_t *forward = entity_manager_make(entity_type_door);
    forward->position = forward_position;
    forward->statuses = world_id + 1;
}
