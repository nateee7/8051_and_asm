#include <8051.h>

void init();							// initializing
char read();							// returns char of letter on keyboard
void disp_write(unsigned char symb);	// writes symbol to LCD
void disp_execute(char comm);			// executes command on LCD
void disp_clear();						// clears LCD
// vars:
	int i;
	int disp_length, disp_cnt;
	char last_symb;
void main() {
						/* readme:		
						/		practice #5
						/ 		IgnatovichVO, INBs3301, #19
						/		принцип клавиатуры:
						/			в строки подаётся 0, в столбцы 1
						/			при нажатии на клавишу:
						/			столбец = 0, чтобы найти строку:
						/			столбцы = 0, строки = 1, тогда
						/			строка будет равна 0
						*/	

// code:					
	init();
	while (1) {
		// for (i = 0; i < 50; i++);
		// P2 = read();
		// for (i = 0; i < 20; i++);
		// disp_write(P2);
		for (i = 0; i < 1; i++);
		P2 = read();
		if (P2 != last_symb && P2 != ' ') {
			last_symb = P2;
			disp_write(last_symb);
		}
		
	}		
}

void init() {
	P0 = 0x00;
	P1 = 0x00;
	P2 = 0x00;
	P3 = 0x00;
	
	last_symb = ' ';
	
	disp_length = 8;
	disp_cnt = 0;
	disp_execute(0x02);	// to the start
	disp_write('s');
	disp_write('t');
	disp_write('a');
	disp_write('r');
	disp_write('t');
	for (i = 0; i < 50; i++);
	disp_clear();
	disp_cnt = 0;
	
}

char read() {	
	int col, row;
	char res = ' ';
	
	P00 = P01 = P02 = 0;				// rows
	P20 = P21 = P22 = P23 = P24 = 1;	// columns
	
	if (P20 == 0)
		col = 4;
	if (P21 == 0)
		col = 3;
	if (P22 == 0)
		col = 2;
	if (P23 == 0)
		col = 1;
	if (P24 == 0)
		col = 0;
	
	P00 = P01 = P02 = 1;				// rows
	P20 = P21 = P22 = P23 = P24 = 0;	// columns
	
	if (P00 == 0)
		row = 0;
	if (P01 == 0)
		row = 1;
	if (P02 == 0)
		row = 2;
	
	if (col == 0 && row == 0) res = '7';
	if (col == 1 && row == 0) res = '8';
	if (col == 2 && row == 0) res = '9';
	if (col == 3 && row == 0) res = '+';
	if (col == 4 && row == 0) res = '-';
	
	if (col == 0 && row == 1) res = '4';
	if (col == 1 && row == 1) res = '5';
	if (col == 2 && row == 1) res = '6';
	if (col == 3 && row == 1) res = '*';
	if (col == 4 && row == 1) res = '/';
	
	if (col == 0 && row == 2) res = '1';
	if (col == 1 && row == 2) res = '2';
	if (col == 2 && row == 2) res = '3';
	if (col == 3 && row == 2) res = '0';
	if (col == 4 && row == 2) res = '.';
	
	
	return res;
}

void disp_write(unsigned char symb) {
	P31 = 1;	// RS: 1 - data, 0 - instructions
	P30 = 0;	// RW
	P1 = symb;	// Data
	if (disp_cnt >= disp_length - 1) {
		disp_cnt = 0;
		disp_clear();
		disp_execute(0x02);	// to the start
		
	}
	else
		disp_cnt++;
	P32 = 1;	// E
	P32 = 0;
}
void disp_clear() {
	P31 = 0;
	P30 = 0;
	P1 = 0x01;
	P32 = 1;
	P32 = 0;
}
void disp_execute(char comm) {
	P31 = 0;
	P30 = 0;
	P1 = comm;
	P32 = 1;
	P32 = 0;
}
