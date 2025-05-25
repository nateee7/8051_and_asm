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
	unsigned char SetLeft;
	unsigned char SetRight;
	unsigned char MoveStartOf1;
	unsigned char MoveStartOf2;
	unsigned char MovePos1Of2;
	unsigned char MovePos3Of1;
	unsigned char Mode8bit;
} dispCommStruct;

int i;
dispCommStruct dispComm;

void dispInit		 ();						// initialization
void dispWriteRu	 (unsigned char inp);		// to write ru letter
void dispExecute	 (unsigned char command);	// to run certain command on display
void dispAnimate	 (unsigned char* inp, 
						const int space);		// for "running line" animation; line w\spaces&ru, length < 50
void dispSetPos (int pos);

void main(void) {
						/* readme:		
						/		practice #3
						/ 		IgnatovichVO, INBs3301, #19
						/
						/
						/		!!! �� ������� ������ ������ ������ !!!
						/
						/		�������:
						/			������� �����/����� �� 8�2 
						/			������� � ������ ������� ������ 
						/			����� ������� � ����� ������ ������,
						/			����������� ������ �� ������ ������
						/		��������� �����:
						/			�������:
						/				Base Character Set = 1
						/				Character Subset = 30;	// ��� �������
						/			
						*/	
	dispInit();		
	
	// dispAnimate ("abcdefghijklmnopqrstuvwxyz", 5);
	// dispAnimate ("!@#$%^&*\(\)\'\"", 5);
	// dispAnimate ("�����Ũ���������������������������", 5);
	dispAnimate ("��������� �����", 5);
	
	while(1);
}

void dispInit() {
	// �������:
		dispComm.Clear = 		0x01;		// �������
		dispComm.MoveStart = 	0x02;		// � ������
		dispComm.Off = 			0x08;		// ���������� �������
		dispComm.On = 			0x0E;		// ��������� �������
		dispComm.SetLeft = 		0x04;		// ������� ����������� �����
		dispComm.SetRight = 	0x06;		// ������� ����������� ������
		dispComm.MoveStartOf1 = 0x80;		// � ������ ������ ������
		dispComm.MoveStartOf2 = 0xC0;		// � ������ ������ ������
		dispComm.MovePos1Of2 = 	0xC1;		// � 1 ������� ������ ������
		dispComm.MovePos3Of1 = 	0x83;		// � 3 ������� ������ ������
		dispComm.Mode8bit = 	0x38;		// ����� 8-bit ����������, 2 ������
	// ��������� �������:
		dispRW = 0;
		dispRS = 1;
		dispE = 1;
		dispExecute (dispComm.Clear);
}
void dispExecute (unsigned char command) {
	dispRS = 0;
	dispRW = 0;
	dispData = command;
	dispE = 1;
	dispE = 0;
}
void dispWriteRu	(unsigned char inp) {
	int j = inp;
	dispRW = 0;
	dispRS = 1;	// 1 - data, 0 - instruction
	if (inp >= 0xC0 && inp <= 0xF1) { // if it's russian letter
		j = inp - 0x20;		// for '�' .. '�'
		if (inp > 0xC5)		// for '�' .. '�'
			j = inp - 0x1F;
	}
	if (inp == 0xA8)		// for '�'
		j = 0xA6;
	dispData = j;
	dispE = 1;	
	dispE = 0;	
}
void dispAnimate	(unsigned char* inp, const int space) {
	int length = strlen(inp);
	int curr = 1;
	int buf = 0;
	unsigned char j;
	unsigned char buf2;
	unsigned char in[55];
	strcpy (in, inp);
	dispExecute (dispComm.Clear);
	space = length + dispLength;
	while (1) {
		buf = curr - length /* - 1 */;
		if (buf >= 0) {
			if (buf > 0) {
				dispSetPos(buf - 1);
				dispWriteRu(' ');
			}
			else
				dispSetPos(buf);
			for (i = 0; i < length; i++)
				if (buf + i < dispLength)
					dispWriteRu(in[i]);
		}
		else {
			dispSetPos(0);
			if (dispLength - curr >= 0)
				for (i = 0; i < curr; i++)
					dispWriteRu(in[-buf + i]);
			else
				for (i = 0; i < dispLength; i++)
					dispWriteRu(in[-buf + i]);
		}
		
		for (i = 0; i < 300; i++);
		if (curr >= dispLength + length)
			curr = 1;
		else
			curr++;
	}
}

void dispSetPos (int pos) {
	dispExecute(0x80 + pos);
}
