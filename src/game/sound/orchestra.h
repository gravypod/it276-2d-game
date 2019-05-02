#ifndef GF2D_ORCHESTRA_H
#define GF2D_ORCHESTRA_H

#include <stdbool.h>

typedef enum
{
    ORCHESTRA_BGM_COCONUTS_SILVER_LIGHTS, ORCHESTRA_BGM_HEALTH_WE_ARE_WATER,
    ORCHESTRA_FOOTSTEPS,
    ORCHESTRA_BUG_FOOTSTEPS,
    ORCHESTRA_ERR
} orchestra_instruments;

bool orchestra_init();

void orchestra_update();

void orchestra_instrument_set(orchestra_instruments instrument, bool playing);

void orchestra_destroy();

#endif
