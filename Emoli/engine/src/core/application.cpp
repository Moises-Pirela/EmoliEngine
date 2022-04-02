#include "application.h"
#include "logger.h"
#include "platform/platform.h"
#include "core/emmemory.h"
#include "game_types.h"

typedef struct application_state
{
    game* game_instance;

    b8 is_running;

    b8 is_suspended;

    platform_state platform;

    i16 width;

    i16 height;

    i16 last_time;

} application_state;

static b8 initialized = FALSE;
static application_state app_state;

EM_API b8 create(game* game_instance)
{
    if (initialized)
    {
        EM_ERROR("Application has been called more than once!");
        return FALSE;
    }

    app_state.game_instance = game_instance;

    //NOTE: Initialize subsystems here
    initialize_logging();

    
    //TODO: Remove this, for testing purposes only.
    EM_INFO("A test");
    EM_WARN("A test");
    EM_ERROR("A test");
    EM_TRACE("A Test");
    EM_DEBUG("A Test");
    EM_FATAL("A TEST");

    app_state.is_running = true;
    app_state.is_suspended = false;

    if (!platform_startup(
        &app_state.platform, 
        game_instance->app_config.name, 
        game_instance->app_config.start_pos_x, 
        game_instance->app_config.start_pos_y, 
        game_instance->app_config.start_width, 
        game_instance->app_config.start_height))  return false;

        if (!app_state.game_instance->initialize(app_state.game_instance))
        {
            EM_FATAL("GAME FAILED TO INIT")
            return false;
        }

     app_state.game_instance->on_resize(app_state.game_instance, app_state.width, app_state.height);

    initialized = true;

    return true;
}

EM_API b8 run()
{
    EM_INFO(get_memory_usage_str());

    while (app_state.is_running)
    {
        //NOTE: Game loop
        if (!platform_pump_messages(&app_state.platform))
        {
            app_state.is_running = false;
        }    

        if (!app_state.is_suspended)
        {
            if (!app_state.game_instance->update(app_state.game_instance, (f32)0))
            {
                EM_FATAL("Game update failed. terminating...");
                app_state.is_running = false;
                break;
            }

            if (!app_state.game_instance->render(app_state.game_instance, (f32)0))
            {
                EM_FATAL("Game render failed. terminating...");
                app_state.is_running = false;
                break;
            }
        }
    }
    app_state.is_running = false;
    platform_shutdown(&app_state.platform);

    return true;
}