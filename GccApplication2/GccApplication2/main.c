#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	
    while (1) 
    {
		PORTB = 0x66;
		_delay_ms(500);
		
		PORTB = 0x99;
		_delay_ms(500);
    }
}

