#include "game.h"
#include <core/logger.h>

b8 game_init(game* game_instance)
{
    EM_DEBUG("Game init");
    return true;
}

b8 game_update(game* game_instance, f32 delta_time)
{
    return true;
}

b8 game_render(game* game_instance, f32 delta_time)
{
    return true;
}

void game_on_resize(game* game_instance, u32 width, u32 height)
{

}