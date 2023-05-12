#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE

#include <avr/io.h>
#include <util/delay.h>

unsigned char FND[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};

void CPU_Setup(){
	DDRB = 0xff;
	DDRE = 0xff;
}

int main(void)
{
	CPU_Setup();
    while (1) 
    {
		FND_SEL = ~0x01;
		
		for(char k = 0; k < 10; k++){
			FND_DB = FND[k];
			_delay_ms(300);
			
		}
    }
}

