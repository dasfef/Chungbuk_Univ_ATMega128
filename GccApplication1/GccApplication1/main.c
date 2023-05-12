/*
 * GccApplication1.c
 *
 * Created: 2023-04-26 오후 5:07:30
 * Author : User
 */ 


#include <avr/io.h>
#define F_CPU 1474560 //가운데 위치 중요
#include <util/delay.h>


int main(void)
{
    DDRB=0xff;
	
    while (1) 
    {
		PORTB=0X66;
		_delay_ms(500);
		PORTB=0x99;
		_delay_ms(500);
    }
}

