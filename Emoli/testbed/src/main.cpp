#include <core/logger.h>
#include <core/asserts.h>
#include <core/platform/platform.h>

int main() {
    EM_INFO("A test");
    EM_WARN("A test");
    EM_ERROR("A test");
    EM_TRACE("A Test");
    EM_DEBUG("A Test");
    EM_FATAL("A TEST");

    platform_state state;
    if (platform_startup(&state, "EM Engine Test", 100, 100, 1280, 720)) {
        while (true) {
            platform_pump_messages(&state);
        }
    }

platform_shutdown(&state);

return 0;
}