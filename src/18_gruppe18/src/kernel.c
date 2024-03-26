#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <terminal.h>
#include <io.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include <libc/stdbool.h>
#include <isr.h>
#include <pit.h>

extern void interrupt();
extern uint32_t end;

struct multiboot_info
{
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

int main(uint32_t magic, struct multiboot_info *mb_info_addr)
{
    gdtInit();
    printf("This is %d before initIdt\n", 7283234);
    initIdt();
    printf("This is after initIdt\n");

    initPit(TARGET_FREQUENCY);
    initKeyboard();
    int counter = 0;
    while (true)
    {
        printf("[%d]: Sleeping with busy-waiting (HIGH CPU).\n", counter);
        sleep_busy(1000);
        printf("[%d]: Slept using busy-waiting.\n", counter++);

        printf("[%d]: Sleeping with interrupts (LOW CPU).\n", counter);
        sleep_interrupt(1000);
        printf("[%d]: Slept using interrupts.\n", counter++);
    };
    while (1)
    {
    };

    setColors(RED, 20);
    setColors(BLUE, YELLOW);

    printf("Hello World \n");
    return kernel_main();
}