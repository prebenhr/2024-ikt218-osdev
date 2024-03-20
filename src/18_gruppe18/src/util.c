#include <util.h>
#include <libc/stdint.h>

void memset(void *start, char val, uint32_t size)
{
    char *temp = (char *)start;
    for (uint32_t i = 0; i < size; i++)
    {
        *temp = val;
        *temp++;
    }
}