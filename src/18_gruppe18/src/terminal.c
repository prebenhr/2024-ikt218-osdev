#include "../include/terminal.h"
#include "../include/libc/stdint.h"

int col = 0;
int row = 0;
uint16_t *const vid = (uint16_t *const)0xB8000;
uint16_t const defaultColor = (BLACK << 12) | (GRAY << 8);
uint16_t selectedColor = defaultColor;

void terminalWrite(const char *string)
{
    char *ptr = string;

    while (*ptr != 0x00)
    {
        vid[row * width + col] = *ptr | selectedColor;
        *ptr++;
        col++;
        if (col == width)
        {
            newLine();
        }
    }

    return;
}

void clearScreen()
{
    row = 0;
    col = 0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            vid[y * width + x] = ' ' | defaultColor;
        }
    }
}

void newLine()
{
    col = 0;
    row++;
    if (row == height)
    {
        scrollUp();
    }
}

void scrollUp()
{
    row--;

    for (int y = 0; y < height - 1; y++)
    {
        for (int x = 0; x < width; x++)
        {

            vid[y * width + x] = vid[(y + 1) * width + x];
        }
    }

    for (int x = 0; x < width; x++)
    {
        vid[(height - 1) * width + x] = ' ' | selectedColor;
    }
}