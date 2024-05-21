#include <util.h>
#include <libc/stdint.h>
#include <terminal.h>

void panic(const char *message)
{

    printf("Panic! %s", message);

    __asm__ volatile("cli \n\t"
                     "hlt");
}