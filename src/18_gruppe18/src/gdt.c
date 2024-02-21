#include "libc/stdint.h"
#include "gdt.h"

extern void flush_gdt(addr_t);

struct gdt_entry gdt_entries[5];
struct gdt_pointer gdt_ptr;

void gdtInit()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;
    gdt_ptr.base = ((addr_t)&gdt_entries);

    createGdtEntry(0, 0, 0, 0, 0);
    createGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    createGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    createGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    createGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    flush_gdt(&gdt_ptr);
}

void createGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdt_entries[index].base_low = (base & 0xFFFF);
    gdt_entries[index].base_mid = ((base >> 16) & 0xFF);
    gdt_entries[index].base_high = ((base >> 24) & 0xFF);

    gdt_entries[index].limit = (limit & 0xFFFF);
    gdt_entries[index].flags = ((limit >> 16) & 0xF);
    gdt_entries[index].flags |= (flags & 0xF0);

    gdt_entries[index].access = access;
}
