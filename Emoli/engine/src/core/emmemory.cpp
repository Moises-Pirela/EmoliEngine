#include "emmemory.h"
#include "core/logger.h"
#include "platform/platform.h"
#include "string.h"
#include "stdio.h"

struct memory_stats
{
    u64 total_allocated;
    u64 tagged_allocations[MTAG_MAX_TAGS];
};
 

static const char* mtag_strings[MTAG_MAX_TAGS] = 
{
    "UNKOWN     ",
    "ARRAY      ",
    "DARRAY     ",
    "DICT       ",
    "RING_QUEUE ",
    "BST        ",
    "STRING     ",
    "APP        ",
    "JOB        ",
    "TEXTURE    ",
    "MAT_INST   ",
    "RENDERER   ",
    "GAME       ",
    "TRANSFORM  ",
    "ENTITY     ",
    "ENTITY_NODE",
    "SCENE      "
};

void init_memory()
{
    platform_zero_memory(&stats, sizeof(stats));
}

void shutdown_memory()
{

}

void* em_allocate(u64 size, memory_tag tag)
{
    if (tag == MTAG_UNKOWN)
    {
        EM_WARN("Allocate called using Unknown tag.");
    }

    //TODO: Memory alignment

    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    void* block = platform_allocate(size, false);
    platform_zero_memory(block, size);

    return block;
}

void em_free(void* block, u64 size, memory_tag tag)
{
    if (tag == MTAG_UNKOWN)
    {
        EM_WARN("Free called using Unknown tag.");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    //TODO: Memory alignment
    platform_free(block, false);
}

void* em_zero_memory(void* block, u64 size)
{
    return platform_zero_memory(block,size);
}

void* em_copy_memory(void* dest, const void* source, u64 size)
{
    return platform_copy_memory(dest,source,size);
}

void* em_set_memory(void* dest, i32 value, u64 size)
{
    return platform_set_memory(dest,value,size);
}

char* get_memory_usage_str()
{
    const u64 gib = 1024 * 1024 * 1024;
    const u64 mib = 1024 * 1024;
    const u64 kib = 1024;

    char buffer[8000] = "System memory use (tagged): \n";
    u64 offset = strlen(buffer);

    for (u32 i = 0; i < MTAG_MAX_TAGS; i++)
    {
        char unit[4] = "XiB";
        float amount = 1.0f;

        if (stats.tagged_allocations[i] >= gib)
        {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (float)gib;
        }
        else if (stats.tagged_allocations[i] >= mib)
        {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (float)mib;
        }
        else if (stats.tagged_allocations[i] >= kib)
        {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (float)kib;
        }
        else
        {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (float)stats.tagged_allocations[i];
        }

        i32 len = snprintf(buffer + offset, 8000, " %s: %.2f%s\n", mtag_strings[i], amount, unit);
        offset += len;
    }

    char* out_string = _strdup(buffer);
    return out_string;
}

 