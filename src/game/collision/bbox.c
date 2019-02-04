#include "bbox.h"

void bbox_offset_apply(Vector2D center, bbox *box, bbox *destination)
{
    vector2d_add(destination->origin, box->origin, center);
    vector2d_add(destination->size, box->size, vector2d(0, 0));

}

bool bbox_touching(bbox *left, bbox *right)
{
    int diff_x = (int) (left->origin.x - right->origin.x);
    int diff_y = (int) (left->origin.y - right->origin.y);

    return (abs(diff_x) * 2 < (left->size.x + right->size.x)) &&
           (abs(diff_y) * 2 < (left->size.y + right->size.y));
}
