section .data:
    filename db 'file.txt', 0

section .bss
    buffer resb 10  ; буффер для высасывания
    fd resb 4       ;
        
section .text:
    global _start
    
_start:
    
    pop ebx ; argc      - число аргументов
    pop ebx ; argv[0]   - путь программы
    pop ebx ; argv[1]   - первый параметр (имя файла для чтения)
    
    mov eax, 5
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
    
    
    mov eax, 6
    mov ebx, [fd]
    int 0x80

    mov eax, 1
    mov ebx, 0
    int 0x80
    