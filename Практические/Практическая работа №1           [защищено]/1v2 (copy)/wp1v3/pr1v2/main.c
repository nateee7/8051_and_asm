#include <8051.h>	

#define 	start 	0x0AA
#define 	end 	0x800


int i;
char xdata *ptr;
char buf, value;

// 0=success, 1=fail, 2=waiting
void showStatus(int status) { P1 = 0x01 * (status == 0) + 0x02 * (status == 1) + 0x04 * (status == 2); }
void main(void) {
						/*		
						/		practice #1v2
						/ 		IgnatovichVO, INBs3301, #19
						/		to set start, end: 
						/		change values in the end of strings 3, 4	
						*/		
	value = 0xAA;										// at 21 in IRAM
	buf = 0x01;											// at 20 in IRAM
	showStatus(2);
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
	showStatus(2);
	for (;;);
}