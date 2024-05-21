#include "terminal.h"
#include "libc/stdint.h"
#include "libc/stdarg.h"
#include "libc/stdbool.h"

int col = 0;
int row = 0;

// Setting pointer to start of video memory.
uint16_t *const vid = (uint16_t *const)0xB8000;
// Setting default color scheme, gray on black.
uint16_t const defaultColor = (BLACK << 12) | (GRAY << 8);
uint16_t selectedColor = defaultColor;

void monitorInitialize()
{
}

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

void disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void move_cursor(int x, int y)
{
    uint16_t pos = y * width + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

// Function to write to screen. Takes in a string and writes it on the screen.
// If the string contains a newline, the newLine function is called.
void terminalWrite(const char *string)
{
    char *ptr = string;

    while (*ptr != 0x00 && *ptr != '\0')
    {
        if (*ptr == '\n')
        {
            newLine();
            *ptr++;
            continue;
        }
        if (*ptr == '\b')
        {
            backSpace();
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
    move_cursor(col, row);
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
    move_cursor(col, row);
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
    move_cursor(col, row);
}

void backSpace()
{
    if (col != 0)
    {
        col--;
        terminalWrite("  ");
        col--;
        col--;
        move_cursor(col, row);
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

    move_cursor(col, row);
}

// itoa() implementation from https://www.geeksforgeeks.org/implement-itoa/

char *citoa(int num, char *str, int base)
{
    int i = 0;
    bool isNegative = false;

    // Print 0 as value
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Check if number is negative
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        end--;
        start++;
    }

    return str;
}

// printf() implementation to print formatted strings.
void printf(const char *str, ...)
{
    va_list ptr;
    va_start(ptr, str);

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '%' && str[i] != '\0')
        {
            char singleChar[2] = {str[i], '\0'};
            terminalWrite(singleChar);
        }

        else if (str[i] == '%' && (str[i + 1] == 'i' || str[i + 1] == 'd'))
        {
            int num = va_arg(ptr, int);
            char digits[11];
            citoa(num, digits, 10);
            terminalWrite(digits);

            i = i + 1;
        }
        else if (str[i] == '%' && str[i + 1] == 's')
        {
            char *s = va_arg(ptr, char *);
            terminalWrite(s);

            i++;
        }
        else if (str[i] == '%' && str[i + 1] == 'x')
        {
            int num = va_arg(ptr, int);
            char digits[9];
            citoa(num, digits, 16);
            terminalWrite(digits);

            i = i + 1;
        }

        else
        {
            break;
        }
    }
    va_end(ptr);
}