; boot/boot.asm - Multiboot-compliant bootloader header

section .multiboot
align 4
    dd 0x1BADB002            ; magic number
    dd 0x00                  ; flags
    dd -(0x1BADB002 + 0x00)  ; checksum

section .text
global _start
_start:
    ; This is a dummy entry; actual boot handled by GRUB
    cli
    hlt
