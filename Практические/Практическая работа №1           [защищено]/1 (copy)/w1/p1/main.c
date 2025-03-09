#include <8051.h>

#define 	start 	0x0AA
#define 	end 	0x800

int i;
char xdata *ptr;
char buf, value;

// 0=success, 1=fail, 2=waiting, 3=start
void showStatus(int status) { P1 = 0x01 * (status == 0) + 0x04 * (status == 1) + 0x02 * (status == 2) + 0x80 * (status == 3); }
// for checking
void check() {
	buf = 0x13;											// at 20 in IRAM	
	ptr = (char xdata *) 0x123;
	*ptr = 0xAA;
	//(unsigned char *) 0x124 = 0xA1;
	buf = *ptr;
	for (i = 0; i < 5; i++) {
		buf = *ptr;
		ptr++;
	}
	for(;;);
}
// 11101010 (EA) but instead of  
// 01111111
		
void main(void) {
						/*		practice #1
						/ 		IgnatovichVO, INBs3301, #19
						/		to set start, end: 
						/		change values in the end of strings 3, 4	
						*/		
	value = 0xAA;										// at 21 in IRAM
	buf = 0x01;											// at 20 in IRAM
	showStatus(3);
 //	check();											// comment this!
	ptr = (char xdata*)start;							// at 24-25 in IRAM
	for (i = 0; i < end - start + 1; i++) {
		showStatus(2);
		*ptr = value;
		buf = *ptr;
		if (buf != value)
			showStatus(1);
		else
			showStatus(0);
		ptr++;
	}	
	showStatus(3);
	for (;;);
}
