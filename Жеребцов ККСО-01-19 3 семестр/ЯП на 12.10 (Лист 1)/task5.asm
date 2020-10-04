section .bss
	a resb 1
	s resb 80

section .text:
	global _start

_start:
	mov eax, 3
	mov ebx, 0
	mov ecx, s
	mov edx, 80
	int 0x80


	mov byte[s+4], 0x24
	 

	mov eax, 4
	mov ebx, 1
	mov ecx, s
	mov edx, 80
	int 0x80


	mov eax, 1
	mov ebx, 0
	int 0x80
	
 
