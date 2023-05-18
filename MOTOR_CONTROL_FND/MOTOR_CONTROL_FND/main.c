#include "SHT11.c"

#define F_CPU 14745600UL
#define FND_SEL PORTD
#define FND_DB PORTC
#define MOTOR_PORT PORTB
#define MOTOR_DDR DDRB
#define SWITCH PINA
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>

//unsigned char FND[11]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x40};
unsigned char FND[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49, 0x40};
unsigned char DGT[6] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
unsigned char newKey;
unsigned char oldKey = 0;
unsigned char Keypad;
unsigned char speed = 0;

int difTemp = 0;
int Count = 0;

unsigned int Temp = 0;
int setTemp = 20;
	
void Hex2Dec(char temp, char setTemp) {
	unsigned int tmp = Temp;
	NUM[5]=tmp/100;
	tmp = tmp % 100;
	NUM[4]=tmp/10;
	NUM[3]=tmp%10;
		
	tmp = setTemp;
	NUM[2]=tmp/100;
	tmp = tmp % 100;
	NUM[1]=tmp/10;
	NUM[0]=tmp%10;
}

void FND_Display(){
	for (unsigned char k=0; k<6; k++){
		FND_SEL=DGT[k];
		FND_DB=FND[NUM[k]];
		_delay_ms(dTime);
	}
}

void Motor_Init(){
	MOTOR_DDR |= 0x80;
	MOTOR_PORT &= ~(0x80);
	TCCR2 = 0x61;
	TCNT2 = 0;
}

unsigned int setDutyRate (unsigned int percentage) {
	return (255 * percentage / 100);
}


void scanKey() {
	Keypad = ~SWITCH;
	newKey = Keypad;
	if(newKey != oldKey) {
		switch(Keypad) {
			case 0x01:
				if(++setTemp>45) setTemp=45;
				break;
			case 0x10:
				if(--setTemp<0) setTemp=0;
				break;
				/*
			case 0x02:
				if(speed==0){
					speedFan(80);
					OCR2=setDutyRate(80);
				} else {speed=1;}
				break;
			case 0x04:
				if(speed==0){
					OCR2=setDutyRate(90);
				} else {speed=1;}
				break;
			case 0x08:
				if(speed==0){
					OCR2=setDutyRate(100);	
				} else{speed=1;}
				break;
				*/
		}
		oldKey = newKey;
	}
}

void CPU_Setup(){
	DDRD=0xff;
	DDRC=0xff;
	DDRA=0x00;
}

int main(void) {
	SHT11_Init();
	CPU_Setup();
	Motor_Init();
	
	while(1){
		if(Count == 0){
			Temp = get_SHT11_data(TEMP);
		} else {
			scanKey();
			
			Hex2Dec(Temp, setTemp);
			FND_Display();
			
			difTemp = ((Temp/10)/setTemp*100);
			
			if(difTemp<=100) {
				OCR2=setDutyRate(70);
				if(difTemp<=80) {
					OCR2=setDutyRate(80);
					if(difTemp<=60) {
						OCR2=setDutyRate(100);
					}
				}
			} else {
				OCR2=setDutyRate(0);
			}
		}
		
		/*
		if (realTemp > setTemp) {
			OCR2 = setDutyRate(90);
			//_delay_ms(2000);
		} else {
			OCR2 = setDutyRate(0);
			//_delay_ms(2000);
		}
		*/
		Count++;
		if (Count > 50) Count=0;
		
	}
}