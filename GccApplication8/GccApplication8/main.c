#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>


int main(void){
	LCD_Init();
	while (1) {
		write_Command(0x01); /* Clear Display */
		_delay_ms(9);
		write_Command(0x80); /* 1 Line Address */
		_delay_us(220);
		printString ( " IoT Smart SW " );
		write_Command(0xC0); /* 2 line Address */
		_delay_us(220);
		printString ( " Jong,Yi - YOON " );
		_delay_ms(500);
	}
}