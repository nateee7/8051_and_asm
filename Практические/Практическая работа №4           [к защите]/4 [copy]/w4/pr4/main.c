#include <8051.h>

//int T1, T2, T3, T4, T5, T6;

const int dur1 = 2;
const int dur2 = 5;
const int dur3 = 2;
const int dur4 = 5;
const int dur5 = 1;
const int dur6 = 1;

void delayms(const int duration);
void init();

void main(void) {
						/* readme:		
						/		practice #4
						/ 		IgnatovichVO, INBs3301, #19
						/
						/		Задание:
						/			Зажигать 8 цветных светодиодов с интервалами:
						/				T1  T2  T3  T4  T5  T6
						/				2c  5c  2c  5c  1c  1c  
						/			
						*/
	
	init();
	while (1) {
		P00 = 1;
		delayms(dur3);
		P00 = 0;
		
		P01 = 1;
		delayms(dur4);
		P01 = 0;
		
		P02 = 1;
		delayms(dur3);
		P02 = 0;
		
		P03 = 1;
		delayms(dur1);
		P03 = 0;
		
		P04 = 1;
		delayms(dur2);
		P04 = 0;
		
		P05 = 1;
		delayms(dur1);
		P05 = 0;
		
		P06 = 1;
		delayms(dur6);
		P06 = 0;
		
		P07 = 1;
		delayms(dur5);
		P07 = 0;
		
	}
//						TMOD 	(T1/T0):
//								[7/3]	gate	блокировка:
//									gate=1: работа разрешена до тех пор, пока: INTx=1, TRx=1
//									gate=0: работа заблокирована до момента: TRx=1
//								[6/2]	C/T		выбор режима:
//									C/T=1: режим счётчика по входу Tx
//									C/T=0: режим таймера
//								[5/1]	M1		старший бит управления
//								[4/0]	M0		младший бит управления
//						
//						режимы работы (M1,M0):	// ТС - таймеросчётчик
//									   0  0		таймер BE48, TLx - 5-bit предделитель
//									   0  1		16-bit ТС; THx, TLx включены последовательно
//									   1  0		8-bit ТС; автоперезагрзка (THx -> TLx при переполнении)
//									   1  1		только T0; TL0 - 8-bit ТС, TH0 - 8-bit таймер
//									   
//						TCON:
//							[7]		TF1		флаг переполнения T0
//							[6]		TR1		управление T1
//							[5]		TF0		флаг переполнения T0
//							[4]		TR0		управление T0
//							[3]		IE1		фронт прерывания 1
//							[2]		IT1		тип прерывания 1
//							[1]		IE0		фронт прерывания 0
//							[0]		IT0		тип прерывания 0
	
					// vars:					
					// TMOD, TCON
					// TL0, TL1, TH0, TH1
					// IT0, IE0, IT1, IE1, TR0, TF0, TR1, TF1
	
}
void init() {
	P0 = 0x00;
	P1 = 0x00;
	P2 = 0x00;
	P3 = 0x00;
		
	TMOD = 0x01;
}
void delayms(const int duration) {
	duration *= 52;						// scale for multisim
	for (; duration >=0; duration--) {
		TH0 = 0x00;
		TL0 = 0x00;
		TR0 = 1;
		while (TF0 != 0);
		TR0 = 0;
		TF0 = 0;
	}
}
