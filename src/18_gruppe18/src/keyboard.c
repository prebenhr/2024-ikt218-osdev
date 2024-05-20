// Keyboard scancodes sourced from kbdlayout.info/kbdno/virtualkeys

#include <libc/stdint.h>
#include <isr.h>
#include <io.h>
#include <terminal.h>

const char keyboardScancodes[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '+', '\\', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'å', '¨', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', 'ø', 'æ', '|', 0, '\'', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '-', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',
    '2', '3', '0', '.'};

void keyboard_handler(registers_t r)
{
    uint8_t input = inb(0x60);
    if (input < 0x53)
    {
        char c[2] = {keyboardScancodes[input], '\0'};
        terminalWrite(c);
    }
}