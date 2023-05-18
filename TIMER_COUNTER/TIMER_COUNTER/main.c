#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_RED PORTB
unsigned char LED[8] = {0x08, 0x04, 0x02, 0x01, 0x10, 0x20, 0x40, 0x80};
unsigned char Count = 0;
unsigned char mSec = 0;

ISR(TIMER0_OVF_vect){
	if (++mSec >= 100) {
		mSec = 0;
		LED_RED = LED[Count];
		if(++Count > 7) Count = 0;
	}
	TCNT0 = 0xff - 144;
	// 10ms 단위
	/*
	LED_RED = LED[Count];
	if(++Count > 7) Count = 0;
	TCNT0 = 0xff - 144;		
	*/
}

void Timer0_Init() {
	TCCR0 = 0x07;
	TIMSK = 1<<TOIE0;
	TIFR = 1<<TOV0;
	TCNT0 = 0xff - 144;
}

void CPU_Setup() {
	DDRB = 0xff;
}

int main(void) {
	CPU_Setup();
	Timer0_Init();
	sei();
	
	while(1){
		
	}
}