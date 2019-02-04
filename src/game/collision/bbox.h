#ifndef GF2D_BBOX_H
#define GF2D_BBOX_H


#include <gf2d_vector.h>
#include <stdbool.h>

typedef struct {
    Vector2D origin; // Top left corner
    Vector2D size;   // Size of this box from origin
} bbox;


void bbox_offset_apply(Vector2D center, bbox *box, bbox *destination);
bool bbox_touching(bbox *left, bbox *right);

#endif
