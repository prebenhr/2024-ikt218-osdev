#include <libc/stdint.h>
#include <idt.h>

extern void flush_idt(addr_t);
extern void *isr_stub_table[];

struct idt_entry idt_entries[256] __attribute__((aligned(0x10)));
struct idt_pointer idt_ptr;

void initIdt()
{
    idt_ptr.base = ((addr_t)&idt_entries);
    idt_ptr.size = (sizeof(struct idt_entry) * 256) - 1;

    for (int i = 0; i < 32; i++)
    {
        createIdtEntry(i, isr_stub_table[i], 0x8E);
    }

    flush_idt((uint32_t)&idt_ptr);
}

void createIdtEntry(int index, void *offset, uint8_t attributes)
{
    idt_entries[index].offset_low = (uint32_t)offset & 0xFFFF;
    idt_entries[index].offset_high = ((uint32_t)offset >> 16) & 0xFFFF;
    idt_entries[index].segment_selector = 0x08;
    idt_entries[index].reserved = 0;
    idt_entries[index].attributes = attributes;
}