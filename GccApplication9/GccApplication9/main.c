#define F_CPU 14745600
#include <util/delay.h>
#include <avr/io.h>

long Count = 120000;

unsigned char ASCII[17] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x20};
unsigned char DISP[7];

void Hex2ASC(long NO) {
	long tmpNO = NO;
	DISP[0] = ASCII[tmpNO / 100000];
	tmpNO %= 100000;
	DISP[1] = ASCII[tmpNO / 10000];
	tmpNO %= 10000;
	DISP[2] = ASCII[tmpNO / 1000];
	tmpNO %= 1000;
	DISP[3] = ASCII[tmpNO / 100];
	tmpNO %= 100;
	DISP[4] = ASCII[tmpNO / 10];
	DISP[5] = ASCII[tmpNO % 10];
}

int main(void)
{
    LCD_Init();
    write_Command(0x01); _delay_ms(9); /* Clear Display */
    write_Command(0x80); _delay_us(220); /* 1 Line Address */
    printString ( " IoT SMART SW " );
    write_Command(0xC0); _delay_us(220); /* 2 line Address */
    _delay_ms(500);
    while (1) {
	    Hex2ASC(Count);
		write_Command(0xc4);
		printString(DISP);	_delay_ms(1000);
		
	    if (++Count>130000) Count=0;
    }
}

