#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE
#define dTime 3
#define tConst 144		// ((1/14745600) * 1024) * 144 = 0.01sec
#define SWITCH PINA

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char FND[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49, 0x40};
unsigned char DGT[6] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char Keypad;
	
unsigned char Min = 0;
unsigned char Sec = 0;
unsigned char mSec = 0;
unsigned char flag = 0;

ISR(TIMER0_OVF_vect){
	if(++mSec>99) {
		mSec=0;
		if(++Sec>59){
			Sec=0;
			if(++Min>59) Min=0;
		}
	}
	TCNT0 = 0xff-tConst;
}

void Timer0_Init(){
	TCCR0 = 0x07;			// Clk / 1024
	TIMSK = 1 << TOIE0;		// Overflow Interrupt Enable
	TIFR = 1 << TOV0;		// Set Overflow Interrupt Flag
	TCNT0 = 0xff - tConst;
}


void Hex2Dec() {
	unsigned char tmp=Min;
	NUM[5]=tmp/10;
	NUM[4]=tmp%10;
	
	tmp=Sec;
	NUM[3]=tmp/10;
	NUM[2]=tmp%10;
	
	tmp=mSec;
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
	DDRA=0x00;
}

int main(void) {
	CPU_Setup();
	Timer0_Init();
	//sei();
	while (1) {
		Keypad = ~SWITCH;
		switch(Keypad){
			case 0x01:
				if(flag==0) {
					sei(); flag=1;}
					
				else if(flag==1) {
					cli(); flag=0;}
					break;
			case 0x10: Min=0; Sec=0; mSec=0; break;
		}
		Hex2Dec();
		FND_Display();
	}
}