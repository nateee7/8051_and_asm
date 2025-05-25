#include <8051.h>



// В <htc.h> всё то же самое

static volatile unsigned char	output		@ 0x80;
static volatile unsigned char	x_sc_p		@ 0x90;
static volatile unsigned char	x_sc_m		@ 0x91;
static volatile unsigned char	y_sc_p		@ 0x92;
static volatile unsigned char	y_sc_m		@ 0x93;
static volatile unsigned char	reset_inp	@ 0xB7;		// P37

// static volatile unsigned char	dispWR		@ 0xB0;		// 1->write
// static volatile unsigned char	dispRD		@ 0xB1;		// 1->write
// static volatile unsigned char	dispCD		@ 0xB2;		// 0->comm, 1->data
// static unsigned char			dispData	@ 0x90;

void init();
void draw();
void on_INT0();




int i;
int x_scale, y_scale;
int x_len; 
int x1, x2, x3, x4;
int y_len;
int y1, y2, y3;
int buf1, buf2;
int cnt1, cnt2;



// void dispComm(char c);
// void dispByte(char c);
// void dispDraw();

/* const char values[] = { 
		63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127
}; */
/* 
const char values2 = { 
		255, 253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 213, 211, 209, 207, 205, 203, 201, 199, 197, 195, 193, 191, 189, 187, 185, 183, 181, 179, 177, 175, 173, 171, 169, 167, 165, 163, 161, 159, 157, 155, 153, 151, 149, 147, 145, 143, 141, 139, 137, 135, 133, 131, 129, 127
}; */

interrupt void on_interr() {
	if (TCON_BITS.B1 == 0)	// при IE0=0, т.е. при спаде по ~INT0
		on_INT0();
		
	TCON_BITS.B1 = 1;
}

void main() {
						/*		practice #8
						/
						/ 		IgnatovichVO, INBs3301, #19
						/		
						/		Параметры по варианту в функции init()
						*/	
	init();
	
// DEBUG_start
			
			
	// dispComm(0b10010000);
	// dispComm(0x24);
	// dispComm(0xB0);
	// dispByte(0x27);	
			
			
	/* while (1) {
		P10 = 0;	
		for (i = 0; i < 317; i++)
			output = i;
		P10 = 0;	
	}	 */	

	
	TR0 = 1;		// включение Т/С1
	/* cnt1 = 0;
	while(1){
		for(i = 0; i < cnt1; i++)
			output = i;
		for(i = 0; i < 10; i++)
			output = 0;
	} */
	
	
	//while (1)  {
		// draw_point(i);
		draw();		// X = 50%, Y = 50%
	//}
					
// DEBUG_end
	
	
		
}

void init() {
	P0 = P1 = P2 = P3 =  0x00;
	output = 0x00;
	
	// Настройка Т/С1:
		TMOD = 0b00000001;
		// первый режим работы Т/С1, при котором
		// использоется 16-битовый Т/С без автоперезагрузки;
		// при переполнении TF0 = 1
	// Настройка системы прерываний:
		IE = 0;
		IE_BITS.B7 = 1;		// EA, 	включение системы прерываний
		IE_BITS.B0 = 1;		// EX0,	разрешение прерывания по входу ~INT0
		TCON_BITS.B0 = 1;	// IT0,	прерывание будет по спаду по входу ~INT0
		TCON_BITS.B1 = 1;	// IE0,	изначальное значение 1; при прерывании будет 0
		
}

void draw() {
	x_scale = 100;
	y_scale = 100;
	x_len = 255 * x_scale / 100; 
	x1 = x_len / 5;
	x2 = x_len * 2 / 5;
	x3 = x_len * 3 / 5;
	x4 = x_len * 4 / 5;
	y_len = 255 * y_scale / 100;
	y1 = y_len / 4;
	y2 = y_len / 2;
	y3 = y_len * 3 / 4;
	buf1, buf2;
	cnt1, cnt2;
	P2 = y_len;
	//int x_len = x_scale;
	//y_scale = y_scale * 255 / 100;		// 100% -> 255; 50% -> 127
	
	while (1) {
		buf1 = y1;
		buf2 = y_len;
		cnt1 = (y2 - y1) / x1;
		cnt2 = (y_len - y2) / x1;
		for (i = 0; i < x_len; i++) {
			if (i > x4)
				output = 0;
			else if (i > x3)
				output = y2;
			else if (i > x2)
				output = buf2;
			else if (i > x1)
				output = buf1;
			else
				output = 0;
			if (i == x1)
				buf1 = y1;
			if (i == x2)
				buf2 = y_len;
				
			buf1 += cnt1;
			buf2 -= cnt2;
		}
	}
}


void on_INT0() {
	// при нажатии любой из кнопок
	
	// debug start
	/* 
		if (P10 == 1)
			cnt1 += 5;
		else
			cnt1 -= 15;
	 */
	// debug end
	
	if (P10 == 1) {		// scale X inc
		x_scale += 10;	// +10%
		x_len = 255 * x_scale / 100; 
	}
	if (P11 == 1) {		// scale X dec
		x_scale -= 10;	// -10%
		x_len = 255 * x_scale / 100; 
	}
	if (P12 == 1) {		// scale Y inc
		y_scale += 10;	// +10%
		y_len = 255 * y_scale / 100; 
	}
	if (P13 == 1) {		// scale Y dec
		y_scale -= 10;	// -10%
		y_len = 255 * y_scale / 100; 
	}
	
	P2 = y_len;
	
	x1 = x_len / 5;
	x2 = x_len * 2 / 5;
	x3 = x_len * 3 / 5;
	x4 = x_len * 4 / 5; 
	y1 = y_len / 4;
	y2 = y_len / 2;
	y3 = y_len * 3 / 4;
	
	i = 0;
	
	
}
