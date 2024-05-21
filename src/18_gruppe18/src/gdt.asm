;Inspired by OsDev.org and OliveStem on Youtube(https://www.youtube.com/@olivestemlearning)

;Tells the compiler that this function should be available from other parts of the code. 
global flush_gdt

;Function to set the new GDT
flush_gdt:
    ;First we move the first and only argument, the address of the gdt pointer struct, located at the stack pointer with at 4 byte offset, into the accumulator register eax. 
    mov eax, [esp + 4]
    ;Then we load the gdt using lgdt with the contents of the accumulator.
    lgdt [eax]
    ;We do a long jump to 0x08, transfering control to the code segment, and going to the .flush label in the code.
    jmp 0x08:.flush

;From here, a stand-in address for the data segment is moved to the accumulator register, and then copied to all the segments. Finally it returns from assembly.
.flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret


    


