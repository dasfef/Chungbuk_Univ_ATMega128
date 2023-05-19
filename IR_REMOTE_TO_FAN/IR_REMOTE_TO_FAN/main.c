#include "IR_Remote.c"

//#define F_CPU 14745600
#define FND_SEL PORTF
#define FND_SEL_DDR DDRF
#define FND_DB PORTA
#define FND_DB_DDR DDRA
#define MOTOR_PORT PORTB
#define MOTOR_DDR DDRB
#define dTime 10

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>

unsigned char FND[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49, 0x40};
unsigned char DGT[6] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
unsigned char IR_RxCode;
unsigned char num1, num2;
int speed = 0;
int times = 0;
	
void CPU_Setup() {
	FND_SEL_DDR=0xff;
	FND_DB_DDR=0xff;
}

void Motor_Init() {
	MOTOR_DDR |= 0x80;
	MOTOR_PORT &= ~(0x80);
	TCCR2 = 0x61;
	TCNT1 = 0;
}

unsigned int setDutyRate (unsigned int percentage) {
	return(255 * percentage / 100);
}

void motorDrive(char num) {
	
	switch(num) {
		case 0x16: OCR2=setDutyRate(0); break;
		case 0x0c: OCR2=setDutyRate(70); break;
		case 0x18: OCR2=setDutyRate(80); break;
		case 0x5e: OCR2=setDutyRate(100); break;
		case 0x08: 
			OCR2=setDutyRate(speed);
			_delay_ms(times);
			break;
		default: OCR2=setDutyRate(0); break;
	}
}

void FND_Display() {
	for(unsigned char k=0; k<2; k++){
		FND_SEL=DGT[k];
		FND_DB=FND[NUM[k]];
		_delay_ms(dTime);
	}
}

void my_delay_ms(int ms)
{
	while (0 < ms)
	{
		_delay_ms(1);
		--ms;
	}
}

void makeRandom() {
	srand(time(NULL));
	speed = (rand() % 100) + 70;
	times = (rand() % 5000);
	my_delay_ms(times);
}

int main(void) {
	CPU_Setup();
	IR_Init();
	Motor_Init();
	
	sei();
	
	while(1) {
		makeRandom();
		IR_RxCode = get_IR_Code();
		
		NUM[1]=(IR_RxCode>>4)&0x0f;
		NUM[0]=(IR_RxCode)&0x0f;
		
		//num1 = ((IR_RxCode>>3) & 0x0f) | ((IR_RxCode>>4) & 0x0f);
		
		motorDrive(IR_RxCode);
		FND_Display();
	}
}