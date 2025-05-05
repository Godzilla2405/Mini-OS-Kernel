// kernel/vga.c

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000
#define WHITE_ON_BLACK 0x0F

static uint16_t *const vga_buffer = (uint16_t *)VGA_ADDRESS;
static uint8_t cursor_row = 0;
static uint8_t cursor_col = 0;

static uint16_t make_vga_entry(char c, uint8_t color)
{
    return (uint16_t)c | ((uint16_t)color << 8);
}

void vga_clear()
{
    for (uint8_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (uint8_t x = 0; x < VGA_WIDTH; x++)
        {
            const int index = y * VGA_WIDTH + x;
            vga_buffer[index] = make_vga_entry(' ', WHITE_ON_BLACK);
        }
    }
    cursor_row = 0;
    cursor_col = 0;
}

void vga_put_char(char c)
{
    if (c == '\n')
    {
        cursor_row++;
        cursor_col = 0;
    }
    else
    {
        const int index = cursor_row * VGA_WIDTH + cursor_col;
        vga_buffer[index] = make_vga_entry(c, WHITE_ON_BLACK);
        cursor_col++;
        if (cursor_col >= VGA_WIDTH)
        {
            cursor_col = 0;
            cursor_row++;
        }
    }

    if (cursor_row >= VGA_HEIGHT)
    {
        vga_clear(); // For simplicity, clear screen on overflow
    }
}
