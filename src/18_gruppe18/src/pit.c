// Inspired by OsDev.org and OliveStem on Youtube(https://www.youtube.com/@olivestemlearning)

#include <libc/stdint.h>
#include <libc/limits.h>
#include <isr.h>
#include <pit.h>
#include <io.h>
#include <terminal.h>

uint32_t ticks = 0;

void initPit(uint16_t frequency)
{

    uint16_t divisor = PIT_BASE_FREQUENCY / frequency;
    if (divisor % 2 != 0)
    {
        divisor -= 1;
    }

    outb(PIT_CMD_PORT, 0x36);
    outb(PIT_CHANNEL0_PORT, divisor & 0xFF);
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xFF);
}

void pit_handler(registers_t r)
{
    if (ticks == UINT32_MAX)
        ticks = 0;
    ticks++;
}

uint32_t get_current_ticks()
{
    /* uint16_t ticks = 0;
    cli();
    outb(PIT_CMD_PORT, 0x00);
    uint8_t l = inb(PIT_CHANNEL0_PORT);
    uint8_t h = inb(PIT_CHANNEL0_PORT);
    ticks = l | (h << 8); */
    return ticks;
}

void sleep_busy(uint32_t milliseconds)
{
    uint32_t start_ticks = get_current_ticks();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t elapsed_ticks = 0;
    while (elapsed_ticks < ticks_to_wait)
    {
        /* uint16_t current_ticks = get_current_ticks();
        elapsed_ticks += (current_ticks >= start_ticks) ? (current_ticks - start_ticks) : (UINT16_MAX - start_ticks + current_ticks); */
        while (get_current_ticks() == elapsed_ticks + start_ticks)
        {
        }
        elapsed_ticks++;
    }
}
void sleep_interrupt(uint32_t milliseconds)
{
    uint32_t current_ticks = get_current_ticks();
    uint32_t ticks_to_wait = milliseconds * TICKS_PER_MS;
    uint32_t end_ticks = current_ticks + ticks_to_wait;
    while (current_ticks < end_ticks)
    {
        wait_for_interrupt();
        current_ticks = get_current_ticks();
    }
}