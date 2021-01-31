section .data
    gamma db 'sdat' ; Гамма-строка шифрования

section .bss
    buffer resb 100  ; Строка
    size resb 1      ; Размер принятых данных
    t resb 4
    t1 resb 4        ; temp
    t2 resb 4        ;   
    
        
section .text:
    global _start
    
_start:
    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, 100
    int 0x80
    
    lea esi, [buffer]
    mov [size], eax
    
    mov ecx, [size]
    
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
    
;   Гамма-шифрование
    
    lea esi, [buffer]

    mov ecx, [size]
    
loop2:
    push ecx
    
    mov eax, 0
    mov ecx, 0   
    lodsd       
    mov ecx, eax
    
    
    
    mov [t1], esi ; Откладываем адрес исходной строки
    lea esi, [gamma]
    lodsd
    
    xor eax, ecx  ; В EAX результат шифрования
    
    lea edi, [t2] ; Выгружаем из EAX и отправляем на вывод
    stosd

    
    
    mov eax, 4
    mov ebx, 1
    mov ecx, t2
    mov edx, 4
    int 0x80
    
    mov esi, [t1] ; Возвращаем адрес исходной строк
    
    pop ecx
    sub ecx, 3
    loop loop2
    
        
end:
    

    mov eax, 1
    mov ebx, 0
    int 0x80