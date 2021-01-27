section .data:
    file_in db 'file.txt', 0
    file_out db 'out.txt', 0

section .bss
    buffer resb 10 ; буффер для высасывания
    fd_in resb 4   ;
    fd_out resb 4  ;
        
section .text:
    global _start
    
_start:
    
    mov eax, 5
    mov ebx, file_in
    mov ecx, 0
    int 0x80
    
    mov [fd_in], eax   ; Файловый дескриптор (ввод)
    
    mov eax, 8
    mov ebx, file_out
    mov ecx, 420
    int 0x80
    
    mov [fd_out], eax   ; Файловый дескриптор (вывод)
    
p1:
    mov eax, 3
    mov ebx, [fd_in]
    mov ecx, buffer
    mov edx, 10
    int 0x80
    
    
    ; Вывод в консоль (для проверки корректности)
    mov edx, eax
    
    pop eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    int 0x80
    
    push eax
    ; Перекачка в out
    
    
    mov edx, eax
    
    pop eax
    mov eax, 4
    mov ebx, [fd_out]
    mov ecx, buffer
    int 0x80
    
    push eax
    
    
    ; Проверка, что файл закончился
    cmp eax, 10
    jl end
    jmp p1
    
    
end:
    mov eax, 6
    mov ebx, [fd_in]
    int 0x80
    
    mov eax, 6
    mov ebx, [fd_out]
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80

    