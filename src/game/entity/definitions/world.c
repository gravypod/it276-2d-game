#include "world.h"
#include "player.h"
#include <game/game.h>
#include <game/collision/bbox.h>
#include <game/entity/manager.h>
#include <game/states/save/world.h>
#include <zconf.h>

#define WORLD_MAX_BUGS 1

#define WORLD_SAVE_FILE "world-0.bin"

Vector2D world_first_open_position, world_last_open_position;

Vector2D tile_size = {
        TILE_SIZE_X, TILE_SIZE_Y
};

bool tiles[TILES_COUNT];
Sprite *sprite = NULL;


bool entity_world_point_collides(Vector2D *point)
{
    for (int i = 0; i < TILES_COUNT; i++) {
        if (!tiles[i]) {
            continue;
        }

        const int x = i % TILES_X, y = i / TILES_X;

        const Vector2D tile = {
                (tile_size.x * x) - (TILE_SIZE_X / 2.0f),
                (tile_size.y * y) - (TILE_SIZE_Y / 2.0f)
        };

        const bool within_x = (tile.x <= point->x) && ((tile.x  + TILE_SIZE_X) > point->x);
        const bool within_y = (tile.y <= point->y) && ((tile.y  + TILE_SIZE_Y) > point->y);

        if (within_x && within_y) {
            return true;
        }
    }
    return false;
}

Vector2D entity_world_point_to_tile(Vector2D *point)
{
    for (int i = 0; i < TILES_COUNT; i++) {
        const int x = i % TILES_X, y = i / TILES_X;

        const Vector2D tile = {
                (tile_size.x * x) - (TILE_SIZE_X / 2.0f),
                (tile_size.y * y) - (TILE_SIZE_Y / 2.0f)
        };

        const bool within_x = (tile.x <= point->x) && ((tile.x  + TILE_SIZE_X) > point->x);
        const bool within_y = (tile.y <= point->y) && ((tile.y  + TILE_SIZE_Y) > point->y);

        if (within_x && within_y) {
            Vector2D t = {
                    .x = x,
                    .y = y
            };
            return t;
        }
    }

    Vector2D n = {
            .x = -1,
            .y = -1
    };
    return n;

}

bool entity_world_entity_collision_generator(entity_t *entity, Vector2D *position_next, Vector2D *tile) {
    int i;
    for (i = ((int) (tile->y * TILES_X) + tile->x); i < TILES_COUNT; i++) {
        if (!tiles[i]) {
            continue;
        }

        const int x = i % TILES_X, y = i / TILES_X;

        const Vector2D top_left_entity = {
                .x = position_next->x - (entity->size.x / 2.0f),
                .y = position_next->y - (entity->size.y / 2.0f),
        };
        const Vector2D top_left_tile = {
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

    tile->x = i % TILES_X;
    tile->y = i / TILES_X;

    return false;
}

bool entity_world_entity_is_colliding(entity_t *entity, Vector2D *position) {
    Vector2D tile = {0, 0};
    return entity_world_entity_collision_generator(entity, position, &tile);
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

    do {
        entity_world_random_valid_point(&point);
    } while (!entity_world_carve_point(cave, &point, &num_empty));
    *first_point = point;

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

void entity_world_bug_spawn(const bool cave[TILES_COUNT], int desired_num_bugs)
{
    int num_bugs = 0;
    for (int i = 0; num_bugs < desired_num_bugs && i < TILES_COUNT; i++) {
        if (cave[i]) {
            continue;
        }

        float chance = (rand() % 10) / 10.f;

        if (chance < 0.8f) { // 50% chance
            continue;
        }

        num_bugs++;

        // Make the bug in the world
        entity_t *bug = entity_manager_make(entity_type_bug);
        bug->position.x = ((int) (i % TILES_X)) * TILE_SIZE_X;
        bug->position.y = ((int) (i / TILES_X)) * TILE_SIZE_Y;
    }
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
    entity->allocated = true;
    entity->health = LONG_MAX;

    // world tile sprite
    sprite = gf2d_sprite_load_all("images/backgrounds/bg_flat.png", TILE_SIZE_X, TILE_SIZE_Y, 1);

    save_world_t save;
    if (save_world_load(WORLD_SAVE_FILE, &save)) {
        memcpy(tiles, save.filled, sizeof(bool) * TILES_COUNT);
        world_last_open_position = save.last_open_position;
        world_first_open_position = save.first_open_position;
    } else {
        entity_world_burrow(&world_first_open_position, &world_last_open_position, tiles, 0.4f);
        entity_world_bug_spawn(tiles, WORLD_MAX_BUGS);


        memcpy(save.filled, tiles, sizeof(bool) * TILES_COUNT);
        save.last_open_position = world_last_open_position;
        save.first_open_position = world_first_open_position;
        save_world_dump(WORLD_SAVE_FILE, &save);
    }
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


            draw_centered_around_player(sprite, tile_size, position, NULL, 0, 0);
        }
    }
}

void entity_world_touch(entity_t *entity, entity_t *other) {

}