// Inspired by OsDev.org and James Molloy's tutorial (https://archive.is/dWJGu)

#include <isr.h>
#include <io.h>
#include <terminal.h>
#include <pit.h>
#include <keyboard.h>

void initIrq()
{
    set_isr_handler(IRQ0, &pit_handler);
    set_isr_handler(IRQ1, &keyboard_handler);
}

void irq_handler(registers_t r)
{
    if (r.int_no >= 40)
    {

        outb(PIC_SEC_CONTROL, 0x20);
    }

    outb(PIC_MAIN_CONTROL, 0x20);

    if (interrupt_handlers[r.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
    else
    {
        printf("Interrupt received! Type: %s \nInterrupt number: %d  -  %s\n%s", r.int_no >= 32 ? "IRQ" : "Software Interrupt", r.int_no, exception_messages[r.int_no], ((r.int_no == 8 || (r.int_no >= 10 && r.int_no < 15)) && r.err_code != 0) ? "Error code: " : "");
    }
}