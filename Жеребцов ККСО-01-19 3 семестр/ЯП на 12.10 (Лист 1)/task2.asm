section .bss
	a resb 1
	b resb 1

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
	sub eax, 0x30
	sub ebx, 0x30
	add eax, ebx
	add eax, 0x30
	mov [a], eax

	mov eax, 4
	mov ebx, 1
	mov ecx, a
	mov edx, 1
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80
