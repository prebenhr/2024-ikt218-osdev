#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include <multiboot2.h>
#include <gdt.h>
#include "../include/terminal.h"

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

    setColors(RED, 20);
    setColors(BLUE, YELLOW);

    terminalWrite("Hello World \nGreetings from NEW YORK!! \n 1\n  2\n   3\n    4\n     5\n      6\n       7\n        8\n         9\n          10");
    return kernel_main();
}