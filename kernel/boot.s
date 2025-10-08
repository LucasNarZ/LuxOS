global _start
section .multiboot
align 4
dd 0x1BADB002
dd 0x00
dd -(0x1BADB002)
section .text
extern main
_start:
    call main
.halt:
    jmp .halt

