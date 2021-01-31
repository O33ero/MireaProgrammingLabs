; Решение основанно на след. факте.
; Чтобы разделить число на число: 
; 1) eax - Делимое
; 2) ebx - Делитель
; 3) edx = 0 
; div ebx
; После:
; 1) eax - частное (результат деления)
; 2) edx - остаток (!!!)

section .bss
    d resb 4     ; Какое-то число, которое нужно вывести
    d_BCD resb 4 ; Упакованное BCD-число 
    t resb 1     ; временная переменная (навсякий случай)
        
section .text:
    global _start
    
_start:
    mov ebx, 0  ; Кладем в стек bool, отвечающий за нули
    push ebx
    
    
    mov eax, 1645
    mov [d], eax    ; теперь в d лежит какое-то число,
                    ; которое мы хотим вывести
                    
   ; Будем собирать упакованное BCD-число в CX
                
p1: ; Единицы
    mov eax, [d]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [d], eax
    
    add cl, dl    

p2: ; Десятки
    mov eax, [d]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [d], eax
    
    mov al, dl
    mov bl,  16
    mul bl
    
    mov dl, al
    add cl, dl  
    
p3: ; Сотни
    mov eax, [d]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [d], eax
    
    add ch, dl    

p4: ; Тысячи
    mov eax, [d]
    mov ebx, 10
    mov edx, 0
    div ebx
    
    mov [d], eax
    
    mov al, dl
    mov bl, 16
    mul bl
    
    mov dl, al
    add ch, dl 
    
p5: ;Вывод BCD-числа, лежащего в CX

    mov [d_BCD], cx
    mov ecx, 0
       
    L1000:; Тысячи
    mov eax, [d_BCD]
    mov ecx, 0
    mov cl, ah
    
    mov eax, ecx
    mov ebx, 16
    mov edx, 0
    div ebx
    
    add al, 0x30
    mov [t], al
    
    cmp al, 0x30
    je L100
    
    
    print1000:
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80
        
        pop ebx
        mov ebx, 1
        push ebx
          
        
    L100:; Сотни
    mov eax, [d_BCD]
    mov ecx, 0
    mov cl, ah
    
    mov eax, ecx
    mov ebx, 16
    mov edx, 0
    div ebx
    
    add dl, 0x30
    mov [t], dl
    
    cmp dl, 0x30
    jne print100
    
    pop ebx
    cmp ebx, 0
    push ebx
    je L10
    
    print100:
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80
        
        pop ebx
        mov ebx, 1
        push ebx
        
        
    L10:; Десятки
    mov eax, [d_BCD]
    mov ecx, 0
    mov cl, al
    
    mov eax, ecx
    mov ebx, 16
    mov edx, 0
    div ebx
    
    add al, 0x30
    mov [t], al
    
    cmp al, 0x30
    jne print10
    
    pop ebx
    cmp ebx, 0
    push ebx
    je L1
    
    print10:
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80
        
        pop ebx
        mov ebx, 1
        push ebx
        
        
    L1:; Единицы
    mov eax, [d_BCD]
    mov ecx, 0
    mov cl, al
    
    mov eax, ecx
    mov ebx, 16
    mov edx, 0
    div ebx
    
    add dl, 0x30
    mov [t], dl
    print1:
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80
 
end:
    mov eax, 1
    mov ebx, 0
    int 0x80