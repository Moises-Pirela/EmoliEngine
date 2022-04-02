#pragma once 

#include "defines.h"

typedef enum memory_tag
{
    MTAG_UNKOWN,
    MTAG_ARRAY,
    MTAG_DARRAY,
    MTAG_DICT,
    MTAG_RING_QUEUE,
    MTAG_BST,
    MTAG_STRING,
    MTAG_APP,
    MTAG_JOB,
    MTAG_TEXTURE,
    MTAG_MATERIAL_INSTANCE,
    MTAG_RENDERER,
    MTAG_GAME,
    MTAG_TRANSFORM,
    MTAG_ENTITY,
    MTAG_ENTITY_NODE,
    MTAG_SCENE,

    MTAG_MAX_TAGS
} memory_tag;

EM_API void init_memory();
EM_API void shutdown_memory();

EM_API void* em_allocate(u64 size, memory_tag tag);
EM_API void em_free(void* block, u64 size, memory_tag tag);
EM_API void* em_zero_memory(void* block, u64 size);
EM_API void* em_copy_memory(void* dest, const void* source, u64 size);
EM_API void* em_set_memory(void* dest, i32 value, u64 size);
EM_API char* get_memory_usage_str();