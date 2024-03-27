#pragma once
#include <libc/stdint.h>

extern const char defaultLookup[];

void initKeyboard();
void keyboard_handler(registers_t r);