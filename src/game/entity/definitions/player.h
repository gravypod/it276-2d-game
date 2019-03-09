#ifndef GF2D_GAME_ENTITY_DEFINITIONS_PLAYER_H
#define GF2D_GAME_ENTITY_DEFINITIONS_PLAYER_H

#include <game/entity/entity.h>

extern entity_t *player;

#define PLAYER_ALIVE() (player->health > 0)

#define PLAYER_MAX_HEALTH 1000

typedef enum {
    entity_player_status_none     = 0,
    entity_player_status_speedup  = 1,
    entity_player_status_slowdown = 2,
    entity_player_status_bagofchips = 4,
    entity_player_status_glowstick = 8,
} entity_player_status_t;

void entity_player_init(entity_t *entity);
void entity_player_touching_wall(entity_t *entity, entity_touch_wall_t wall);
void entity_player_free(entity_t *entity);
void entity_player_update(entity_t *entity);
void entity_player_draw(entity_t *entity);

#endif
