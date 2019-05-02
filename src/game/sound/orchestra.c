#include "orchestra.h"
#include <stddef.h>
#include <SDL_mixer.h>
#include <simple_logger.h>

char *instrument_sound_files[ORCHESTRA_ERR + 1] = {
        "sounds/coconuts-silver_lights.mp3", "sounds/health-we_are_water.mp3", // BGM
        NULL
};

#define ORCHESTRA_MUSICS_NUM 2
orchestra_instruments music_instruments[ORCHESTRA_MUSICS_NUM] = {
        ORCHESTRA_BGM_COCONUTS_SILVER_LIGHTS, ORCHESTRA_BGM_HEALTH_WE_ARE_WATER
};

Mix_Music *musics[ORCHESTRA_MUSICS_NUM];

void orchestra_music_load()
{
    for (int i = 0; i < ORCHESTRA_MUSICS_NUM; i++) {
        musics[i] = Mix_LoadMUS(instrument_sound_files[music_instruments[i]]);
    }
}

void orchestra_music_unload()
{

    for (int i = 0; i < ORCHESTRA_MUSICS_NUM; i++) {
        if (musics[i]) {
            Mix_FreeMusic(musics[i]);
        }
    }
}

void orchestra_music_switch_songs()
{
    static orchestra_instruments current_song = ORCHESTRA_ERR;

    switch (current_song) {
        case ORCHESTRA_BGM_COCONUTS_SILVER_LIGHTS:
            current_song = ORCHESTRA_BGM_HEALTH_WE_ARE_WATER;
            break;
        case ORCHESTRA_BGM_HEALTH_WE_ARE_WATER:
        default:
            current_song = ORCHESTRA_BGM_COCONUTS_SILVER_LIGHTS;
            break;
    }

    Mix_PlayMusic(musics[current_song], 1);
}

bool orchestra_init()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        slog("Failed to Mix_OpenAudio");
        return false;
    }
    orchestra_music_load();

    // Background music is happening
    Mix_HookMusicFinished(orchestra_music_switch_songs);
    orchestra_music_switch_songs();
}

void orchestra_update()
{

}

void orchestra_instrument_set(orchestra_instruments instrument, bool playing)
{

}

void orchestra_destroy()
{
    orchestra_music_unload();
}