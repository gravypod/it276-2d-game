#include "world.h"
#include <game/game.h>
#include <game/collision/bbox.h>

#define TILES_X 10
#define TILES_Y 10
#define TILES_COUNT (TILES_X * TILES_Y)

#define TILE_SIZE_X 128
#define TILE_SIZE_Y 128

#define WORLD_X (TILE_SIZE_X * TILES_X)
#define WORLD_Y (TILE_SIZE_Y * TILES_Y)

bool tiles[TILES_COUNT];
Sprite *sprite = NULL;

void entity_world_random_valid_point(Vector2D *point)
{
    point->x = (rand() % (TILES_X - 1)) + 1;
    point->y = (rand() % (TILES_Y - 1)) + 1;
}

bool entity_world_carve_point(bool cave[TILES_COUNT], Vector2D *point, size_t *num_empty)
{
    if (point->x == 0 || point->y == 0)
        return false;

    if (point->x == TILES_X - 1 || point->y == TILES_Y - 1)
        return false;

    cave[(int) (point->x + (point->y * TILES_X))] = false;
    *num_empty += 1;

    return true;
}

void entity_world_burrow(bool cave[TILES_COUNT], float desired_ratio_empty)
{
    static Vector2D point;
    size_t num_empty = 0;

    // make all tiles wall
    memset(cave, true, sizeof(bool) * (TILES_COUNT));

    entity_world_random_valid_point(&point);
    entity_world_carve_point(cave, &point, &num_empty);

    while ((num_empty / ((float) TILES_COUNT)) < desired_ratio_empty) {
        Vector2D tmp = point;

        // move in random direction
        switch (rand() % 4) {
            case 0:
                tmp.x -= 1;
                break;
            case 1:
                tmp.x += 1;
                break;
            case 2:
                tmp.y -= 1;
                break;
            case 3:
                tmp.y += 1;
                break;
        }

        if (entity_world_carve_point(cave, &tmp, &num_empty)) {
            point = tmp;
        }
    }
}

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


    // world tile sprite
    sprite = gf2d_sprite_load_all("images/backgrounds/bg_flat.png", TILE_SIZE_X, TILE_SIZE_Y, 1);

    entity_world_burrow(tiles, 0.4f);

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
            bool exists = tiles[(y * TILES_X) + x];
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