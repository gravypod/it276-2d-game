#include <game/game.h>
#include "equiptment.h"
#include "player.h"


Sprite  *open_bag_of_chips_elemnt = NULL,
        *glowstick_elemnt = NULL,
        *superglue_elemnt = NULL;

void entity_equiptment_draw_element(Sprite *element, int slot)
{
    Vector2D slot_size = {.x = 32, .y = 32};
    Vector2D scale = {
            .x = slot_size.x / element->frame_w,
            .y = slot_size.y / element->frame_h,
    };
    Vector2D position = {
            .x = slot * slot_size.x,
            .y = state.render_height - slot_size.y
    };

    gf2d_sprite_draw(
            element,
            position,
            &scale,
            NULL,
            NULL,
            NULL,
            NULL,
            0
    );
}

void entity_equiptment_init(entity_t *entity)
{
    entity->type = entity_type_equiptment;
    entity->draw = entity_equiptment_draw;
    entity->free = entity_equiptment_free;
    if (!open_bag_of_chips_elemnt) {
        open_bag_of_chips_elemnt = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_075.png");
    }
    if (!glowstick_elemnt) {
        glowstick_elemnt = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_024.png");
    }
    if (!superglue_elemnt) {
        superglue_elemnt = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_103.png");
    }
}

void entity_equiptment_draw(entity_t *entity)
{
    if (!PLAYER_ALIVE()) {
        return;
    }

    if (player->statuses & entity_player_status_bagofchips) {
        entity_equiptment_draw_element(open_bag_of_chips_elemnt, 0);
    }

    if (player->statuses & entity_player_status_glowstick) {
        entity_equiptment_draw_element(glowstick_elemnt, 1);
    }

    if (player->statuses & entity_player_status_superglue) {
        entity_equiptment_draw_element(superglue_elemnt, 2);
    }
}

void entity_equiptment_free(entity_t *entity)
{
    if (open_bag_of_chips_elemnt) {
        gf2d_sprite_free(open_bag_of_chips_elemnt);
        open_bag_of_chips_elemnt = NULL;
    }
    if (glowstick_elemnt) {
        gf2d_sprite_free(glowstick_elemnt);
        glowstick_elemnt = NULL;
    }
    if (superglue_elemnt) {
        gf2d_sprite_free(superglue_elemnt);
        superglue_elemnt = NULL;
    }
}
