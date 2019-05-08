#include <game/entity/manager.h>
#include "bug.h"
#include "player.h"
#include "plop.h"

#define ENTITY_BUG_SPEED_NORMAL 1

#define SPRITE_HEIGHT 128
#define SPRITE_WIDTH 128


void entity_bug_init(entity_t *entity)
{
    entity->type = entity_type_bug;

    entity->sprite_frame = 0;
    entity->sprite = gf2d_sprite_load_all("images/space_bug_top.png", SPRITE_WIDTH, SPRITE_HEIGHT, 16);
    entity->size.x = SPRITE_WIDTH - 30; entity->size.y = SPRITE_HEIGHT;

    entity->speed = ENTITY_BUG_SPEED_NORMAL;
    entity->health = 1;
}

