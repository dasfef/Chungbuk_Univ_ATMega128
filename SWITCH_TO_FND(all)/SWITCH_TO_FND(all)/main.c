#define F_CPU 14745600UL
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH1 PIND
#define SWITCH2 PINC
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>

unsigned char FND[11]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x40};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
signed int A;
signed int B;	
/*unsigned char Keypad;*/

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
	switch (tKey) {
		case 0x01: if(++A > 999) A=999; break;
		case 0x08: if(++B > 999) B=999; break;
		case 0x10: if(--A < 0) A=0; break;
		case 0x01: if(--B < 0) B=0; break;
	}
}

void Hex2Dec() {
	unsigned int tmp = A;
	NUM[5] = tmp / 100;
	tmp = tmp % 100;
	NUM[4] = tmp / 10;
	NUM[3] = tmp % 10;
	
	tmp = B;
	NUM[2] = tmp / 100;
	tmp = tmp % 100;
	NUM[1] = tmp / 10;
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

/*
char SwitchIn(void) {
	char KeyNo;
	unsigned int KeyIn =(~SWITCH2<<8) | (~SWITCH1 & 0x00ff);
	switch ( KeyIn ) {
		case 0x0001: KeyNo =0; break;
		case 0x0002: KeyNo =1; break;
		case 0x0004: KeyNo =2; break;
		case 0x0008: KeyNo =3; break;
		case 0x0010: KeyNo =4; break;
		case 0x0020: KeyNo =5; break;
		case 0x0040: KeyNo =6; break;
		case 0x0080: KeyNo =7; break;
		case 0x0100: KeyNo =8; break;
		case 0x0200: KeyNo =9; break;
		case 0x0400: KeyNo =10; break;
		case 0x0800: KeyNo =11; break;
		case 0x1000: KeyNo =12; break;
		case 0x2000: KeyNo =13; break;
		case 0x4000: KeyNo =14; break;
		case 0x8000: KeyNo =15; break;
		default: KeyNo =16; break;
	}
	return KeyNo;
}

void Hex2Dec(unsigned char No) {
	NUM[1]=No / 10;
	NUM[0]=No % 10;
}
int main(void) {
	CPU_Setup( );
	while (1) {
		Keypad=SwitchIn( );
		if (Keypad>15){
			NUM[1]=10; NUM[0]=10;
			}else{
			Hex2Dec(Keypad);
		}
		for (unsigned char k=0;k<2;k++){
			FND_SEL=DGT[k];
			FND_DB=FND[ NUM[k] ];
			_delay_ms(dTime);
		}
	}
}
*/