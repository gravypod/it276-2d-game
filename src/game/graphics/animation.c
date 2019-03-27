#include "animation.h"

#define FRAME(a, b, c) { .action = a, .ticks = b, .texture = NULL, .frame_file_name = c }


animation_t player_body_rifle_idle = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/idle/survivor-idle_rifle_19.png"),
        }
};

animation_t player_body_rifle_move = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/move/survivor-move_rifle_19.png"),
        }
};

animation_t player_body_rifle_shoot = {
        .num_frames = 3,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/rifle/shoot/survivor-shoot_rifle_0.png"),
                FRAME(true, 5, "images/player/top-down-survivor/rifle/shoot/survivor-shoot_rifle_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/rifle/shoot/survivor-shoot_rifle_2.png"),
        }
};

animation_t player_body_handgun_idle = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/idle/survivor-idle_handgun_19.png"),
        }
};

animation_t player_body_handgun_move = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/handgun/move/survivor-move_handgun_19.png"),
        }
};

animation_t player_body_handgun_shoot = {
        .num_frames = 3,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/handgun/shoot/survivor-shoot_handgun_0.png"),
                FRAME(true, 5, "images/player/top-down-survivor/handgun/shoot/survivor-shoot_handgun_1.png"),
                FRAME(false, 30, "images/player/top-down-survivor/handgun/shoot/survivor-shoot_handgun_2.png"),
        }
};

animation_t player_body_knife_idle = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/idle/survivor-idle_knife_19.png"),
        }
};

animation_t player_body_knife_meleeattack = {
        .num_frames = 15,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_6.png"),
                FRAME(true, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_7.png"),
                FRAME(true, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_8.png"),
                FRAME(true, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/meleeattack/survivor-meleeattack_knife_14.png"),
        }
};


animation_t player_body_knife_move = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/knife/move/survivor-move_knife_19.png"),
        }
};


animation_t player_body_flashlight_idle = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/idle/survivor-idle_flashlight_19.png"),
        }
};

animation_t player_body_punch_walk = {
        .num_frames = 14,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_9.png"),
                FRAME( true, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/meleeattack/survivor-meleeattack_flashlight_14.png")
        }
};

animation_t player_body_flashlight_walk = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/flashlight/move/survivor-move_flashlight_19.png"),
        }
};

animation_t player_feet_idle = {
        .num_frames = 1,
        .frames = {
                FRAME(false, 1, "images/player/top-down-survivor/feet/idle/survivor-idle_0.png"),
        }
};

animation_t player_feet_walk = {
        .num_frames = 20,
        .frames = {
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_0.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_1.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_2.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_3.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_4.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_5.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_6.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_7.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_8.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_9.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_10.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_11.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_12.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_13.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_14.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_15.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_16.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_17.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_18.png"),
                FRAME(false, 5, "images/player/top-down-survivor/feet/walk/survivor-walk_19.png"),
        }
};

void animation_render(entity_t *entity, const animation_t *animation, animation_state_t *state, void (*action)())
{
    if (state->animation != animation) {
        state->animation = animation;
        state->frame = 0;
        state->tick = 0;
    }

    animation_frame_t frame = state->animation->frames[state->frame];

    if (state->tick > frame.ticks) {
        // This frame was an action frame. Handle action
        if (frame.action) {
            if (action) {
                action();
            }
        }

        state->tick = 0;
        state->frame += 1;

        if (state->animation->num_frames <= state->frame) {
            state->frame = 0;
        }

        frame = state->animation->frames[state->frame];
    }


    if (frame.texture == NULL) {
        frame.texture = gf2d_sprite_load_image(frame.frame_file_name);
    }

    Vector2D size = {
            .x = frame.texture->frame_w,
            .y = frame.texture->frame_h,
    };

    draw_centered_around_player(
            frame.texture,
            size,
            entity->position,
            entity->has_color ? &entity->color : NULL,
            0,
            entity->roation - 90
    );

    state->tick += 1;
}
