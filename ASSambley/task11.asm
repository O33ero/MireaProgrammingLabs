; Наверника, есть проще решение, но это тоже рабочее и 
; масштабируется под любые числа


section .bss
    d resb 4 ; Какое-то число, которое нужно вывести
    b resb 1 ; boolean-переменная, отвечающая за нули
    t resb 1 ; временная переменная (навсякий случай)
        
section .text:
    global _start
    
_start:
    
    mov eax, 100
    mov [d], eax    ; теперь в d лежит какое-то число,
                    ; которое мы хотим вывести
    
    mov eax, 0
    mov [b], eax
                    
    ; Тысячи                                                
    mov eax, [d]
    mov ebx, 1000
    mov edx, 0
    div ebx
    
    mov [d], edx
    
    mov [b], ecx
    cmp ecx, 0
    jne print1000
    
    cmp eax, 0
    jne print1000
    jmp p1
    
print1000:
    add eax, 0x30
    mov [t], eax
    
    
    mov eax, 4
    mov ebx, 1
    mov ecx, t
    mov edx, 1
    int 0x80
    
    mov eax, 1
    add [b], eax ; Если есть значащий знак, то 0 напечатается,
                 ; иначе - нет. Т.е. 100 - напечатает, 0100 - нет
    
    
    ; /////////////////
p1:
    ; Сотни
    mov eax, [d]
    mov ebx, 100
    mov edx, 0
    div ebx
    
    mov [d], edx
    
    mov [b], ecx
    cmp ecx, 0
    jne print100
    
    ; Тысячи
    cmp eax, 0
    jne print100
    jmp p2
    
print100:
    add eax, 0x30
    mov [t], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, t
    mov edx, 1
    int 0x80
    
    mov eax, 1
    add [b], eax
    
    ; /////////////////
p2:
    ; Десятки
    mov eax, [d]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [d], edx
    
    mov [b], ecx
    cmp ecx, 0
    jne print10
    
    cmp eax, 0
    jne print10
    jmp p3
    
print10:
    add eax, 0x30
    mov [t], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, t
    mov edx, 1
    int 0x80
    
    mov eax, 1
    add [b], eax
    
    ; ////////////////////////
p3:
    ; Единицы
    mov eax, [d]
    
    mov [b], ecx
    cmp ecx, 0
    jne print1
    
    cmp eax, 0
    jne print1
    jmp end
    
print1:
    add eax, 0x30
    mov [t], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, t
    mov edx, 1
    int 0x80
    
    mov eax, 1
    add [b], eax
    
end:
    mov eax, 1
    mov ebx, 0
    int 0x80