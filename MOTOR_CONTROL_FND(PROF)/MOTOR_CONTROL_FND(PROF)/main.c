#define F_CPU 14745600UL
#include "SHT11.c"
#include "TextLCD.c"

#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_PORT PORTB
#define MOTOR_DDR DDRB

#define FND_SEL PORTD
#define FND_SEL_DDR DDRD
#define FND_DB PORTC
#define FND_DB_DDR DDRC

#define SWITCH PINA


#define dTime 3

unsigned int Temp=0;
unsigned int SetTemp=38;

unsigned char FND[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x40,0x49,0x08};
unsigned char DGT[6]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};
unsigned NUM[6]={0x00,0x00,0x00,0x00,0x00,0x00};

unsigned int setDutyRate(unsigned int percentage){
	return (255*percentage/100);
}

void FND_Display(){
	for(unsigned char k=0;k<6;k++){
		FND_SEL=DGT[k];
		FND_DB=FND[NUM[k]];
		_delay_ms(dTime);
	}
}

void Hex2ASC(int Stemp,int VTemp){
	int tmpNo=VTemp;
	NUM[5]=tmpNo/100;
	tmpNo=tmpNo%100;
	NUM[4]=tmpNo/10;
	NUM[3]=tmpNo%10;
	
	tmpNo=Stemp;
	NUM[2]=tmpNo/100;
	tmpNo=tmpNo%100;
	NUM[1]=tmpNo/10;
	NUM[0]=tmpNo%10;
}

void CPU_Setup(){
	MOTOR_DDR |= 0x80;
	MOTOR_PORT &=~(0x80);
	
	FND_SEL_DDR=0xff;
	FND_DB_DDR=0xff;
	
	DDRA = 0x00;
	
	TCCR2=0x61;
	TCNT2=0;
	
	
}

unsigned char GetT(){
	Temp=get_SHT11_data(TEMP)/10;
	return Temp;
}
unsigned char NewKey;
unsigned char oldKey=0;

void scanKey(){
	unsigned char keyBuffer=~SWITCH;
	NewKey=keyBuffer;
	if(NewKey!=oldKey){
		switch(keyBuffer){
			case 0x01:
			
			if(++SetTemp>45) SetTemp=45;
			break;
			case 0x10:
			if(--SetTemp<20) SetTemp=20;
			break;
		}
		oldKey=NewKey;
	}
}

unsigned char Count=0;

int main(void)
{
	CPU_Setup();
	SHT11_Init();
	
	while (1)
	{
		if(Count==0){
			Temp=get_SHT11_data(TEMP);
			}else{
			scanKey();
			
			Hex2ASC(SetTemp,Temp);
			FND_Display();
			
			
		}
		
		Count++;
		

		
	}
}
