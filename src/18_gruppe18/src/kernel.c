#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <terminal.h>
#include <io.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include <libc/stdbool.h>
#include <isr.h>
#include <irq.h>
#include <memory.h>
#include <pit.h>

extern void interrupt();
extern uint32_t end;

struct multiboot_info
{
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

void lineDefault()
{
    setColors(BLACK, BLACK);
    terminalWrite("                  ");
    setColors(RED, BLACK);
    terminalWrite("            ");
    setColors(WHITE, BLACK);
    terminalWrite("  ");
    setColors(BLUE, BLACK);
    terminalWrite("    ");
    setColors(WHITE, BLACK);
    terminalWrite("  ");
    setColors(RED, BLACK);
    terminalWrite("                       ");
    newLine();
}
void lineWhite()
{
    setColors(BLACK, BLACK);
    terminalWrite("                  ");
    setColors(WHITE, BLACK);
    terminalWrite("            ");
    setColors(WHITE, BLACK);
    terminalWrite("  ");
    setColors(BLUE, BLACK);
    terminalWrite("    ");
    setColors(WHITE, BLACK);
    terminalWrite("  ");
    setColors(WHITE, BLACK);
    terminalWrite("                       ");
    newLine();
}
void lineBlue()
{
    setColors(BLACK, BLACK);
    terminalWrite("                  ");
    setColors(BLUE, BLACK);
    terminalWrite("            ");
    setColors(BLUE, BLACK);
    terminalWrite("  ");
    setColors(BLUE, BLACK);
    terminalWrite("    ");
    setColors(BLUE, BLACK);
    terminalWrite("  ");
    setColors(BLUE, BLACK);
    terminalWrite("                       ");
    newLine();
}

void norgesflagg()
{
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
    lineWhite();
    lineBlue();
    lineBlue();
    lineWhite();
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
    lineDefault();
}

int kernel_main();

int main(uint32_t magic, struct multiboot_info *mb_info_addr)
{

    gdtInit();
    // printf("GDT initialized\n");

    initIdt();
    // printf("IDT initialized\n");

    initIrq();

    init_kernel_memory(&end);
    // printf("Kernel memory initialized\n");

    init_paging();
    // printf("Paging initialized\n");
    // printf("Printing memory layout:\n\n");

    // print_memory_layout();

    initPit(TARGET_FREQUENCY);
    // printf("PIT initialized with target frequency of %d Hz\n", TARGET_FREQUENCY);

    /* int counter = 0;
    while (true)
    {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    }; */

    clearScreen();
    disable_cursor();

    return kernel_main();
}