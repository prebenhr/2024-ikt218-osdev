#include "libc/stdint.h"

/*Struct for a GDT entry, also known as a segment descriptor.
 * This is a 64-bit struct which contains 32 bits for the base (linear address of the beginning of the segment),
 * 20 bits for the limit (the size of the segment), and 12 bits for some configuration of the segment (access byte and 4 bits for flags).
 * The layout of the struct is predefined, with base and limit split up in different parts, with 4 bits of the limit being the least significant bits of the flags byte.
 * __attribute__((packed)) is used to ensure that the different parts of the struct is stored consecutively in memory without any padding.
 */
struct gdt_entry
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed));

/* Struct for a GDT pointer, which will be used in assembly code to point to the GDT table.
 * The struct contains a 32-bit base (linear address for the GDT table), and a 16-bit limit (size of the table).
 */
struct gdt_pointer
{
    uint16_t limit;
    unsigned int base;
} __attribute__((packed));

// Declaring functions to initialize the GDT and to add a GDT entry to the table.
void gdtInit();
void createGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
