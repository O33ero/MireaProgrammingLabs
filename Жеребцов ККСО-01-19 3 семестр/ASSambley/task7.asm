section .data:
    filename db 'file.txt', 0

section .bss
    buffer resb 10  ; буффер для высасывания
    fd resb 4       ;
    size resb 1     ; Размер
        
section .text:
    global _start
    
_start:
    
    mov eax, 5
    mov ebx, filename
    mov ecx, 0
    mov edx, 0
    int 0x80
       
    
    
    
    mov [fd], eax   ; Файловый дескриптор (ввод)
  
    
p1:
    ; Высасываение из файла
    mov eax, 3
    mov ebx, [fd]
    mov ecx, buffer
    mov edx, 10
    int 0x80
    
    
    ; Вывод в консоль
    add [size], eax
    
    ; Проверка, что файл закончился (в EAX хранится кол-во считанных
    ; байт, если их <10, значит файл закончился)
    cmp eax, 10
    jl end ; Закончили
    jmp p1 ; Повтори высасывание
    
    
end:
    mov eax, [size]
    add eax, 0x30
    mov [size], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, size
    mov edx, 1
    int 0x80
    
    
    mov eax, 6
    mov ebx, [fd]
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80
