section .data:
    str1 db '1', 0
    str2 db '8', 0

section .bss
    one resb 1 ; 
    r resb 1 ;
    t resb 1 ;
        
section .text:
    global _start
    
_start:
    mov eax, '1'
    mov [one], eax
    ;pop ebx ;count
;    pop ebx ;path
;    pop ebx ;a_BCD
    
p1: ; 1-e ЧИСЛО

    lea esi, [str1] ; копируем адрес 1 символа str1
    lodsb           ; заносим в AL
    sub al, 0x30    ; берем значение
    mov bl, al      ; записали в младший байт BL
    
    lea esi, [str1+1]
    lodsb
    cmp al, 0
    je case2
    jmp case1
    
    
case1: ; 2-значное число
    sub al, 0x30
    mov bh, al      ; записали в старший байт BH
    xchg bh, bl     ; поменяли местами BL и BH
    
    rol bh, 4       ; упакавали
    add bl, bh      ; теперь в BL лежит упакованное str1
    
    jmp p2

case2: ; 1-значное число 
    mov bh, al      ; записали в старший байт BH

    ; упаковывать не надо, потому что уже запаковано
    
p2: ; 2-e ЧИСЛО

    lea esi, [str2] ; копируем адрес 1 символа str2
    lodsb           ; заносим в AL
    sub al, 0x30    ; берем значение
    mov cl, al      ; записали в младший байт BL
    
    lea esi, [str2+1]
    lodsb
    cmp al, 0
    je case4
    jmp case3
    
    
case3: ; 2-значное число
    sub al, 0x30
    mov ch, al      ; записали в старший байт CH
    xchg ch, cl     ; поменяли местами CL и CH
    
    rol ch, 4       ; упакавали
    add cl, ch      ; теперь в CL лежит упакованное str2
    
    jmp p3

case4: ; 1-значное число
    mov ch, al      ; записали в старший байт CH    
    

    ; упаковывать не надо, потому что уже запаковано

; /////////////////////////////////////////////////////////

p3: ; СЛОЖЕНИЕ в BL - 1-e , в CL - 2-е
    
    mov al, bl
    mov bl, cl
    
    
    adc al, bl
    daa
    
    mov [r], al
    jc m1   ; > 100
    jmp m2  ; < 100
    
m1:
    mov eax, 4
    mov ebx, 1
    mov ecx, one
    mov edx, 1
    int 0x80
    
    
    
m2:
    mov al, [r]
    ror eax, 4
    
    add al, 0x30
    mov [t], al
    
    cmp al, 0
    jne L1
    jmp L2
    
    L1:
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80    ; Десятки
    
    L2:
        mov al, [r]
        btr eax, 7
        btr eax, 6
        btr eax, 5
        btr eax, 4
        
        add al, 0x30
        mov [t], al
        
        mov eax, 4
        mov ebx, 1
        mov ecx, t
        mov edx, 1
        int 0x80    ; Единицы
  
    

    
    

end:

    mov eax, 1
    mov ebx, 0
    int 0x80