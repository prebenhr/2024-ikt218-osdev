#pragma once
#include "libc/stdint.h"

// Defining screen size, the grid size for text
#define width 80
#define height 25

// Colorchart with values for colors.
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define PURPLE 5
#define BROWN 6
#define GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define YELLOW 14
#define WHITE 15

// Declaring the functions used for writing on screen.
void clearScreen();
void setColors(uint16_t background, uint16_t text);
void putc(const char c);
void terminalWrite(const char *string);
void scrollUp();
void newLine();
