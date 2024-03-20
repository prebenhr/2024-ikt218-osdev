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

const char defaultLookup[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',   // 0x00 to 0x0F
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',  // 0x10 to 0x1F
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', // 0x20 to 0x2F
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,                 // 0x30 to 0x3F
    0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',               // 0x40 to 0x4F
    '2', '3', '0', '.'                                                              // 0x50 to 0x53
};

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

void irq_handler(registers_t r)
{
    if (r.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);
    // printf("Interrupt: %d", r.int_no);
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

void initKeyboard()
{
    set_isr_handler(IRQ1, &keyboard_handler);
}

void keyboard_handler(registers_t r)
{
    uint8_t input = inb(0x60);
    if (input < 0x53)
    {
        char c[2] = {defaultLookup[input], '\0'};
        terminalWrite(c);
    }
    // char string[2] = {input, '\0'};
    // terminalWrite(string);
}