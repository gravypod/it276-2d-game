#include <simple_logger.h>
#include <gf2d_sprite.h>
#include <gf2d_graphics.h>
#include <game/entity/definitions/cursor.h>
#include <game/entity/definitions/background.h>
#include <game/entity/definitions/player.h>
#include <game/collision/bbox.h>
#include <game/entity/definitions/bug.h>
#include <game/entity/definitions/world.h>
#include <game/states/manager.h>
#include "game.h"
#include "entity/manager.h"


game_sate_t state = {
        .running = true,
        .keys = NULL,

        .view_width = 1200, .render_width = 1200,
        .view_height = 600, .render_height = 600
};

void game_graphics_init()
{
    gf2d_graphics_initialize(
            "gf2d",
            state.view_width,
            state.view_height,
            state.render_width,
            state.render_height,
            vector4d(0, 0, 0, 255),
            0
    );
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

void game_setup()
{
    init_logger("gf2d.log");
    entity_manager_init();
    game_graphics_init();
    SDL_ShowCursor(SDL_DISABLE);
}

void game_teardown()
{
    gf2d_sprite_cleanup();
    gf2d_graphics_cleanup();
    close_logger();
}

int main(int argc, char **argv)
{
    game_setup();
    {
        if (SDL_NumJoysticks() <= 0) {
            slog("Failed to find any joystick devices\n");
            exit(1);
        }

        game_state_manager_set(game_state_playing);
        {
            while (state.running) {
                game_update();
                game_draw();
            }
        }
        game_state_manager_set(game_state_none);
    }
    game_teardown();

}
