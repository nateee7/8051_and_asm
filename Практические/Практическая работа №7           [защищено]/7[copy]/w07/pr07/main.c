#include <8051.h>
	
// В <htc.h> всё то же самое


const int T;
	  int Q;
/* const */ int F;
/* const */ int Qmin;
/* const */ int Qmax;
	  int flag;

void init();
void write(char inp);
void write_Q();
void pulse(int Qinp);
void inc ();
void dec ();
void set_50 ();
void set_default ();

void main() {
						/*		practice #7
						/
						/ 		IgnatovichVO, INBs3301, #19
						/		
						/		Параметры по варианту в функции init()
						*/	
						
	init();
	
	
	
// DEBUG_start
					// мои расчёты:
					// Fосц = 11.059 МГц
					// v = 921583.33 Гц
					// T = 7 * 10^-2 с
					// R ~= 1025.17 		=>	R = 0x0401
// DEBUG_end
	
	
	
	T2CON = 0b00000100;	// start T/C2
	while (1) {
		if (P30 == 1) {
			if (!flag) {
				inc();
				flag = 1;
			}
		}
		if (P31 == 1) {
			if (!flag) {
				dec();
				flag = 1;
			}
		}
		if (P32 == 1) {
			if (!flag) {
				set_default();
				flag = 1;
			}
		}
		if (P33 == 1) {
			if (!flag) {
				set_50();
				flag = 1;
			}
		}
		if (P30 == 0 && P31 == 0 && P32 == 0 && P33 == 0)
			flag = 0;
		pulse (Q);
		
	}
						
}

void init() {
	P0 = P1 = P2 = P3 =  0x00;
	flag = 0;
	
	T = 60;		// 60 мс
	Q = 30;		// 30%
	F = 12;		// 12 МГц
	Qmin = 30;	// 30%
	Qmax = 60;	// 60%
	
	RCAP2H = 0x04;
	RCAP2L = 0x01;
	T2CON = 0b00000000;
	TH2 = 0xFF;
	TL2 = 0xFF;
	
	ET2 = 1;
	EA = 1;
	
	P21 = 0;	// RS (1 = data)
	P22 = 0;	// RW
	P20 = 1;	// E
	P20 = 0;
	write (' ');
	write ('Q');
	write ('=');
	write ('3');
	write ('0');
}

// Qinp means % of T
void pulse(int Qinp) {
							// t = 82 	-> 1 мс
							// t = 5740 -> 70 мс
	int t = 57 * Qinp;		// at 2C .. 2D		// 45 ms on 0x0F00
	//int t = 574 * Qinp / 10;		// at 2C .. 2D		// 45 ms on 0x0F00
	P27 = 1;
	while (t-- != 0);		// 1 on pulse
	P27 = 0;
	while(TF2 == 0);		// 0 after pulse
	TF2 = 0;
}
void set_default () {
	Q = 30;
	write_Q();
}
void set_50 () {
	Q = 50;
	write_Q();
}
void inc () {
	if (Q <= Qmax - 10)
		Q += 10;
	write_Q();
}
void dec () {
	if (Q >= Qmin + 10)
		Q -= 10;
	write_Q();
}
void write(char inp) {
	P1 = inp;
	P21 = 1;	// RS (1 = data)
	P22 = 0;	// RW
	P20 = 1;	// E
	P20 = 0;
}
void write_Q() {
	P1 = 0x82;
	P21 = 0;	// RS (1 = data)
	P22 = 0;	// RW
	P20 = 1;	// E
	P20 = 0;
	write ((char)(Q / 10) + 48);
	//write ((char)(Q % 10) + 48);
}
