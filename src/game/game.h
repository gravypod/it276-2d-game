#ifndef GF2D_GAME_GAME_H
#define GF2D_GAME_GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct
{
    bool running;
    const Uint8 *keys;
    int mouse_x, mouse_y;
} game_sate_t;

extern game_sate_t state;

#endif
