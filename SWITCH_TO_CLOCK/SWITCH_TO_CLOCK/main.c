#define F_CPU 14745600UL
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH1 PIND
#define SWITCH2 PINC
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>

unsigned char FND[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
signed int A;
signed int B;
signed int C;
unsigned char newKey;
unsigned char oldKey;

void CPU_Setup( ) {
	DDRB=0xff;
	DDRE=0xff;
	DDRC=0x00;
	DDRD=0x00;
}

unsigned char KeyIn() {
	unsigned char Key = ~SWITCH1;
	for (int k = 0; k < 100; k++) {
		Key &= ~SWITCH1;
	}
	return Key;
}

void KeyProc() {
	unsigned char tKey = KeyIn();
	newKey = KeyIn();
	if(newKey != oldKey){
		switch (tKey) {
			case 0x01: if(++A > 23) A=0; break;
			case 0x02: if(++B > 59) B=0; break;
			case 0x04: if(++C > 59) C=0; break;
			
			case 0x10: if(--A < 0) A=0; break;
			case 0x20: if(--B < 0) B=0; break;
			case 0x40: if(--C < 0) C=0; break;
		}
		oldKey = newKey;
	}
	
}

void Hex2Dec() {
	unsigned int tmp = A;
	NUM[5] = tmp / 10;
	tmp = tmp % 10;
	NUM[4] = tmp % 10;
	
	tmp = B;
	NUM[3] = tmp / 10;
	tmp = tmp % 10;
	NUM[2] = tmp % 10;

	tmp = C;
	NUM[1] = tmp / 10;
	tmp = tmp % 10;
	NUM[0] = tmp % 10;
	
	
}

int main(void) {
	CPU_Setup();
	
	while(1) {
		for (unsigned char k = 0; k < 6; k++){
			FND_SEL = DGT[k];
			FND_DB = FND[NUM[k]];
			_delay_ms(dTime);
		}
		KeyProc();
		Hex2Dec();
	}
}