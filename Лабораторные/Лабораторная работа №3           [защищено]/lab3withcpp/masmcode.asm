;.686 
;.model flat, c 
;.stack 100h			; stack size
 
	PUBLIC asm_func_1

.data				; vars here
	res		word	0

	buf		word 0				; �������� ����������
	buf2	word 0				; �������� ����������
	on_add	word 0				; ���� ��� ���������� �������� ������� � �����
	test_v	word 13				; �������� ��� ��������� (13 = 1101b)



.code 
;ExitProcess PROTO STDCALL :DWORD 

;Start:	
	
	
	
	
	
	
	
	
	
	
;___________________________________________________________________________
	asm_func_1 PROC	; I par. = *arr, II par. = arr_len, III par. = *res

					;	I param		->	rcx
					;	II param	->	rdx
					;	III param	->	r8
					;	IV param	->	r9

					; output(int)	<-	rax

		mov r10, rcx
		mov r11, rdx
		;mov r12, 0		; r12 = i = 0
		xor rax, rax

		sub rsp, 40
		
		
		;movss xmm0, dword ptr [buf]
		call arr_proc_func	; result -> rax

			
		add rsp, 40
		ret			; output(int) <- rax	
	asm_func_1 ENDP
;_________________________________________________________________________
	arr_proc_func PROC
					;	*arr		in	r10
					;	arr_len		in	r11
					;	result		->	rax
		call INIT
		
		;mov esi, offset arr	
		mov rsi, r10	; *arr
		cld

		mov rcx, r11		; arr_len

		loop1:
			lodsw
			mov bx, ax
			mov buf2, bx

			xor eax, eax
			xor edx, edx
			mov dx, 13		; 16 - 4 + 1 = 13 ��������� ������������ ���������� "1101" � 2-������� �����
			loop2:
				mov buf, bx
				and buf, 00001111b	; �������� ������ 4 ��. ����
			
				call math_func_1	; ����� ������� ��������

				bt word ptr [on_add], 0		; CF = 1, ���� on_add == 1, �.�. ���� ������� ������� ��� �������� � �����
				jc on_continue

				sar bx, 1	; �������������� ����� ������
				dec dx
				mov on_add, 0
				cmp edx, 0
			jne loop2

				on_continue:
		loop loop1

			mov ax, res

		
		ret
	arr_proc_func ENDP
;_________________________________________________________________________
	INIT PROC ;uses eax ebx ecx edx esi
					; ������� ��������� ���������

		finit	; math proc (FPU) initialization w/out waiting (NO-WAIT)
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx
		xor esi, esi


		ret
	INIT ENDP
;_________________________________________________________________________
	math_func_1 PROC
					; ����� ���������, ��������� ST(0) ���������� "1101"
					
		fild word ptr [test_v]	; �������� buf � ST(0)
		fild word ptr [buf]	; �������� buf � ST(0)
		fcompp	; ��������� ST(0) (������������) � ST(1) (�������� ��������)
		fstsw ax
		sahf	; ���������� ������������ ����� �� ����� FPU

		je on_equal	; ���� ZF == 1, ��� ������ C3 == 1
		ret

		on_equal:
			mov dx, buf2
			add res, dx
			inc on_add
		ret
	math_func_1 ENDP
;_________________________________________________________________________



;exit: 				; end code

;Invoke ExitProcess,1 
End ;Start