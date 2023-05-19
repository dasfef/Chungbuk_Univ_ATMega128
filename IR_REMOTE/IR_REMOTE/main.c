#include "IR_Remote.c"

#define FND_SEL PORTB
#define FND_SEL_DDR DDRB
#define FND_DB PORTE
#define FND_DB_DDR DDRE

#define dTime 10

unsigned char FND[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x40, 0x49, 0x40};
unsigned char DGT[6] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf};
unsigned char NUM[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
unsigned char IR_RxCode;

void CPU_Setup(){
	FND_SEL_DDR = 0xff;
	FND_DB_DDR = 0xff;
}

void FND_Display() {
	for (unsigned char k=0; k<2; k++){
		FND_SEL=DGT[k];
		FND_DB=FND[NUM[k]];
		_delay_ms(dTime);
	}
}

int main(void) {
	CPU_Setup();
	IR_Init();
	sei();
	
	while(1) {
		IR_RxCode = get_IR_Code();
		NUM[1]=(IR_RxCode >> 4) & 0x0f;
		NUM[0]=(IR_RxCode)&0x0f;
		
		FND_Display();
	}
}