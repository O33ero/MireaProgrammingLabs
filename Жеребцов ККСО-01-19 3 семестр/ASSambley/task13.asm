%macro NEWLINE 0
mov eax, 4
mov ebx, 1
mov ecx, newline
mov edx, 1
int 0x80
%endmacro

section .data:
    data db 'Data: ', 0
    data_l equ $ - data
    
    sizestr db 'Size: ', 0
    size_l equ $ - sizestr
    
    newline db 0xA, 0

section .bss
    size resb 4     ; size of file
    fd resb 4       ; file descriptor
    buffer resb 16  ; 
        
section .text:
    global _start
    
_start:  
    mov eax, 0
    mov [size], eax
    
    pop ebx ; count
    pop ebx ; path
    pop ebx ; arg
    
    mov eax, 5 ; ReadFile
    mov ecx, 2 ; mode = ReadWrite
    int 0x80
    
    mov [fd], eax
    NEWLINE
    
    mov eax, 4
    mov ebx, 1
    mov ecx, data
    mov edx, data_l
    int 0x80
    
p1:
    mov eax, 3
    mov ebx, [fd]
    mov ecx, buffer
    mov edx, 16
    int 0x80
    
    mov edx, eax
    
    mov ebx, [size]
    add ebx, eax
    mov [size], ebx
    
    push eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    int 0x80
    
    pop eax
    
    cmp eax, 16 ; Если считало <10, то файл закончился
    jl print_size
    jmp p1
    
    
    
    
print_size:
    
    NEWLINE
    
    mov eax, 4
    mov ebx, 1
    mov ecx, sizestr
    mov edx, size_l
    int 0x80
    
    
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

    NEWLINE
    
    mov eax, 6
    mov ebx, [fd]
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80