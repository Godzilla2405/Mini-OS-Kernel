// scripts/linker.ld

ENTRY(_start)

SECTIONS {
    . = 0x100000; /* Kernel load address (1MB) */
    
    .text : {
        *(.text)          /* All code goes here */
    }

    .data : {
        *(.data)          /* Data section goes here */
    }

    .bss : {
        *(.bss)           /* BSS section goes here */
    }

    .rodata : {
        *(.rodata)        /* Read-only data section goes here */
    }

    . = ALIGN(0x1000);  /* Align the stack and heap */

    .stack : {
        . = . + 0x1000;   /* Stack space (4KB) */
    }

    .heap : {
        . = . + 0x2000;   /* Heap space (8KB) */
    }
}
