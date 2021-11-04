#include <core/logger.h>
#include <core/asserts.h>

int main()
{
    EM_INFO("A test");
    EM_ASSERT(1==0);

    return 0;
}