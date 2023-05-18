#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_PORT PORTB
#define MOTOR_DDR DDRB

unsigned int setDutyRate (unsigned int percentage) {
	return (255 * percentage / 100);
}

void Motor_Init(){
	MOTOR_DDR |= 0x80;
	MOTOR_PORT &= ~(0x80);
	// 8bit Timer / Counter2 with PWM
	// Phase Correct PWM, No Prascaling, non-inverting mode
	TCCR2 = 0x61;	// Set PWM
	TCNT2 = 0;
}

int main(void) {
	Motor_Init();
	
	while(1) {
		OCR2 = setDutyRate(0);	_delay_ms(2000);
		OCR2 = setDutyRate(10);	_delay_ms(2000);
		OCR2 = setDutyRate(20);	_delay_ms(2000);
		OCR2 = setDutyRate(30);	_delay_ms(2000);
		OCR2 = setDutyRate(50);	_delay_ms(2000);
		OCR2 = setDutyRate(70);	_delay_ms(2000);
		OCR2 = setDutyRate(80);	_delay_ms(2000);
		OCR2 = setDutyRate(90);	_delay_ms(2000);
		OCR2 = setDutyRate(100);_delay_ms(2000);
	}
}