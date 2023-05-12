#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH PINA

#include <avr/io.h>

unsigned char FND[11] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x40};
unsigned char DGT[6] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char Keypad;

unsigned long Count = 0;

void CPU_Setup(){
	DDRB =0xff;
	DDRE = 0xff;
	DDRA = 0x00;
}

int main(void)
{
    CPU_Setup();
	
    while (1) 
    {
		Keypad = ~SWITCH;
		FND_SEL = DGT[5];
		switch (Keypad) {
			case 0x01: FND_DB = FND[0]; break;
			case 0x02: FND_DB = FND[1]; break;
			case 0x04: FND_DB = FND[2]; break;
			case 0x08: FND_DB = FND[3]; break;
			case 0x10: FND_DB = FND[4]; break;
			case 0x20: FND_DB = FND[5]; break;
			case 0x40: FND_DB = FND[6]; break;
			case 0x80: FND_DB = FND[7]; break;
			default: FND_DB = FND[10]; break;
		}
    }
}

