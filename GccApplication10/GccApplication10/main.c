#define F_CPU 14745600
#define LED_RED PORTB
#define SWITCH PINA

#include <avr/io.h>
#include <util/delay.h>

unsigned char Keypad;

void CPU_Setup()
{
	DDRB = 0xff;
	DDRA = 0x00;
}

int main(void) 
{
	CPU_Setup();
	
	while(1) {
		Keypad = ~SWITCH;
		/*if (Keypad==0x01){ LED_RED=0b00000001; }
		else if (Keypad==0x02){ LED_RED=0b00000011; }
		else if (Keypad==0x04){ LED_RED=0x07; }
		else if (Keypad==0x08){ LED_RED=0x0f; }
		else if (Keypad==0x10){ LED_RED=0x1f; }
		else if (Keypad==0x20){ LED_RED=0x3f; }
		else if (Keypad==0x40){ LED_RED=0x7f; }
		else if (Keypad==0x80){ LED_RED=0xff; }
		else { LED_RED=0x00; }*/
			
		switch(Keypad){
			case 0x01: LED_RED=0x01; break;
			case 0x02: LED_RED=0x03; break;
			case 0x04: LED_RED=0x07; break;
			case 0x08: LED_RED=0x0f; break;
			case 0x10: LED_RED=0x1f; break;
			case 0x20: LED_RED=0x3f; break;
			case 0x40: LED_RED=0x7f; break;
			case 0x80: LED_RED=0xff; break;
			default: LED_RED=0x00; break;
		}
	}
}