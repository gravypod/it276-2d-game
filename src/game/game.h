#ifndef GF2D_GAME_GAME_H
#define GF2D_GAME_GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct
{
    bool running;
    const Uint8 *keys;
    int mouse_x, mouse_y;

    int view_width, view_height;
    int render_width, render_height;

    // The viewport is x = 0 is the left most, y = 0 top most
} game_sate_t;

extern game_sate_t state;

#endif
