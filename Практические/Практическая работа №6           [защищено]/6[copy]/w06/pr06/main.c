#include <8051.h>
#include <string.h>

//const unsigned char* start_address;
const unsigned char* message;
const int N;
int i;
unsigned char cnt;

void init();
void send(unsigned char inp);
void send_ascii(unsigned char inp);
void send_ascii_word(unsigned char* inp);

void main() {
	init();
	
	message = "6766";			// 20 B = 20 символов, CAPS ONLY
	while (1)
		send_ascii_word (message);
						/* readme:		
						/		practice #6
						/ 		IgnatovichVO, INBs3301, #19
						/
						/		Задание:
						/		передать на терминал N байт на 3 режиме со скоростью 4.8 Кбит/с
						/		в адрес 0x30
						/		
						/		
						/		R/T:			T
						/		K:				3
						/		S (kbit/s):		4.8
						/		XX:				0x30	(НЕ ИСПОЛЬЗУЕТСЯ, Т.К. ПЕРЕДАЧА, А НЕ ПРИЁМ)
						/		N:				20
						/			
						*/
}

void init() {
	PCON = 0x00;
	//		R/T:			T
	//		K:				3
	//		S (kbit/s):		4.8
	//		XX:				0x30
	//		N:				20
	
	//	настройка по варианту:
		N = 20;
		SM2 = 1;				// разрешение передачи
		// режим 3 приёмопередатчика:
			SM0 = 1;
			SM1 = 1;		
//		start_address = 0x30;	// адрес начала записи
		PCON_BITS.B7 = 0;		// PCON[7] = SMOD = 0
	
	// настройка таймеросчётчика1:
		TMOD_BITS.B6 = 0;		// TMOD[6] = T/C = 0
		// режим 2 таймеросчётчика1:
			TMOD_BITS.B5 = 1;	// M1 = 1 (для TC1)
			TMOD_BITS.B4 = 0;	// M0 = 0 (для TC1)
			// режим 2: 8-bit автоперезагружаемый счётчик
			// 		при этом TH1->TL1 при переполнении
		TH1 = 0xFA;				// см. "частоты" в "К практике №6"
		TR1 = 1;				// включение таймеросчётчика1
	// прочая настройка:
		P0 = 0x00;
		P1 = 0x00;
		P2 = 0x00;
		P3 = 0x00;
	
}

void send_ascii(unsigned char inp) {
	// 0x45='%' (37), 0x71='1' (49), 0x90='P', 0x6D='-', 0x80='@'
	// 0x81='A'
	// inp address = 0x05
	if (inp - 0x41 >= 0x00 && inp - 0x5A <= 0x00) { 	// if inp is in 'A' .. 'Z'
		inp -= 0x41;
		inp += 0x81;
	}
	if (inp - 0x30 >= 0x00 && inp - 0x3A <= 0x00) { 	// if inp is in '0' .. '9'
		inp -= 0x30;
		inp += 0x70;
	}
	send(inp);
}
void send(unsigned char inp) {
	SBUF = inp;
	while (TI == 0);
	TI = 0;
}
void send_ascii_word(unsigned char* inp) {
	int j, t;
	int length = strlen(inp);
	send_ascii(0x6D);		// due to stupidness of multisim
	send_ascii(0x6D);
	// send_ascii(0x6D);
	// send_ascii(0x6D);
	for (t = 0; t < 20; t++);
	for (j = 0; j < length; j++) {
		send_ascii(inp[j]);
		for (t = 0; t < 20; t++);
	}
}
