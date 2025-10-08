[BITS 32]

global gdt_flush
gdt_flush:
    ; EAX = ponteiro para gdt_ptr
    lgdt [eax]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Far jump para atualizar CS
    jmp 0x08:flush_done
flush_done:
    ret

