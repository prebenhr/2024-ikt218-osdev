#include "libc/stdint.h"

struct gdt_entry
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_pointer
{
    uint16_t limit;
    unsigned int base;
} __attribute__((packed));

void gdtInit();
void createGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
