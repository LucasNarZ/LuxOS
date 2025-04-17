section .multiboot
align 4
    dd 0x1BADB002    ; magic number
    dd 0x00          ; flags
    dd -(0x1BADB002) ; checksum

section .text
global start
extern main
start:
    call main
.halt:
    jmp .halt
