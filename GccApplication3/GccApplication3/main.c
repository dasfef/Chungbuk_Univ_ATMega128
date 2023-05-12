#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	DDRE = 0xff;
	
    while (1) 
    {
		for (unsigned char k=0; k<4; k++) {
			PORTB = 1<<k;
			_delay_ms(100);
		}
		
		for (unsigned char k=7; k>3; k--){
			PORTB = 1<<k;
			_delay_ms(100);
		}
		
		for (unsigned char k=0; k<4; k++) {
			PORTE = 1<<k;
			_delay_ms(100);
		}
    }
}

