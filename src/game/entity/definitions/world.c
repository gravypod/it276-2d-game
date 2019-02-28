#include "world.h"
#include <game/game.h>
#include <game/collision/bbox.h>

#define TILES_X 10
#define TILES_Y 10
#define TILES_COUNT (TILES_X * TILES_Y)

#define TILE_SIZE_X (128 + 32)
#define TILE_SIZE_Y (128 + 32)

#define WORLD_X (TILE_SIZE_X * TILES_X)
#define WORLD_Y (TILE_SIZE_Y * TILES_Y)

Vector2D tile_size = {
        TILE_SIZE_X, TILE_SIZE_Y
};

bool tiles[TILES_COUNT];
Sprite *sprite = NULL;

bool entity_world_entity_collision_generator(entity_t *entity, Vector2D *tile) {
    int x, y = (int) tile->y;

    for (x = (int) tile->x; x < TILES_X; x++) {
        for (y = (int) tile->y; y < TILES_Y; y++) {
            bool exists = tiles[(y * TILES_X) + x];

            if (!exists) {
                continue;
            }

            Vector2D top_left_entity = {
                    .x = entity->position.x - (entity->size.x / 2.0f),
                    .y = entity->position.y - (entity->size.y / 2.0f),
            };
            Vector2D top_left_tile = {
                    (tile_size.x * x) - (TILE_SIZE_X / 2.0f), (tile_size.y * y) - (TILE_SIZE_Y / 2.0f)
            };

            if (top_left_tile.x < top_left_entity.x + entity->size.x &&
                top_left_tile.x + TILE_SIZE_X > top_left_entity.x &&
                top_left_tile.y < top_left_entity.y + entity->size.y &&
                top_left_tile.y + TILE_SIZE_Y > top_left_entity.y) {

                tile->x = x;
                tile->y = y;

                return true;
            }

        }
    }

    tile->x = x;
    tile->y = y;

    return false;
}

void entity_world_entity_prevent_collision(entity_t *entity)
{
    Vector2D tile = {0, 0};


    while (entity_world_entity_collision_generator(entity, &tile)) {

        Vector2D top_left_entity = {
                .x = entity->position.x - (entity->size.x / 2.0f),
                .y = entity->position.y - (entity->size.y / 2.0f),
        };

        Vector2D top_left_tile = {
                (tile_size.x * tile.x) - (TILE_SIZE_X / 2.0f), (tile_size.y * tile.y) - (TILE_SIZE_Y / 2.0f)
        };


        if (top_left_tile.x < top_left_entity.x + entity->size.x) {
            // x -> |
            entity->position.x = (top_left_tile.x + TILE_SIZE_X) + .1f;
        } else if (top_left_tile.x + TILE_SIZE_X > top_left_entity.x) {
            // | <- x
            entity->position.x = (top_left_tile.x - entity->size.x) - 1;
        }

        if (top_left_tile.y < top_left_entity.y + entity->size.y) {
            entity->position.y = (top_left_tile.y + entity->size.y) - 1;
        } else if (top_left_tile.y + TILE_SIZE_Y > top_left_entity.y) {
            entity->position.y = (top_left_tile.y - TILE_SIZE_Y) + 1;
        }
    }
}

bool entity_world_entity_is_colliding(entity_t *entity) {
    Vector2D tile = {0, 0};
    return entity_world_entity_collision_generator(entity, &tile);
}

void entity_world_random_valid_point(Vector2D *point) {
    point->x = (rand() % (TILES_X - 1)) + 1;
    point->y = (rand() % (TILES_Y - 1)) + 1;
}

bool entity_world_carve_point(bool cave[TILES_COUNT], Vector2D *point, size_t *num_empty) {
    if (point->x == 0 || point->y == 0)
        return false;

    if (point->x == TILES_X - 1 || point->y == TILES_Y - 1)
        return false;

    cave[(int) (point->x + (point->y * TILES_X))] = false;
    *num_empty += 1;

    return true;
}

void entity_world_burrow(Vector2D *first_point, Vector2D *last_point, bool cave[TILES_COUNT], float desired_ratio_empty) {
    static Vector2D point;
    size_t num_empty = 0;

    // make all tiles wall
    memset(cave, true, sizeof(bool) * (TILES_COUNT));

    entity_world_random_valid_point(&point);
    *first_point = point;
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

    *last_point = point;
}

void entity_world_init(entity_t *entity) {
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

    Vector2D first, last;

    entity_world_burrow(&first, &last, tiles, 0.4f);


}

void entity_world_free(entity_t *entity) {

}

void entity_world_update(entity_t *entity) {

}

void entity_world_draw(entity_t *entity) {
    for (int x = 0; x < TILES_X; x++) {
        for (int y = 0; y < TILES_Y; y++) {
            bool exists = tiles[(y * TILES_X) + x];
            if (!exists) {
                continue;
            }

            Vector2D position = {
                    tile_size.x * x, tile_size.y * y
            };


            draw_centered_around_player(sprite, tile_size, position, NULL, 0);
        }
    }
}

void entity_world_touch(entity_t *entity, entity_t *other) {

}