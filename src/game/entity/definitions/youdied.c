#include <SDL_ttf.h>
#include <gf2d_graphics.h>
#include "youdied.h"

TTF_Font *font_cached;

void entity_youdied_render_message(TTF_Font *font, char *message, int scale) {
    int x = 0, y = 0;
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(
            font,
            message,
            color
    );

    SDL_Renderer *renderer = gf2d_graphics_get_renderer();
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    {
        int texW = 0;
        int texH = 0;
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = {x, y, texW * scale, texH * scale};

        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void entity_youdied_init(entity_t *entity) {
    entity->draw = entity_youdied_draw;
    entity->free = entity_youdied_free;
    entity->type = entity_type_youdied;
    TTF_Init();
    font_cached = TTF_OpenFont("./fonts/ComicNeue-Regular.ttf", 64);

    if (!font_cached) {
        printf("Failed to load TTF from disk.\n");
    }
}

void entity_youdied_draw(entity_t *entity) {
    entity_youdied_render_message(font_cached, "You Died!", 3);
}

void entity_youdied_free(entity_t *entity) {
    if (font_cached) {
        TTF_CloseFont(font_cached);
    }
}