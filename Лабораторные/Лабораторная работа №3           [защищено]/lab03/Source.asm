.686 
.model flat, stdcall 
.stack 100h			; stack size
 
.data				; vars here
	res		word 0									; результат вычислений (сумма подходящих элементов массива)
	arr		word 13, 29, 221, 5389, 12345, 56789, 45, 0, 1024, 255, 43690, 32768, 8191			; массив
	N		word 13									; размер массива
	test_v	word 13									; значение для сравнения (13 = 1101b)
	
	buf		word 0									; буферная переменная
	buf2	word 0									; буферная переменная
	on_add	word 0									; флаг при добавлении элемента массива в сумму
 
.code 
ExitProcess PROTO STDCALL :DWORD 

Start:				; start code
					
	call INIT


	mov esi, offset arr	
	cld

	mov cx, N

	loop1:
		lodsw
		mov bx, ax
		mov buf2, bx

		xor eax, eax
		xor edx, edx
		mov dx, 13		; 16 - 4 + 1 = 13 возможных расположений комбинации "1101" в 2-байтном числе
		loop2:
			mov buf, bx
			and buf, 00001111b	; остаются только 4 мл. бита
			
			call math_func_1	; вызов функции проверки

			bt word ptr [on_add], 0		; CF = 1, если on_add == 1, т.е. если элемент массива был добавлен в сумму
			jc on_continue

			sar bx, 1	; арифметический сдвиг вправо
			dec dx
			mov on_add, 0
			cmp edx, 0
			jne loop2

			on_continue:
		loop loop1

		mov ax, res

		
	ret		; end of algorithm






; функции:
	;_________________________________________________________________________
		INIT PROC ;uses eax ebx ecx edx esi
						; функция первичной настройки

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
						; нужно проверить, равенство ST(0) комбинации "1101"
					
			fild word ptr [test_v]	; загрузка buf в ST(0)
			fild word ptr [buf]	; загрузка buf в ST(0)
			fcompp	; сравнение ST(0) (сравниваемое) и ST(1) (тестовое значение)
			fstsw ax
			sahf	; переписать процессорные флаги на флаги FPU

			je on_equal	; если ZF == 1, что значит C3 == 1
			ret

			on_equal:
				mov dx, buf2
				add res, dx
				inc on_add
			ret
		math_func_1 ENDP
	;_________________________________________________________________________

exit: 				; end code

Invoke ExitProcess,1 
End Start