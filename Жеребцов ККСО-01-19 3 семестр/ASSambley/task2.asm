section .bss
	a resb 1 ; резервируем 1 байт
	b resb 1 ;
	r resb 1 ; a + b = r

section .test:
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

	add eax, ebx	; a + b
	
	add eax, 0x30 	; digit -> acii

	mov [r], eax	; = r


	mov eax, 4
	mov ebx, 1
	mov ecx, r
	mov edx, 1
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80
	