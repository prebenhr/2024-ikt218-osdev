#include <isr.h>
#include <terminal.h>

void isr_handler(registers_t r)
{
    terminalWrite("Interrupt received: ");
    terminalWrite("Some error codddeee!!");
    terminalWrite("\n");
    terminalWrite(exception_messages[r.int_no]);
    terminalWrite("\n");
    return;
}