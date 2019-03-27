#ifndef GF2D_GAME_GRAPHICS_ANIMATION_H
#define GF2D_GAME_GRAPHICS_ANIMATION_H


#include <gf2d_sprite.h>
#include <game/entity/entity.h>

typedef struct
{
    /**
     * Number of ticks in this frame
     */
    int ticks;
    /**
     * Sprite to render
     */
    Sprite *texture;
    /**
     * Name of file to load
     */
    char frame_file_name[512];
    /**
     * If this frame is an action frame
     */
    bool action;
} animation_frame_t;

typedef struct
{
    /** Number of frames in this animation */
    int num_frames;
    /** Frame structures */
    animation_frame_t frames[];
} animation_t;

typedef struct
{
    /**
     * Animation we last ran
     */
    const animation_t *animation;
    /**
     * Frame number
     */
    int frame;
    /**
     * Tick number
     */
    int tick;
} animation_state_t;

// Bare handed attacks
extern animation_t player_body_flashlight_idle, player_body_flashlight_walk, player_body_punch_walk;
// Knife attacks
extern animation_t player_body_knife_idle, player_body_knife_meleeattack, player_body_knife_move;
// Handgun attacks
extern animation_t player_body_handgun_idle, player_body_handgun_shoot, player_body_handgun_move;
// Rifle attacks
extern animation_t player_body_rifle_idle, player_body_rifle_shoot, player_body_rifle_move;

// Feet
extern animation_t player_feet_idle, player_feet_walk;

/**
 * Pump a render object to animate a set of images.
 *
 * @param entity - Entity we are animating
 * @param animation - Animation type we are using
 * @param previous - Animation state we are updating
 * @param action - Action to run on interaction frame
 */
void animation_render(entity_t *entity, const animation_t *animation, animation_state_t *previous, void (*action)());

#endif
