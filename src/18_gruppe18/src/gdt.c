// Inspired by OsDev.org and OliveStem on Youtube(https://www.youtube.com/@olivestemlearning)

#include <libc/stdint.h>
#include <gdt.h>

// Telling the compiler that there is a function elsewhere (in the assembly code).
extern void flush_gdt(addr_t);

// Declare an array of GDT entry structs with room for 5 entries in the GDT.
struct gdt_entry gdt_entries[5];

// Declare a GDT pointer struct.
struct gdt_pointer gdt_ptr;

/*Function to create entries in the GDT
 * This function will split up the base, limit and flags, and place them in the correct positions in the segment descriptor.
 * It takes as input an index, 32-bit base address, 32-bit limit (will be explained), 8-bit access byte, and 8 bits for the flags.
 * Now, there is only room for 64-bits in the struct so there is some bitshifting that needs to be done.
 */
void createGdtEntry(uint32_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    // Taking the base and ANDing it with 16 ones will give the lower 16-bits of the base.
    gdt_entries[index].base_low = (base & 0xFFFF);

    // Shifting the base 16 bits to the right makes the 17th bit the lowest.
    // Then ANDing with 8 ones gives the 8 bits from the middle of base and up to 3/4.
    gdt_entries[index].base_mid = ((base >> 16) & 0xFF);

    // Finally shifting 24 bits to the right and ANDing with 8 ones for the most significant 8 bits.
    gdt_entries[index].base_high = ((base >> 24) & 0xFF);

    // Taking the limit and ANDing it with 16 ones will give the lower 16-bits of the limit.
    gdt_entries[index].limit = (limit & 0xFFFF);

    // Shifting the limit 16 bits to the right makes the 17th bit the lowest,
    // and it is ANDed with 4 ones to add the last 4 bits of the limit to the lower part of the flags byte.
    gdt_entries[index].flags = ((limit >> 16) & 0xF);

    // Using OR EQUALS (|=) makes the lower 4 bits of flags remain unchanged when ANDing flags byte with 11110000.
    gdt_entries[index].flags |= (flags & 0xF0);

    // Access byte is just added as is.
    gdt_entries[index].access = access;
}

/*Function to initialize the GDT.
 * First, the GDT pointer base is set with the address of the GDT entries struct.
 * Then the limit is calculated as the size of 5 GDT entry structs minus one (because zero counts).
 * The GDT entries are created using the createGdtEntry function, making user and kernel segments.
 * They are completely overlapping.
 */
void gdtInit()
{
    gdt_ptr.base = ((addr_t)&gdt_entries);
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 5) - 1;

    // Mandatory NULL segment
    createGdtEntry(0, 0, 0, 0, 0);

    // Access byte defines what kind of segment this is. 0x9A is 10011010. This is the kernel data segment.
    createGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 0x92 is 10010010. This is the kernel code segment.
    createGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // 0xFA is 11111010. This is the user data segment.
    createGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);

    // 0xF2 is 11110010. This is the user code segment.
    createGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // Finally the assembly code is called to set the address of the new GDT.
    flush_gdt(&gdt_ptr);
}