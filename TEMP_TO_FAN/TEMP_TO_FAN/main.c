#include "SHT11.c"
#define FND_SEL PORTB
#define FND_DB PORTE
#define FAN PORTC
#define dTime 3

#include <avr/io.h>
#include <util/delay.h>

unsigned char FND[17]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49,0x40};
unsigned char DGT[6]={0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
unsigned int PV = 0;
unsigned int SV = 100;		// user define Set Value
unsigned int Hb = 1;		// user define Hysteresis Band Value

#define MaxQue 20
unsigned int QTemp[MaxQue];
unsigned int Temp = 0;
unsigned int QPoint = 0;

unsigned int ADConv(unsigned char Channel) {
	ADMUX = (Channel & 0x03);
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS1) | (1<<ADPS0);
	_delay_us(100);
	while(~ADCSRA & 0x10);
	return ADC;
}

void Hex2Dec(unsigned int No){
	unsigned int tmp=No;
	NUM[5]=8;
	NUM[4]=16;
	NUM[3]=tmp/1000;
	tmp=tmp%1000;
	NUM[2]=tmp/100;
	tmp=tmp%100;
	NUM[1]=tmp/10;
	NUM[0]=tmp%10;
}

void FND_Display(){
	for (unsigned char k=0; k<6; k++) {
		FND_SEL=DGT[k];
		FND_DB=FND[ NUM[k] ];
		_delay_ms(dTime );
	}
}

void CircularQueue(int Value) {
	QTemp[QPoint] = Value;
	if (++QPoint > MaxQue -1) QPoint = 0;
}

void Hysteresis(unsigned int Val) {
	if((SV+Hb) > Val) {
		FAN = 0x00;
	} else if((SV-Hb) < Val) {
		FAN = 0x01;
	}
}

int main(void) {
	SHT11_Init();
	
	while(1) {
		Temp = get_SHT11_data(TEMP);
		Hex2Dec(Temp);
		CircularQueue(Temp);
		
		FND_Display();
		
		
	}
}