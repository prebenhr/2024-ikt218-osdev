#include <libc/stdint.h>
#include <idt.h>
#include <io.h>
#include <util.h>

extern void flush_idt(addr_t);
extern void *isr_stub_table[];
extern void *irq_stub_table[];

struct idt_entry idt_entries[256] __attribute__((aligned(0x10)));
struct idt_pointer idt_ptr;

void remapPIC()
{

    uint8_t a1, a2;

    a1 = inb(PIC_MAIN_DATA);
    a2 = inb(PIC_SEC_DATA);
    outb(PIC_MAIN_CONTROL, 0x11);
    outb(PIC_SEC_CONTROL, 0x11);

    outb(PIC_MAIN_DATA, 0x20);
    outb(PIC_SEC_DATA, 0x28);

    outb(PIC_MAIN_DATA, 0x04);
    outb(PIC_SEC_DATA, 0x02);

    outb(PIC_MAIN_DATA, 0x01);
    outb(PIC_SEC_DATA, 0x01);

    outb(PIC_MAIN_DATA, 0x0);
    outb(PIC_SEC_DATA, 0x0);

    outb(PIC_MAIN_DATA, a1);
    outb(PIC_SEC_DATA, a2);
}

void initIdt()
{
    idt_ptr.base = ((addr_t)&idt_entries);
    idt_ptr.size = (sizeof(struct idt_entry) * 256) - 1;

    memset(&idt_entries, 0, sizeof(struct idt_entry) * 256);

    remapPIC();

    for (int i = 0; i < 32; i++)
    {
        createIdtEntry(i, isr_stub_table[i], 0x8E);
    }
    for (int i = 0; i < 16; i++)
    {
        createIdtEntry(i + 32, irq_stub_table[i], 0x8E);
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