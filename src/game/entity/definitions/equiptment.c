#include <game/game.h>
#include "equiptment.h"
#include "player.h"

entity_t *equiptment = NULL;

Sprite  *selected_elemnt = NULL;

typedef struct {
    char *file_name;
    Sprite *sprite;
    uint32_t player_status;
} equiptment_slot_t;

#define NUM_EQUIPTMENT_SLOTS 3
equiptment_slot_t slots[NUM_EQUIPTMENT_SLOTS] = {
        {
                .file_name = "images/kenny-nl/generic-items/genericItem_color_075.png",
                .player_status = entity_player_status_bagofchips,
                .sprite = NULL,
        },
        {
                .file_name = "images/kenny-nl/generic-items/genericItem_color_024.png",
                .player_status = entity_player_status_glowstick,
                .sprite = NULL,
        },
        {
                .file_name = "images/kenny-nl/generic-items/genericItem_color_103.png",
                .player_status = entity_player_status_superglue,
                .sprite = NULL,
        },
};

int entity_equiptment_selection_count()
{
    int count = 0;

    for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
        count += (player->statuses & slots[i].player_status) > 0;
    }

    return count;
}

uint32_t entity_equiptment_slot_type(int slot)
{
    return slots[slot].player_status;
}

Sprite *entity_equiptment_slot_sprite(int slot)
{
    if (slot == -1) {
        return NULL;
    }
    if (!slots[slot].sprite) {
        slots[slot].sprite = gf2d_sprite_load_image(slots[slot].file_name);
    }

    return slots[slot].sprite;
}

int entity_equiptment_status_to_slot(uint32_t status)
{
    for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
        if (slots[i].player_status == status)
            return i;
    }
    return -1;
}


uint32_t entity_equiptment_selection_left_next()
{
    int count = entity_equiptment_selection_count();
    int last;

    if (equiptment->statuses != UINT32_MAX) {
        last = (int) equiptment->statuses;
    } else {
        last = count + 1;
    }

    for (int i = last - 1; i >= 0; i--) {
        if (player->statuses & slots[i].player_status) {
            return (uint32_t) i;
        }
    }

    if (count > 0) {
        // Search left from last slot
        for (int i = NUM_EQUIPTMENT_SLOTS - 1; i >= 0; i--) {
            if (player->statuses & slots[i].player_status) {
                return (uint32_t) i;
            }
        }
    }

    return UINT32_MAX;
}

uint32_t entity_equiptment_selection_right_next()
{
    int count = entity_equiptment_selection_count();
    int last;

    if (equiptment->statuses != UINT32_MAX) {
        last = (int) equiptment->statuses;
    } else {
        last = -1;
    }

    // Search right of current possition
    for (int i = last + 1; i <= count; i++) {
        if (player->statuses & slots[i].player_status) {
            return (uint32_t) i;
        }
    }

    if (count > 0) {
        // Search right from 0
        for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
            if (player->statuses & slots[i].player_status) {
                return (uint32_t) i;
            }
        }
    }

    return UINT32_MAX;
}

void entity_equiptment_selection_left()
{
    uint32_t  next = entity_equiptment_selection_left_next();

    if (next == UINT32_MAX) {
        return;
    }

    equiptment->statuses = next;
}

int entity_equiptment_selection()
{
    if (equiptment->statuses == UINT32_MAX) {
        return -1;
    }

    return (int) equiptment->statuses;
}

void entity_equiptment_selection_right()
{
    uint32_t next = entity_equiptment_selection_right_next();

    if (next == UINT32_MAX) {
        return;
    }

    equiptment->statuses = next;
}

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

    if (!selected_elemnt) {
        selected_elemnt = gf2d_sprite_load_image("images/kenny-nl/generic-items/genericItem_color_044.png");
    }

    for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
        slots[i].sprite = gf2d_sprite_load_image(slots[i].file_name);
    }

    entity->statuses = UINT32_MAX;
    equiptment = entity;
}

void entity_equiptment_draw(entity_t *entity)
{
    if (!PLAYER_ALIVE()) {
        return;
    }

    for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
        if (player->statuses & slots[i].player_status) {
            entity_equiptment_draw_element(slots[i].sprite, i);
        }
    }

    if (entity->statuses != UINT32_MAX) {
        entity_equiptment_draw_element(selected_elemnt, (int) entity->statuses);
    }
}

void entity_equiptment_free(entity_t *entity)
{
    for (int i = 0; i < NUM_EQUIPTMENT_SLOTS; i++) {
        gf2d_sprite_free(slots[i].sprite);
        slots[i].sprite = NULL;
    }


    if (selected_elemnt) {
        gf2d_sprite_free(selected_elemnt);
        selected_elemnt = NULL;
    }

    equiptment = NULL;
}
