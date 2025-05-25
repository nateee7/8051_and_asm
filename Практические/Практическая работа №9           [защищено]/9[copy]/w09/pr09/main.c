#include <8051.h>


static volatile unsigned char	VADC_out	@ 0x90;		// P1
static volatile bit				VADC_EOC	@ 0xB0;		// P30
static volatile bit				VADC_SOC	@ 0xB1;		// P31
static volatile unsigned char	VDAC_inp	@ 0xA0;		// P2
static volatile bit				shift_out	@ 0x87;		// P07
//static volatile unsigned char	P0	@ 0x80;


void init();
void on_INT0();

int shift_flag;




interrupt void on_interr() {
	if (TCON_BITS.B1 == 0)	// при IE0=0, т.е. при спаде по ~INT0
		on_INT0();
		
	TCON_BITS.B1 = 1;
}

void main() {
						/*		practice #9
						/
						/ 		IgnatovichVO, INBs3301, #19
						/
						*/	
	init();
	
// DEBUG_start
			
	while(1) {
		VADC_SOC = 1;
		VADC_SOC = 0;
		while(VADC_EOC == 1);
		VDAC_inp = VADC_out;
		shift_out = shift_flag;
	}
	
// DEBUG_end
	
	
		
}

void init() {
	P0 = P1 = P2 = P3 =  0x00;
	shift_flag = 0;
	// Настройка системы прерываний:
		IE = 0;
		IE_BITS.B7 = 1;		// EA, 	включение системы прерываний
		IE_BITS.B0 = 1;		// EX0,	разрешение прерывания по входу ~INT0
		TCON_BITS.B0 = 1;	// IT0,	прерывание будет по спаду по входу ~INT0
		TCON_BITS.B1 = 1;	// IE0,	изначальное значение 1; при прерывании будет 0
		
}

void on_INT0() {
	shift_flag = !shift_flag;
}




