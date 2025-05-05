// kernel/memory.c

#include <stdint.h>
#include "../lib/string.c"
#include "vga.c"

#define MEM_SIZE 1024 * 1024 // 1MB for demo
#define BLOCK_SIZE 4096      // 4KB blocks
#define TOTAL_BLOCKS (MEM_SIZE / BLOCK_SIZE)

static uint8_t memory_map[TOTAL_BLOCKS];

void memory_init()
{
    for (int i = 0; i < TOTAL_BLOCKS; i++)
    {
        memory_map[i] = 0; // 0 = free
    }
}

void *memory_alloc()
{
    for (int i = 0; i < TOTAL_BLOCKS; i++)
    {
        if (memory_map[i] == 0)
        {
            memory_map[i] = 1;
            return (void *)(i * BLOCK_SIZE);
        }
    }
    terminal_writestring("Out of memory!\n");
    return 0;
}

void memory_free(void *addr)
{
    uint32_t index = (uint32_t)addr / BLOCK_SIZE;
    if (index < TOTAL_BLOCKS)
    {
        memory_map[index] = 0;
    }
}
