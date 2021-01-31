section .bss
    buffer resb 10  ; 
        
section .text:
    global _start
    
_start:
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 100
    int 0x80
    
    lea esi, [buffer]
    mov ecx, eax
    
loop1:
    push ecx

    
    mov eax, 4
    mov ebx, 1
    mov ecx, esi
    mov edx, 1
    int 0x80
    
    add esi, 1 
    
    
    pop ecx
    loop loop1
    
        
end:

    mov eax, 1
    mov ebx, 0
    int 0x80