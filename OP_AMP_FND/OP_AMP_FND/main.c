#define F_CPU 14745600UL
#define FND_SEL PORTB
#define FND_DB PORTE
#define SWITCH1 PIND
#define SWITCH2 PINC
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>

unsigned char FND[17]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49,0x40};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
unsigned int Sound=0;

unsigned int ADConv( unsigned char Channel ) {
	ADMUX = (Channel & 0x03);
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS1) | (1<<ADPS0);
	_delay_us(100);
	while( ~ADCSRA & 0x10 );
	return ADC;
}

void Hex2Dec(unsigned int No){
	unsigned int tmp=No;
	NUM[5]=8; 
	NUM[4]=16;
	NUM[3]=tmp/1000;
	tmp=tmp%1000;
	NUM[2]=tmp/100;
	tmp=tmp%100;
	NUM[1]=tmp/10;
	NUM[0]=tmp%10;
}
void FND_Display(){
	for (unsigned char k=0; k<6; k++) {
		FND_SEL=DGT[k];
		FND_DB=FND[ NUM[k] ];
		_delay_ms(dTime );
	}
}

void CPU_Setup( ) {
	DDRB=0xff;
	DDRE=0xff;
	DDRF=0xF0;
}

int main(void) {
	CPU_Setup();
	while (1) {
		Sound=ADConv(0);
		Hex2Dec(Sound);
	FND_Display(); }
}