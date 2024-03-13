#pragma once
#include "libc/stdint.h"

// 64-bit structure for a gate descriptor.
struct idt_entry
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_high;
} __attribute__((packed));

struct idt_pointer
{
    uint16_t size;
    uint32_t base;
} __attribute__((packed));

void initIdt();
void createIdtEntry(int index, void *offset, uint8_t attributes);