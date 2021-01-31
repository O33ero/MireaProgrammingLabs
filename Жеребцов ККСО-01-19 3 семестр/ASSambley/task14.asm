section .data:
    filename db '1.bin', 0

section .bss
    size resb 4     ; size of file
    fd resb 4       ; file descriptor
    buffer resb 16  ; 
        
section .text:
    global _start
    
_start:  
    
    mov ecx, 4
    mov eax, 241321
    mov [size], eax
    
    
    
    ; В size лежит размер файла в байт. 
    mov ecx, 0
loop1:

    add ecx, 1
    
    mov eax, [size]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [size], eax
    
    mov ebx, edx
    push ebx
    
    
    cmp eax, 0
    je break
    jmp loop1

break:
    pop ebx
loop2:
   
    push ecx
    push edx
     
    pop ebx
    add ebx, 0x30
    mov [size], ebx
    
    mov eax, 4
    mov ebx, 1
    mov ecx, size
    mov edx, 1
    int 0x80
    
    pop ecx
    pop edx
    
    
    loop loop2
    
end:

    mov eax, 1
    mov ebx, 0
    int 0x80