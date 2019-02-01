#include <simple_logger.h>
#include <gf2d_sprite.h>
#include <gf2d_graphics.h>
#include <game/entity/definitions/cursor.h>
#include "game.h"
#include "entity/manager.h"

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

void game_draw(Sprite *sprite)
{
    gf2d_graphics_clear_screen();
    {
        gf2d_sprite_draw_image(sprite, vector2d(0, 0));
        entity_manager_draw();
    }
    gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
}

void game_cleanup()
{
    entity_manager_free();
}

int main(int argc, char **argv)
{
    init_logger("gf2d.log");
    entity_manager_init();
    game_graphics_init();
    SDL_ShowCursor(SDL_DISABLE);

    entity_t *mouse = entity_manager_make(entity_cursor_init);
    Sprite *sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");

    while (state.running) {
        game_update();
        game_draw(sprite);
    }

}
