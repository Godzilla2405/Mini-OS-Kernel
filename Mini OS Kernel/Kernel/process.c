// kernel/process.c

#include <stdint.h>
#include "../lib/string.c"
#include "vga.c"

#define MAX_PROCESSES 4
#define STACK_SIZE 4096

typedef struct
{
    uint32_t id;
    void (*entry)(void);
    uint8_t stack[STACK_SIZE];
    uint8_t active;
} Process;

static Process processes[MAX_PROCESSES];
static int current = -1;

void process_dummy1()
{
    while (1)
    {
        terminal_writestring("[Process 1] Running...\n");
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }
}

void process_dummy2()
{
    while (1)
    {
        terminal_writestring("[Process 2] Running...\n");
        for (volatile int i = 0; i < 1000000; i++)
            ;
    }
}

void process_init()
{
    processes[0].id = 1;
    processes[0].entry = process_dummy1;
    processes[0].active = 1;

    processes[1].id = 2;
    processes[1].entry = process_dummy2;
    processes[1].active = 1;

    current = 0;
}

void process_schedule()
{
    current = (current + 1) % MAX_PROCESSES;
    if (processes[current].active && processes[current].entry)
    {
        processes[current].entry();
    }
}
