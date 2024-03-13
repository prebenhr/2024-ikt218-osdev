#include <multiboot2.h>
#include <gdt.h>
#include <idt.h>
#include <terminal.h>
#include <io.h>
#include <libc/stdint.h>
#include <libc/stddef.h>

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
    terminalWrite("This is before initIdt\n");
    initIdt();
    terminalWrite("This is after initIdt\n");

    interrupt();

    setColors(RED, 20);
    setColors(BLUE, YELLOW);

    terminalWrite("Hello World \n");
    return kernel_main();
}