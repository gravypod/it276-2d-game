#ifndef GF2D_GAME_GAME_H
#define GF2D_GAME_GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct
{
    /**
     * If the game is running
     */
    bool running;

    /**
     * Key states from SDL
     */
    const Uint8 *keys;

    /**
     * Position of the mouse
     */
    int mouse_x, mouse_y;

    /**
     * Width and height of the viewport (window)
     */
    int view_width, view_height;

    /**
     * Width and height of the rendering space (fake screen)
     */
    int render_width, render_height;

    // The viewport is x = 0 is the left most, y = 0 top most
} game_sate_t;

/**
 * Global shared game state
 */
extern game_sate_t state;

#endif
