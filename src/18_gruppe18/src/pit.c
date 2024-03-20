#include <libc/stdint.h>
#include <isr.h>
#include <pit.h>

void initPit()
{
    set_isr_handler(IRQ0, &pit_handler);

    // uint32_t divisor = 1193180 / frequency;
}

void pit_handler(registers_t r)
{
    return;
}