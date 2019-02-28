#include "world.h"
#include <game/game.h>
#include <game/collision/bbox.h>

#define TILES_X 10
#define TILES_Y 10

#define TILE_SIZE_X 128
#define TILE_SIZE_Y 128

#define WORLD_X (TILE_SIZE_X * TILES_X)
#define WORLD_Y (TILE_SIZE_Y * TILES_Y)

bool tiles[TILES_X * TILE_SIZE_Y];
Sprite *sprite = NULL;

void entity_world_init(entity_t *entity)
{
    entity->type = entity_type_world;
    entity->free = entity_world_free;
    entity->update = entity_world_update;
    entity->draw = entity_world_draw;
    entity->touching = entity_world_touch;

    entity->position.x = 0;
    entity->position.y = 0;

    entity->size.x = WORLD_X;
    entity->size.y = WORLD_Y;

    memset(tiles, true, sizeof(bool) * (TILES_X * TILE_SIZE_Y));

    // world tile sprite
    sprite = gf2d_sprite_load_all("images/backgrounds/bg_flat.png", TILE_SIZE_X, TILE_SIZE_Y, 1);
}

void entity_world_free(entity_t *entity)
{

}

void entity_world_update(entity_t *entity)
{

}

void entity_world_draw(entity_t *entity)
{
    Vector2D size = {
            TILE_SIZE_X, TILE_SIZE_Y
    };

    for (int x = 0; x < TILES_X; x++) {
        for (int y = 0; y < TILES_Y; y++) {
            bool exists = tiles[(y * TILES_Y) + x];
            if (!exists) {
                continue;
            }

            Vector2D position = {
                    size.x * x, size.y * y
            };


            draw_centered_around_player(sprite, size, position, NULL, 0);
        }
    }
}

void entity_world_touch(entity_t *entity, entity_t *other)
{

}