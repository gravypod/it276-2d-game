#include "healthbar.h"
#include "player.h"

Sprite *health_sprite = NULL;
#define HEALTH_SPRITE_WIDTH 40
#define HEALTH_SPRITE_HEIGHT 40

void entity_healthbar_init(entity_t *entity)
{
    entity->type = entity_type_healthbar;
    entity->update = entity_healthbar_update;
    entity->draw = entity_healthbar_draw;
    entity->free = entity_healthbar_free;

    // Not a world entity
    entity->size.x = entity->size.y = 0;
    entity->position.x = entity->position.y = 0;

    if (!health_sprite) {
        health_sprite = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_089.png");
    }
}

void entity_healthbar_update(entity_t *entity)
{
    if (player) {
        entity->health = player->health;
    }
}

void entity_healthbar_draw(entity_t *entity)
{
    if (PLAYER_ALIVE()) {
        const long max = PLAYER_MAX_HEALTH;
        const long step = max / 10;

        for (long i = 0; (i * step) < entity->health; i++) {
            const long x = i * HEALTH_SPRITE_WIDTH, y = 10;
            Vector2D position = {
                    .x = x,
                    .y = y
            };
            gf2d_sprite_draw(
                    health_sprite,
                    position,
                    NULL, NULL, NULL, NULL,
                    NULL,
                    0
            );
        }
    }
}

void entity_healthbar_free(entity_t *entity)
{
    if (health_sprite) {
        gf2d_sprite_free(health_sprite);
        health_sprite = NULL;
    }
}
