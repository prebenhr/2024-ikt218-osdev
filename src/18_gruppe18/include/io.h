#pragma once
#include <libc/stdint.h>

#define PIC_MAIN_CONTROL 0x20
#define PIC_MAIN_DATA 0x21
#define PIC_SEC_CONTROL 0xA0
#define PIC_SEC_DATA 0xA1

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void wait_for_interrupt(void);
void cli(void);