// kernel/terminal.c

#include "../lib/string.c"
#include "vga.c"

static char input_buffer[256];
static int input_index = 0;

void terminal_initialize()
{
    vga_clear();
}

void terminal_putchar(char c)
{
    vga_put_char(c);
}

void terminal_writestring(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        terminal_putchar(str[i]);
    }
}

void terminal_readchar(char c)
{
    if (c == '\b')
    {
        if (input_index > 0)
        {
            input_index--;
            terminal_putchar('\b');
            terminal_putchar(' ');
            terminal_putchar('\b');
        }
    }
    else if (c == '\n')
    {
        input_buffer[input_index] = '\0';
        terminal_putchar('\n');
        terminal_writestring("You typed: ");
        terminal_writestring(input_buffer);
        terminal_putchar('\n');
        input_index = 0;
    }
    else
    {
        if (input_index < sizeof(input_buffer) - 1)
        {
            input_buffer[input_index++] = c;
            terminal_putchar(c);
        }
    }
}
