#define F_CPU 14745600

#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_PORT PORTB
#define MOTOR_DDR DDRB
#define SWITCH PINA

unsigned char Keypad;

void CPU_Setup(){
	MOTOR_DDR = 0x03;
	DDRA=0x00;
}

int main(void) {
	CPU_Setup();
	
	while(1) {
		Keypad = ~SWITCH;
		switch(Keypad) {
			case 0x01:
				MOTOR_PORT=0x01;	// 정회전
				break;
			case 0x02:
				MOTOR_PORT=0x02;	// 역회전
				break;
			case 0x10:
				MOTOR_PORT=0x00;	// 정지
				break;
		}
		/*
		MOTOR_PORT=0x01;	_delay_ms(1000);	// 정회전
		MOTOR_PORT=0x00;	_delay_ms(4000);
		MOTOR_PORT=0x02;	_delay_ms(1000);	// 역회전
		MOTOR_PORT=0x00;	_delay_ms(4000);
		*/
	}
}