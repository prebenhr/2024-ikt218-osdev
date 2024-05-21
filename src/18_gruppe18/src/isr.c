#include <isr.h>
#include <terminal.h>
#include <io.h>

const char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Programmable Interrupt Timer Interrupt",
    "Keyboard Interrupt",
    "Cascade",
    "COM2",
    "COM1",
    "LPT2",
    "Floppy Disk",
    "LPT1",
    "CMOS real-time clock",
    "Free for peripherals / legacy SCSI / NIC",
    "Free for peripherals / SCSI / NIC",
    "Free for peripherals / SCSI / NIC",
    "PS2 Mouse",
    "FPU / Coprocessor / Inter-processor",
    "Primary ATA Hard Disk",
    "Secondary ATA Hard Disk"};

isr_t interrupt_handlers[256];

void set_isr_handler(uint8_t int_no, isr_t handler)
{
    interrupt_handlers[int_no] = handler;
}

void isr_handler(registers_t r)
{
    printf("Interrupt received: ");
    printf("%d", r.err_code);
    printf("\n");

    printf(exception_messages[r.int_no]);
    printf("\n");
    return;
}
