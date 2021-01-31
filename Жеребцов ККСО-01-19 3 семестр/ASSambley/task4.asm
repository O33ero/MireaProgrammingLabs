section .data:
    filename db 'file.txt', 0

section .bss
    buffer resb 10
    fd resb 4
        
section .text:
    global _start
    
_start:
    
    mov eax, 5
    mov ebx, filename
    mov ecx, 0
    int 0x80
    
    mov [fd], eax   ; Файловый дескриптор
    
    mov eax, 3
    mov ebx, [fd]
    mov ecx, buffer
    mov edx, 10
    int 0x80
    
    mov edx, eax
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    int 0x80
    
    mov eax, 6
    mov ebx, [fd]
    int 0x80
    
    
    
end:
    mov eax, 1
    mov ebx, 0
    int 0x80
    