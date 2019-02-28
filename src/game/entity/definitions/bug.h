#ifndef GF2D_BUG_H
#define GF2D_BUG_H

#include <game/entity/entity.h>

void entity_bug_init(entity_t *entity);
void entity_bug_free(entity_t *entity);
void entity_bug_update(entity_t *entity);
size_t entity_bug_alive_count();

#endif