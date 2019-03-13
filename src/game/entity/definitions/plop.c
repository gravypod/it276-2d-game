#include <game/entity/manager.h>
#include "plop.h"
#include "player.h"
#include "equiptment.h"

#define MAX_PLOPS 128
typedef struct {
    int num_glowsticks, num_bagofchips, num_superglues;
    entity_t *glowsticks[MAX_PLOPS];
    entity_t *bagofchips[MAX_PLOPS];
    entity_t *superglues[MAX_PLOPS];
} plopidx_t;

plopidx_t plops;


int entity_plop_glowsticks_count() { return plops.num_glowsticks; }
int entity_plop_bagofchips_count() { return plops.num_bagofchips; }
int entity_plop_superglues_count() { return plops.num_superglues; }

entity_t *entity_plop_glowsticks_get(int slot) { return plops.glowsticks[slot]; }
entity_t *entity_plop_bagofchips_get(int slot) { return plops.bagofchips[slot]; }
entity_t *entity_plop_superglues_get(int slot) { return plops.superglues[slot]; }

void entity_plop_reindex() {
    memset(&plops, 0, sizeof(plops));

    size_t i = 0;
    entity_t *entity;

    while (entity_manager_iterate_generator(&i, true, &entity)) {
        if (entity->type != entity_type_plop) {
            continue;
        }

        switch (entity->statuses) {
            case entity_player_status_glowstick:
                plops.glowsticks[plops.num_glowsticks++] = entity;
                break;
            case entity_player_status_bagofchips:
                plops.bagofchips[plops.num_bagofchips++] = entity;
                break;
            case entity_player_status_superglue:
                plops.superglues[plops.num_superglues++] = entity;
                break;
        }
    }

    printf(
            "Glowsticks: %d\nBags: %d\nSuperglues: %d\n",
            plops.num_glowsticks,
            plops.num_bagofchips,
            plops.num_superglues
    );
}


void entity_plop_free(entity_t *entity) {
    // Hack to prevent us from being detected by the index
    entity->allocated = false;
    entity_plop_reindex();
}

void entity_plop_draw(entity_t *entity) {
    if (entity->sprite == NULL && entity->statuses == UINT32_MAX) {
        entity_manager_release(entity);
        return;
    }

    if (entity->sprite == NULL) {
        int slot = entity_equiptment_status_to_slot(entity->statuses);

        if (slot == -1) {
            entity_manager_release(entity);
            return;
        }

        entity->sprite = entity_equiptment_slot_sprite(slot);

        // There's a new plop in town.
        entity_plop_reindex();
    }
}

void entity_plop_init(entity_t *entity) {
    entity->type = entity_type_plop;
    entity->free = entity_plop_free;
    entity->draw = entity_plop_draw;
    entity->sprite = NULL;
    entity->statuses = UINT32_MAX;
}