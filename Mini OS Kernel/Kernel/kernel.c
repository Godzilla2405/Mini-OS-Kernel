// kernel/kernel.c

#include "../lib/string.c"
#include "vga.c"
#include "terminal.c"
#include "memory.c"
#include "process.c"
#include "../drivers/keyboard.c"
#include "../fs/fs.c"

void kernel_main()
{
    terminal_initialize();
    terminal_writestring("Welcome to Mini OS Kernel!\n");

    memory_init();
    terminal_writestring("Memory initialized.\n");

    process_init();
    terminal_writestring("Process scheduler initialized.\n");

    keyboard_init();
    terminal_writestring("Keyboard driver loaded.\n");

    fs_init();
    terminal_writestring("Filesystem initialized.\n");

    while (1)
    {
        // Idle loop
        __asm__ __volatile__("hlt");
    }
}
