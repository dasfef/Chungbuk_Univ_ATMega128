#define F_CPU 14745600
#define FND_SEL PORTB
#define FND_DB PORTE

#include <avr/io.h>
#include <util/delay.h>

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
		FND_DB = 0x5b;
		
    }
}

