// drivers/keyboard.c

#include <stdint.h>
#include "../kernel/terminal.c"

#define PORT_KEYBOARD 0x60

static const char keymap[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ',
    0, // Rest unused
};

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void keyboard_handler()
{
    uint8_t scancode = inb(PORT_KEYBOARD);
    if (scancode < 128)
    {
        char c = keymap[scancode];
        if (c)
        {
            terminal_readchar(c);
        }
    }
}

void keyboard_init()
{
    // Stub: Normally you'd set up IRQ1 here.
    terminal_writestring("Keyboard initialized (stub IRQ).\n");
}
