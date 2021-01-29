section .bss
	x resb 3 ; резервируем 3 байта

section .test:
	global _start

_start:
	mov eax, 3
	mov ebx, 0
	mov ecx, x
	mov edx, 3
	int 0x80

	mov eax, 4
	mov ebx, 1
	mov ecx, x
	mov edx, 3
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80