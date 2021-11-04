#pragma once

#include "defines.h"

#define EM_ASSERTIONS_ENABLED


#ifdef EM_ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtint_trap()
#endif

EM_API void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define EM_ASSERT(expr)                                                \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }

#define EM_ASSERT_MSG(expr, message)                                        \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debugBreak();                                                 \
        }                                                                 \
    }

#ifdef _DEBUG
#define EM_ASSERT_DEBUG(expr)                                          \
    {                                                                \
        if (expr) {                                                  \
        } else {                                                     \
            report_assertion_failure(#expr, "", __FILE__, __LINE__); \
            debugBreak();                                            \
        }                                                            \
    }
#else
#define  EM_ASSERT_DEBUG(expr)
#endif

#else
#define EM_ASSERT(expr)
#define EM_ASSERT_MSG(expr)
#define EM_ASSERT_DEBUG(expr)
#endif