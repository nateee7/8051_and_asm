.686 
.model flat,stdcall 
 
.stack 100h			; stack size
 
.data				; vars here
	X dw 3
	Y dw 0
	Z dw 12
 
.code 
ExitProcess PROTO STDCALL :DWORD 
					; Task:
					;	M = (Y/2) or (X*Z`) + (X*Y`)
					;		 [1] [4]  [2]  [5] [3]
					;	M =  edx  or  ebx   +  ecx
Start:				
					; начало кода
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	
; [1] there:
	mov ax, Y
	sar ax, 1	; div by 2 via shift right by 1
	mov dx, ax
; [2] there:
	not Z
	mov ax, X
	mov bx, Z
	mul ebx
	mov ebx, eax
; [3] there:
	xor eax, eax
	not Y
	mov ax, Y
	mov cx, X
	mul ecx
	mov ecx, eax
; [4] there:
	or edx, ebx
; [5] there:
	add edx, ecx
					; конец кода
exit: 				
Invoke ExitProcess,1 
End Start