;.686 
;.model flat, c 
;.stack 100h			; stack size
 
	PUBLIC func1
	PUBLIC func2
	PUBLIC func3
	PUBLIC func4_asm_only
	EXTRN c_function:PROC

.data				; vars here
	res		qword	0.0
	buf		qword	31.123
	buf2	qword	0
	buf3	qword	0
	buf4	qword	0
	one8	real8	1.0
	pi_8		real8	3.1415926535
	a4_8	real8	4.0
	a5_8	real8	5.0



.code 
;ExitProcess PROTO STDCALL :DWORD 

;Start:	

;	PUBLIC func1
;___________________________________________________________________________
	func1 PROC inp:real8	
									; inp -> XMM0
									; результат возвращается по ST(0)

		movsd xmm1, qword ptr [buf]
		; сейчас XMM0 = inp (64bit), XMM1 = buf (64bit)
		addsd xmm0, xmm1

		ret		
	func1 ENDP
;___________________________________________________________________________
	func2 PROC inp:real8
									; вызывает внешнюю функцию в c_func.c
									; с передачей полученных параметров
									; inp -> XMM0

		sub rsp, 40
		call c_function
		add rsp, 40
		ret
	func2 ENDP
;___________________________________________________________________________
	func3 PROC ;inp_arr:ptr real8, inp_arr_len:dword
		;	*inp_arr		->	rcx
		;	inp_arr_len		->	rdx
		push rbp
		mov rbp, rsp
		mov r8, rcx
		mov rcx, rdx
		mov r9, 0		; r9 = i = 0
		xor rax, rax
		

		test ecx, ecx
		jz done		; exit on inp_arr_len == 0

;	код добавления 31.123 + i в массив:

;		movsd xmm1, qword ptr [buf2]
;		loop_1:
;			movsd xmm0, qword ptr [buf]
;			addsd xmm0, xmm1
;			movsd qword ptr [r8 + 8 * r9], xmm0
;			inc r9
;			movsd xmm2, qword ptr [one8]
;			addsd xmm1, xmm2
;			loop loop_1

		loop_2:
			movsd xmm0, qword ptr [r8 + 8 * r9]
			
		;	sub rsp, 40
			mov buf2, rcx
			mov buf3, r9
			mov buf4, r8
			sub rsp, 8
			call c_function
			add rsp, 8
			mov rcx, buf2
			mov r9, buf3
			mov r8, buf4
		;	add rsp, 40

			
			movsd qword ptr [r8 + 8 * r9], xmm0
			inc r9
			loop loop_2

		done:

		mov rcx, r8
		pop     rbp
		ret
	func3 ENDP
;___________________________________________________________________________
	func4_asm_only PROC
		;	*inp_arr		->	rcx
		;	inp_arr_len		->	rdx
		finit

		push rbp
		mov rbp, rsp
		mov r8, rcx
		mov rcx, rdx
		mov r9, 0		; r9 = i = 0
		xor rax, rax
		

		test ecx, ecx
		jz done		; exit on inp_arr_len == 0


		loop_2:
			movsd xmm0, qword ptr [a4_8]
			movsd xmm1, qword ptr [a5_8]
			movsd xmm2, qword ptr [a4_8]
			mulsd xmm2, xmm2
			movsd xmm3, qword ptr [pi_8]
			; inp[i] -> xmm4
			movsd xmm4, qword ptr [r8 + 8 * r9]
			subsd xmm3, xmm4
			mulsd xmm2, xmm3
			mulsd xmm2, xmm4	; xmm2 <- числитель
								; xmm4 <- inp[i]

			movsd xmm0, qword ptr [pi_8]
			subsd xmm0, xmm4
			movsd xmm1, qword ptr [a4_8]
			mulsd xmm0, xmm1
			mulsd xmm0, xmm4	; xmm0 <- правая часть

			movsd xmm1, qword ptr [a5_8]
			movsd xmm3, qword ptr [pi_8]
			mulsd xmm3, xmm3
			mulsd xmm3, xmm1
								; xmm3 <- левая часть

			subsd xmm3, xmm0
			divsd xmm2, xmm3







			


			
			movsd qword ptr [r8 + 8 * r9], xmm2
			inc r9
			loop loop_2

		done:

		mov rcx, r8
		pop     rbp
		ret
	func4_asm_only ENDP
;___________________________________________________________________________


;exit: 				; end code

;Invoke ExitProcess,1 
End ;Start