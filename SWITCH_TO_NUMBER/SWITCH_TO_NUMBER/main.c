#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH1 PIND
#define SWITCH2 PINC
#define dTime 3

#include <util/delay.h>
#include <avr/io.h>

unsigned char FND[17]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77,
						0x7c, 0x58, 0x5e, 0x40, 0x49, 0x08};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char NewKey = 16;
unsigned char oldKey = 16;

void CPU_Setup(){
	DDRB=0xff;
	DDRE=0xff;
	DDRC=0x00;
	DDRD=0x00;
}

char SwitchIn(void) {
	char KeyNo;
	unsigned int KeyIn =(~SWITCH2<<8) | (~SWITCH1 & 0x00ff);
	switch ( KeyIn ) {
		case 0x0001: KeyNo =1; break;
		case 0x0002: KeyNo =2; break;
		case 0x0004: KeyNo =3; break;
		case 0x0008: KeyNo =10; break;
		case 0x0010: KeyNo =4; break;
		case 0x0020: KeyNo =5; break;
		case 0x0040: KeyNo =6; break;
		case 0x0080: KeyNo =11; break;
		case 0x0100: KeyNo =7; break;
		case 0x0200: KeyNo =8; break;
		case 0x0400: KeyNo =9; break;
		case 0x0800: KeyNo =12; break;
		case 0x1000: KeyNo =14; break;
		case 0x2000: KeyNo =0; break;
		case 0x4000: KeyNo =15; break;
		case 0x8000: KeyNo =13; break;
		default: KeyNo =16; break;
	}
	return KeyNo;
}

int main(void)
{
    CPU_Setup();
	
    while (1) 
    {
		NewKey=SwitchIn();
		if(NewKey != oldKey){
			oldKey=NewKey;
			if(NewKey != 16){
				for (unsigned char k=5; k>0; k--){
					NUM[k]=NUM[k-1];
				}
				NUM[0] = NewKey;
			}
		}
		for (unsigned char k=0; k<6; k++){
			FND_SEL = DGT[k];
			FND_DB = FND[NUM[k]];
			_delay_ms(dTime);
		}
    }
}

