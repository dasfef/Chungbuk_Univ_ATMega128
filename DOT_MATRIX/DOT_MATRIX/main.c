#define F_CPU 14745600
#define DOT_COL PORTB
#define DOT_COL_DDR DDRB
#define DOT_ROW PORTE
#define DOT_ROW_DDR DDRE
#define SWITCH PINA
#define dTime 3
#define Speed 15

#include <avr/io.h>
#include <util/delay.h>

unsigned char SMILE_TBL[8] ={0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
unsigned char DOT_COL_TBL[8] ={0x18,0x3C,0x7E,0xFF,0x18,0x18,0x18,0x00};	// Arrow Up
unsigned char DOT_COL2_TBL[8] = {0x00,0x18,0x18,0x18,0xff,0x7e,0x3c,0x18};	// Arrow Down
unsigned char DOT_ROW_TBL[8] ={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
unsigned char ROW=0;
unsigned char Keypad;
unsigned char result;
unsigned char flag=0;

void CPU_Setup() {
	DOT_COL_DDR=0xff;
	DOT_ROW_DDR=0xff;
}

void Dot_Display(int distinguish) {
	unsigned char tRow = ROW;
	
	switch(distinguish) {
		case 0:
			for (int i=0; i<8; i++) {
				DOT_ROW = DOT_ROW_TBL[i];
				DOT_COL = ~DOT_COL_TBL[tRow];
				_delay_ms(dTime);
				if(++ROW > 7) tRow=0;
			}
			break;
		case 1:
			ROW=7;
			for (int k=7; k>=0; k--){
				DOT_ROW = DOT_ROW_TBL[k];
				DOT_COL = ~DOT_COL2_TBL[tRow];
				//DOT_COL = ~DOT_COL_TBL[tRow];
				_delay_ms(dTime);
				if(--tRow < 0) tRow=7;
			}
			break;
		case 2:
			for(int k=0; k<8; k++) {
				DOT_ROW=DOT_ROW_TBL[k];
				DOT_COL=~SMILE_TBL[k];
				_delay_ms(dTime);
			}
	}
}

int SwitchIn() {
	int num = 0;
	Keypad = ~SWITCH;
	switch(Keypad) {
		case 0x01: //smile
			num = 2;
			break;
			
		case 0x02: //Arrow up
			num = 0;
			break;
			
		case 0x04: //Arrow Down
			num = 1;
			break;
	}
	return num;
}

int main(void) {
	CPU_Setup();
	
	while(1) {
		result = SwitchIn();
		Dot_Display(result);
		/*
		for (int k=0; k<Speed; k++){
			Dot_Display();
		}
		if(++ROW >= 8) ROW=0; 
		*/
	}
}