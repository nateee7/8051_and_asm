#include <8051.h>	

int i;
int curr;
const unsigned char arr[] = {		// 3, 4, 5, 6, 7, 8, 9, A, B, C, d, E, F
	0x79,			// 3 = 1111001
	0x33,			// 4 = 0110011
	0x5B,			// 5 = 1011011
	0x5F,			// 6 = 1011111
	0x70,			// 7 = 1110000
	0x7F,			// 8 = 1111111
	0x7B,			// 9 = 1111011
	0x77,			// A = 1110111
	0x1F,			// B = 0011111
	0x4E,			// C = 1001110
	0x3D,			// d = 0111101
	0x4F,			// E = 1001111
	0x47			// F = 1000111
};

void changeValue(){
	if (curr > 12)
		curr = 0;
	P2 = arr[curr];
	P07 = 1;
	P07 = 0;
	curr++;
}
						/*		practice #2
						/ 		IgnatovichVO, INBs3301, #19
						/		values are in strings: 	3..5
						*/	
void main() {
	P1 = 0x00;
	P2 = 0x00;
	curr = 0x00;
	i = 0;
	for (;;) {
		if (P10 == 1) {
			changeValue();
			for(i = 0; i < 1; i++);
		}
	}
}