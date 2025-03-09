#include <8051.h>
#include <string.h>

#define dispLength 8

static volatile unsigned char	dispData	@ 0xA0;	// for port P2
static volatile bit				dispE		@ 0x85;	// for P05
static volatile bit				dispRS		@ 0x86;	// for P06
static volatile bit				dispRW		@ 0x87;	// for P07
static volatile bit				interr		@ 0x80;	// for P00

typedef struct {
	unsigned char Clear;
	unsigned char Off;
	unsigned char On;
	unsigned char MoveStart;
	unsigned char MoveLeft;
	unsigned char MoveRight;
	unsigned char MoveStartOf1;
	unsigned char MoveStartOf2;
	unsigned char MovePos1Of2;
	unsigned char MovePos3Of1;
	unsigned char Mode8bit;
} dispCommStruct;

int i;
dispCommStruct dispComm;

void dispInit		();							// initialization
void dispWrite		(unsigned char inp);		// to write 1-byte letter
void dispWriteLine	(unsigned char* inp);		// line w\spaces, length < 80
void dispExecute	(unsigned char command);	// to run certain command on display
void dispAnimate	(unsigned char* inp);		// for "running line" animation; line w\spaces, length < 50
 
void main(void) {
						/* readme:		
						/		practice #3
						/ 		IgnatovichVO, INBs3301, #19
						/
						/		переменные дисплея объявлены на строках 3..6
						/		Задание:
						/			Вывести слово/фразу на 8х2 
						/			дисплей в режиме бегущей строки 
						/			слева направо с конца второй строки,
						/			отображение только на первой строке
						/		Параметры схемы:
						/			Дисплей:
						/				Base Character Set = 1
						/				Character Subset = 30;	// для русских
						/			
						*/	
	dispInit();		
	dispAnimate ("your mother on sale");
	while(1);
}

void dispInit() {
	// Команды:
	dispComm.Clear = 		0x01;		// Очистка
	dispComm.MoveStart = 	0x02;		// В начало
	dispComm.Off = 			0x08;		// Выключение дисплея
	dispComm.On = 			0x0E;		// Включение дисплея
	dispComm.MoveLeft = 	0x04;		// Влево
	dispComm.MoveRight = 	0x06;		// Вправо
	dispComm.MoveStartOf1 = 0x80;		// В начало первой строки
	dispComm.MoveStartOf2 = 0xC0;		// В начало второй строки
	dispComm.MovePos1Of2 = 	0xC1;		// В 1 позицию второй строки
	dispComm.MovePos3Of1 = 	0x83;		// В 3 позицию первой строки
	dispComm.Mode8bit = 	0x38;		// Режим 8-bit интерфейса, 2 строки
	// Настройка дисплея:
	dispRW = 0;
	dispRS = 1;
	dispE = 1;
	dispExecute (dispComm.Clear);
	// stopAnimation = 0;
}
void dispWrite (unsigned char inp) {
	dispRS = 1;	// 1 - data, 0 - instructions
	dispRW = 0;
	dispData = inp;
	dispE = 1;
	dispE = 0;
}
void dispWriteLine (unsigned char* inp) {
	int length = strlen(inp);
	unsigned char in[79];
	strcpy (in, inp);
}
void dispExecute (unsigned char command) {
	dispRS = 0;
	dispRW = 0;
	dispData = command;
	dispE = 1;
	dispE = 0;
}
void dispAnimate	(unsigned char* inp) {
	int length = strlen(inp);
	int curr = 0;
	unsigned char in[30];
	strcpy (in, inp);
	dispExecute (dispComm.Clear);
	dispExecute (dispComm.MoveStartOf2);
	dispExecute (dispComm.MoveStartOf1);
	dispRS = 1;		// 1 - data, 0 - instructions
	dispRW = 0;	
	while (1) {					// animation from left to right on first row
		dispExecute (dispComm.Clear);
		for (i = 0; i < dispLength; i++) {
			if (curr % (dispLength + 2) >= dispLength || i <= curr) {
				if (i > length)
					dispWrite(' ');
				else
					dispWrite(in[length - curr % (dispLength + 2) - 1 + i]);
			}
			else
				dispWrite(' ');
		}
		curr++;
		// if (curr >= length + dispLength) {
			// dispExecute (dispComm.MoveStartOf1);
			// curr = 0;
		// }
			
	}
	
}
