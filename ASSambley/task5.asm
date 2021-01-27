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
    
p1:
    ; Высасываение из файла
    mov eax, 3
    mov ebx, [fd]
    mov ecx, buffer
    mov edx, 10
    int 0x80
    
    
    ; Вывод в консоль
    mov edx, eax
    
    pop eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    int 0x80
    
    push eax
    
    ; Проверка, что файл закончился (в EAX хранится кол-во считанных
    ; байт, если их <10, значит файл закончился)
    cmp eax, 10
    jl end ; Закончили
    jmp p1 ; Повтори высасывание
    
    
end:
    mov eax, 6
    mov ebx, [fd]
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80

    