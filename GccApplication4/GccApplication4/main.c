#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

void CPU_Setup() {
	DDRB = 0xff;
	DDRE = 0xff;
}

void RED_LED(char M) {
	if(M == 0){
		PORTB = 0x00;
		_delay_ms(100);
	} else {
		PORTB = 0xff;
		_delay_ms(100);
	}
}

void GRN_LED(char M) {
	if(M == 0){
		PORTE = 0x00;
		_delay_ms(100);
	} else{
		PORTE = 0xff;
		_delay_ms(100);
	}
}

int main(void)
{
	CPU_Setup();
	
    while (1) 
    {
		RED_LED(1);		RED_LED(0);
		RED_LED(1);		RED_LED(0);
		
		GRN_LED(1);		GRN_LED(0);
		GRN_LED(1);		GRN_LED(0);
    }
}

