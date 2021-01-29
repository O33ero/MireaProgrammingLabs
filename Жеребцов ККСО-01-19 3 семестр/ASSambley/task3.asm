section .bss
	a resb 1 ; резервируем 1 байт
	b resb 1 ;
	r resb 1 ; a + b = r
        o resb 1;

section .text:
	global _start

_start:
	mov eax, 3
	mov ebx, 0
	mov ecx, a
	mov edx, 1
	int 0x80

	mov eax, 3
	mov ebx, 0
	mov ecx, b
	mov edx, 1
	int 0x80
	
        mov eax, [a]
        mov ebx, [b]

	sub eax, 0x30 	; acii -> digit
	sub ebx, 0x30	; acii -> digit

	add eax, ebx	; a + b, in EAX contain result
	
	add eax, 0x30
	mov [r], eax
	sub eax, 0x30

	cmp al, 9
	jg grad

        

less:
	
	mov eax, 4
	mov ebx, 1
	mov ecx, r
	mov edx, 1
	int 0x80

	jmp end

grad:
	
        mov ebx, '1'
        mov [o], ebx
  
        
        mov eax, 4
	mov ebx, 1
	mov ecx, o
	mov edx, 1
        int 0x80
        
        mov eax, [r]
        sub eax, 10
        mov [r], eax
        
        
	mov eax, 4
	mov ebx, 1
	mov ecx, r
	mov edx, 1
	int 0x80

	jmp end



end:
	mov eax, 1
	mov ebx, 0
	int 0x80