#include "game.h"
#include "entry.h"
#include <core/emmemory.h>

b8 create_game(game* out_game)
{
    out_game->app_config.start_pos_x = 100;
    out_game->app_config.start_pos_y = 100;
    out_game->app_config.start_width= 1280;
    out_game->app_config.start_height = 720;
    out_game->app_config.name = const_cast<char *>("Engine Test");
    out_game->initialize = game_init;
    out_game->update = game_update;
    out_game->render = game_render;
    out_game->on_resize = game_on_resize;

    out_game->state = em_allocate(sizeof(game_state), MTAG_GAME);

    return true;
}
