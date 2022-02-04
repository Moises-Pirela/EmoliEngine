#pragma once

#include "defines.h"

struct game;

typedef struct config
{
    i16 start_pos_x;

    i16 start_pos_y;

    i16 start_width;

    i16 start_height;

    char* name;

} application_config;

EM_API b8 create(struct game* game_instance);

EM_API b8 run();