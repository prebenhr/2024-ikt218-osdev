#pragma once
#include <libc/stdint.h>
#include <isr.h>

void initIrq();
void irq_handler(registers_t r);