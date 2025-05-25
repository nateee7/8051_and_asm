.686 
.model flat,stdcall 
 
.stack 100h			; stack size
 
.data				; vars here
	X		word	37257
	Y		word	29003
	Z		word	52498
	M		word	0
	R		dword	0
	two		dword	2
	cnt		word	0
 
.code 
ExitProcess PROTO STDCALL :DWORD 
					; Task:
Start:				
					; start code
	xor eax, eax
	xor ebx, ebx
	xor ecx, ecx
	xor edx, edx
	mov dl, 0

;	push word ptr [X]
;	push word ptr [Y]
;	push word ptr [Z]


	mov eax, offset X	; getting address of X

	mov cx, 3
	mov si, 0
	
; Task 1 there:
	loop_s:
		inc eax
		mov [eax], dl	
		inc eax
		inc si
		loop loop_s

; Task 2 there:
	mov bx, Y
	and bx, Z
	add bx, X
	mov M, bx

	cmp ebx, 0

	ja on_larger_then_zero
	; if (M <= 0) {
	xor ebx, 0E130h
	jmp endd
	; }
	; if (M > 0) {
	on_larger_then_zero:
		sub ebx, 04101h
	; }
	endd:
	mov R, ebx	
	
; Task 3 there:
	mov cx, 8	; 8 times for 8 bit in 1 byte
				; R[0] is in bx
	xor eax, eax
	and ebx, 11111111b	; keeping ebx[0] only
	mov ax, bx
	loops_s2:
		div two
		add cnt, dx
		;sar bx, 1
		loop loops_s2
	; now amount of ones is in cnt
	
	;	another way to check if amount of ones in ax is even:
	;
	;	xor ax, 0	; not changing cnt
	;	jpo ...
	;

	mov ebx, R
	test cnt, 1
	jz on_even		; if (cnt % 2 == 0) jmp on_even;
					; else {
	call on_not_even_proc
	jmp endd2
					; }
	on_even:
		call on_even_proc
	jmp endd2

	on_even_proc PROC
		or ebx, 1024
		ret
	on_even_proc ENDP

	on_not_even_proc PROC
		shr ebx, 1		; div by 2
		ret
	on_not_even_proc ENDP

	endd2:
	mov R, ebx
	
					; end code
exit: 				
Invoke ExitProcess,1 
End Start