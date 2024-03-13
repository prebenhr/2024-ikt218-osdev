#include <terminal.h>
#include <libc/stdint.h>

int col = 0;
int row = 0;

// Setting pointer to start of video memory.
uint16_t *const vid = (uint16_t *const)0xB8000;
// Setting default color scheme, gray on black.
uint16_t const defaultColor = (BLACK << 12) | (GRAY << 8);
uint16_t selectedColor = defaultColor;

// Function to set color.
// Ensures that color codes used are within valid range.
void setColors(uint16_t background, uint16_t text)
{
    if (background > 0xF)
    {
        terminalWrite("Background color out of range\n");
        return;
    }
    if (text > 0xF)
    {
        terminalWrite("Text color out of range\n");
        return;
    }

    selectedColor = (background << 12) | (text << 8);
}

// Function to write to screen. Takes in a string and writes it on the screen.
// If the string contains a newline, the newLine function is called.
void terminalWrite(const char *string)
{
    char *ptr = string;

    while (*ptr != 0x00)
    {
        if (*ptr == '\n')
        {
            newLine();
            *ptr++;
            continue;
        }
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

// Function to clear screen. Basically writes blank space to every field on the grid/screen.
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

// Function to begin new line. Starts writing from left on the row below current. If that is outside of screen size, invokes scroll function.
void newLine()
{
    col = 0;
    row++;
    if (row == height)
    {
        scrollUp();
    }
}

// Function to scroll text up. Copies every character up one row and writes spaces to the bottom row.
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
        vid[(height - 1) * width + x] = ' ' | defaultColor;
    }
}

void itos(int integer, char *string)
{
}