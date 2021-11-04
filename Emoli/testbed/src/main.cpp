#include <core/logger.h>
#include <core/asserts.h>

int main()
{
    EM_INFO("A test");
    EM_WARN("A test");
    EM_ERROR("A test");
    EM_TRACE("A Test");
    EM_DEBUG("A Test");
    EM_ASSERT(1==0);
    EM_ASSERT(1==1);

    return 0;
}