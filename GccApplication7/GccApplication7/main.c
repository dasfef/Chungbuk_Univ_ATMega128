#define F_CPU 14745600UL
#define FND_SEL PORTB
#define FND_DB PORTE
#define dTime 10
#include <avr/io.h>
#include <util/delay.h>
unsigned char FND[4][2]={ {0x63, 0x00}, {0x00, 0x63}, {0x00, 0x5c}, {0x5c, 0x00}};
unsigned char DGT[2] = {0xfb, 0xf7};

void CPU_Setup( )
{
DDRB=0xff;
DDRE=0xff;
}

int main(void)
{
CPU_Setup( );
while (1) 
{
	for(char k = 0; k < 4; k++){
		for(char h = 0; h < 10; h++){
			for(char m = 0; m < 2; m++){
				FND_SEL = DGT[m];
				FND_DB = FND[k][m];
				_delay_ms(dTime);
			}
		}
	}
}
}