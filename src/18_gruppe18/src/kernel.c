#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <terminal.h>
#include <io.h>
#include <libc/stdint.h>
#include <libc/stddef.h>
#include <isr.h>
#include <pit.h>

extern void interrupt();

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
    initPit();
    initKeyboard();
    while (1)
    {
    };

    setColors(RED, 20);
    setColors(BLUE, YELLOW);

    printf("Hello World \n");
    return kernel_main();
}