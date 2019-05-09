# Joshua Katz 2D Game (gameframework2d)

You are an exterminator who is taking out bugs. Kill bugs and explore.

# Weapons

1. Your Foot: Crush a bug. Brings risk of spawning more bugs. Harms you.
2. Punching: Kill a bug. No risk of spawning more bugs.
3. Knife: Slightly faster than punching.
4. Handgun: Slightly faster than Knife and longer range
5. Rifle: Extremely fast

# Pickups

1. Coffee: Walk faster
2. Super Glue: Throw and trap bugs
3. Glowsticks: Throw and repel bugs
4. Bag of Chips: Throw and attract bugs
5. Wet Towel: Heal player

# Level Effects

1. Fire: Damage while standing on
2. Chest: Provide equipment that you don't already have
3. Broken Glass: Walk slower
4. Door: Go to other rooms

# Controls

1. Look: Right Joystick
2. Move: Left Joystick
3. Attack: RT
4. Throw: LT
5. Select Equipment Left/Right: LB/RB

# Level Editor

Please checkout the `level-editor` branch to use the level editor.

# Fonts

1. ComicNeue-Regular.otf: http://comicneue.com/
2. ComicNeue-Regular.ttf: https://convertio.co/otf-ttf/


# Build Requirements

1. youtube-dl
2. cmake
3. wget
4. SDL, SDL_image, SDL_ttf, SDL_mixer headers&libraries
5. C Compiler 


# Build Instructions

```
$ mkdir cmake-build
$ cd cmake-build
$ cmake ..
$ make
$ cd ..
$ ./cmake-build/gf2d
```
