#ifndef GF2D_THROWING_H
#define GF2D_THROWING_H


#include <game/entity/entity.h>

void entity_throwing_init(entity_t *entity);
void entity_throwing_touching(entity_t *entity, entity_t *them);
void entity_throwing_update(entity_t *entity);
void entity_throwing_free(entity_t *entity);

#endif
