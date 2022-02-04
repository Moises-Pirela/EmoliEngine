#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "core/game_types.h"

extern b8 create_game(game* out_game);

int main() 
{
    game game_inst;

    if (!create_game(&game_inst))
    {
        EM_FATAL("Could not create game!");
        return -1;
    }

    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize)
    {
        EM_FATAL("GAME FUNCTION POINTERS MUST BE ASSIGNED!");
        return -2;
    }

    if (!create(&game_inst))
    {
        EM_INFO("Application failed to create.");
        return 1;
    }

//NOTE: Game loop entry
    if (!run())
    {
        EM_INFO("Application failed to shutdown as properly.");
        return 2;
    }

    return 0;
}