section .text
global _start

_start:
    mov rax, rcx    ; RCX = address shellcode
    call rax        ; call shellcode
    ret