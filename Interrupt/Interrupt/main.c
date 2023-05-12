#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH1 PIND
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char FND[17]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71, 0x00};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
long Count = 123456;

void Hex2Dec(unsigned long No);
void CPU_Setup(){
	DDRB = 0xff;
	DDRE = 0xff;
	DDRD = 0x00;
	
	EIMSK = 0x0f;
	EICRA = 0xaa;
	EICRB = 0x55;
	EIFR = 0x0f;
	sei();	
}

ISR(INT0_vect){
	Count += 10;
	if (Count > 999999) Count = 999999;
	Hex2Dec(Count);
}

ISR(INT1_vect){
	Count += 1;
	if (Count > 999999) Count = 999999;
	Hex2Dec(Count);
}

ISR(INT2_vect){
	Count -= 1;
	if(Count < 0) Count = 0;
	Hex2Dec(Count);
}

ISR(INT3_vect){
	Count -= 10;
	if(Count < 0) Count = 0;
	Hex2Dec(Count);
}

void Hex2Dec(unsigned long No) {
	long tmpNo = No;
	
	NUM[5] = tmpNo / 100000;
	tmpNo = tmpNo % 100000;
	NUM[4] = tmpNo / 10000;
	tmpNo = tmpNo % 10000;
	NUM[3] = tmpNo / 1000;
	tmpNo = tmpNo % 1000;
	NUM[2] = tmpNo / 100;
	tmpNo = tmpNo % 100;
	NUM[1] = tmpNo / 10;
	NUM[0] = tmpNo % 10;
}

void Display(){
	for (unsigned char k=0; k<6; k++){
		FND_SEL = DGT[k];
		FND_DB = FND[NUM[k]];
		_delay_ms(dTime);
	}
}

int main(void) {
	CPU_Setup();
	Hex2Dec(Count);
	
	while(1) {
		Display();
	}
}