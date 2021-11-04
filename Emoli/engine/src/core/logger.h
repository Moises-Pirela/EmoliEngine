#pragma once

#include "defines.h"
#include<stdio.h> 
#include <stdlib.h>
#include <windows.h>
#include <iostream>


#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if EM_RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level
{
    LOG_LEVEL_FATAL   =  0,
    LOG_LEVEL_ERROR   =  1,
    LOG_LEVEL_WARN     =  2,
    LOG_LEVEL_INFO     =  3,
    LOG_LEVEL_DEBUG   =  4,
    LOG_LEVEL_TRACE   =  5,

} log_level;

enum color { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };

b8 initialize_logging();
void shutdown_logging();

EM_API void log_output(log_level level, const char* message, ...);

#define EM_FATAL(message, ...) {\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::RED);\
    log_output(LOG_LEVEL_FATAL , message, ##__VA_ARGS__);\
}

#ifndef EM_ERROR
#define EM_ERROR(message, ...)  {\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::RED);\
     log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);\
}
#endif

#if LOG_WARN_ENABLED == 1
#define EM_WARN(message, ...)  \
{\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::YELLOW);\
     log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__);\
}
#else
#define EM_WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define EM_INFO(message, ...) \
{\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::WHITE);\
     log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__);\
}
#else
#define EM_INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define EM_DEBUG(message, ...) {\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::TEAL);\
     log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);\
}
#else
#define EM_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define EM_TRACE(message, ...) {\
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);\
    SetConsoleTextAttribute(hcon, color::GRAY);\
     log_output(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);\
}
#else
#define EM_TRACE(message, ...)
#endif