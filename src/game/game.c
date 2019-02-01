#include <simple_logger.h>
#include <gf2d_sprite.h>
#include <gf2d_graphics.h>
#include <game/entity/definitions/cursor.h>
#include <game/entity/definitions/background.h>
#include <game/entity/definitions/player.h>
#include "game.h"
#include "entity/manager.h"


#define NUM_SYSTEM_INITIALIZERS 3
entity_initializer_t system_initializers[NUM_SYSTEM_INITIALIZERS] = {
        entity_background_init,
        entity_player_init,
        entity_cursor_init,
};

game_sate_t state = {
        .running = true,
        .keys = NULL,
};

void game_graphics_init()
{
    gf2d_graphics_initialize(
            "gf2d",
            1200,
            720,
            1200,
            720,
            vector4d(0, 0, 0, 255),
            0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
}

void game_update()
{
    // Get events
    SDL_PumpEvents();
    state.keys = SDL_GetKeyboardState(NULL);
    SDL_GetMouseState(&state.mouse_x, &state.mouse_y);

    entity_manager_update();

}

void game_draw()
{
    gf2d_graphics_clear_screen();
    {
        entity_manager_draw();
    }
    gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
}

int main(int argc, char **argv)
{
    init_logger("gf2d.log");
    entity_manager_init();
    game_graphics_init();
    SDL_ShowCursor(SDL_DISABLE);

    // Initialize all system components
    for (size_t i = 0; i < NUM_SYSTEM_INITIALIZERS; i++) {
        entity_manager_make(system_initializers[i]);
    }


    while (state.running) {
        game_update();
        game_draw();
    }

}
