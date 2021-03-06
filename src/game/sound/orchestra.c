#include "orchestra.h"
#include <stddef.h>
#include <SDL_mixer.h>
#include <simple_logger.h>
#include <game/entity/entity.h>
#include <game/entity/manager.h>

#define ORCHESTRA_INSTRUMENTS_TOTAL (ORCHESTRA_ERR + 1)
char *instrument_sound_files[ORCHESTRA_INSTRUMENTS_TOTAL] = {
        "sounds/coconuts-silver_lights.mp3", "sounds/health-we_are_water.mp3", // BGM
        "sounds/footsteps.wav",
        "sounds/bug-footsteps.wav",
        "sounds/gun-gunshot-01.wav",
        "sounds/machine-gun-01.wav",
        NULL
};

int instruments_playing_on_channels[ORCHESTRA_INSTRUMENTS_TOTAL];

bool continue_playing[ORCHESTRA_INSTRUMENTS_TOTAL + 1];
bool playing[ORCHESTRA_INSTRUMENTS_TOTAL + 1];

#define ORCHESTRA_MUSICS_NUM 2
orchestra_instruments music_instruments[ORCHESTRA_MUSICS_NUM] = {
        ORCHESTRA_BGM_COCONUTS_SILVER_LIGHTS, ORCHESTRA_BGM_HEALTH_WE_ARE_WATER
};

#define ORCHESTRA_SOUND_EFFECTS_NUM 4
orchestra_instruments sound_effect_instruments[ORCHESTRA_SOUND_EFFECTS_NUM] = {
        ORCHESTRA_FOOTSTEPS, ORCHESTRA_BUG_FOOTSTEPS,
        ORCHESTRA_GUNSHOT, ORCHESTRA_MACHINE_GUNSHOT
};

Mix_Music *musics[ORCHESTRA_MUSICS_NUM];
Mix_Chunk *sound_effects[ORCHESTRA_SOUND_EFFECTS_NUM];


Mix_Chunk *chunk_for_instrument(orchestra_instruments instrument)
{
    for (int i = 0; i < ORCHESTRA_SOUND_EFFECTS_NUM; i++) {
        if (sound_effect_instruments[i] == instrument) {
            return sound_effects[i];
        }
    }
    return NULL;
}

int instrament_get_channel(orchestra_instruments instrument)
{
    return instruments_playing_on_channels[instrument];
}

orchestra_instruments channel_get_instrument(int channel)
{
    for (int i = 0; i < ORCHESTRA_INSTRUMENTS_TOTAL; i++) {
        if (instruments_playing_on_channels[i] == channel) {
            return (orchestra_instruments) i;
        }
    }
    return ORCHESTRA_ERR;
}

bool orchestra_instrument_music(orchestra_instruments instrument)
{
    for (int i = 0; i < ORCHESTRA_MUSICS_NUM; i++) {
        if (instrument == music_instruments[i]) {
            return true;
        }
    }
    return false;
}

void orchestra_sound_effects_load()
{
    for (int i = 0; i < ORCHESTRA_SOUND_EFFECTS_NUM; i++) {
        sound_effects[i] = Mix_LoadWAV(instrument_sound_files[sound_effect_instruments[i]]);

        if (i == ORCHESTRA_BUG_FOOTSTEPS) {
            Mix_VolumeChunk(sound_effects[i], 128);
        }
        if (!sound_effects[i]) {
            slog("Failed to load %s", instrument_sound_files[sound_effect_instruments[i]]);
        }
    }
}

void orchestra_sound_effects_unload()
{
    for (int i = 0; i < ORCHESTRA_SOUND_EFFECTS_NUM; i++) {
        if (sound_effects[i]) {
            Mix_FreeChunk(sound_effects[i]);
        }
    }
}

void orchestra_music_load()
{
    for (int i = 0; i < ORCHESTRA_MUSICS_NUM; i++) {
        musics[i] = Mix_LoadMUS(instrument_sound_files[music_instruments[i]]);

        if (!musics[i]) {
            slog("Failed to load %s", instrument_sound_files[music_instruments[i]]);
        }
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
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 4, 4096) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return false;
    }
    orchestra_music_load();
    orchestra_sound_effects_load();

    // Background music is happening
    Mix_VolumeMusic(128/4);
    Mix_HookMusicFinished(orchestra_music_switch_songs);
    orchestra_music_switch_songs();

    Mix_Volume(-1, 64);
}

void orchestra_update_bug_scuttle()
{
    bool any_bug_alive_and_moving = false;

    entity_t *e = NULL;
    size_t ei = 0;
    while (entity_manager_iterate_generator(&ei, true, &e)) {
        if (e->type != entity_type_bug) {
            continue;
        }

        if (e->health > 0 && e->speed > 0) {
            any_bug_alive_and_moving = true;
            break;
        }
    }

    orchestra_instrument_set(ORCHESTRA_BUG_FOOTSTEPS, any_bug_alive_and_moving);

}

void orchestra_update()
{
    orchestra_update_bug_scuttle();

    for (int i = 0; i < ORCHESTRA_INSTRUMENTS_TOTAL; i++) {
        if (orchestra_instrument_music(i))
            continue;

        if (playing[i] && !continue_playing[i]) {
            Mix_HaltChannel(instrament_get_channel(i));
            instruments_playing_on_channels[i] = -1;
            playing[i] = false;
        }

        if (continue_playing[i] && !playing[i]) {
            if ((instruments_playing_on_channels[i] = Mix_PlayChannel(-1, chunk_for_instrument(i), -1)) == -1) {
                printf("Mix_PlayChannel: %s\n", Mix_GetError());
            } else {
                playing[i] = true;
                slog("Starting sound effect %d", instruments_playing_on_channels[i]);
            }
        }
    }
}

void orchestra_instrument_set(orchestra_instruments instrument, bool state)
{
    if (orchestra_instrument_music(instrument)) {
        // Can't change music tracks with _set
        slog("Cant change music tracks with _set");
        return;
    }

    continue_playing[instrument] = state;
}

void orchestra_destroy()
{
    orchestra_music_unload();
    orchestra_sound_effects_unload();
}