#ifndef GF2D_GAME_GRAPHICS_ANIMATION_H
#define GF2D_GAME_GRAPHICS_ANIMATION_H


#include <gf2d_sprite.h>
#include <game/entity/entity.h>

typedef struct
{
    int ticks;
    Sprite *texture;
    char frame_file_name[512];
    bool action;
} animation_frame_t;

typedef struct
{
    int num_frames;
    animation_frame_t frames[];
} animation_t;

typedef struct
{
    const animation_t *animation;
    int frame;
    int tick;
} animation_state_t;


extern animation_t player_body_flashlight_idle;

extern animation_t player_body_flashlight_walk;

extern animation_t player_body_punch_walk;

extern animation_t player_feet_idle;

extern animation_t player_feet_walk;

extern animation_t player_body_knife_idle, player_body_knife_meleeattack, player_body_knife_move;
extern animation_t player_body_handgun_idle, player_body_handgun_shoot, player_body_handgun_move;
extern animation_t player_body_rifle_idle, player_body_rifle_shoot, player_body_rifle_move;

void animation_render(entity_t *entity, const animation_t *animation, animation_state_t *previous, void (*action)());

#endif
