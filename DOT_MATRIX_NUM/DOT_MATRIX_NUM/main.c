#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

#define DOT_COL PORTB
#define DOT_COL_DDR DDRB
#define DOT_ROW PORTE
#define DOT_ROW_DDR DDRE
#define dTime 3
#define Speed 50
unsigned char Count=0;
void CPU_Setup( ) {
	DOT_COL_DDR=0xff;
	DOT_ROW_DDR=0xff;
}

unsigned char DOT_SEL[8] ={0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char DOT_NUM[10][8]={ {0x7e, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7e}, //0
{0x38, 0x3c, 0x3e, 0x38, 0x38, 0x38, 0x38, 0x38}, //1
{0x7e, 0xff, 0xe7, 0x70, 0x1c, 0x06, 0xff, 0xff}, //2
{0x7f, 0xff, 0xe0, 0x7f, 0x7f, 0xe0, 0xff, 0x7f}, //3
{0x77, 0x77, 0x77, 0xff, 0xff, 0x70, 0x70, 0x70}, //4
{0xff, 0xff, 0x07, 0x7f, 0xff, 0xe0, 0xff, 0x7e}, //5
{0x7e, 0xff, 0x07, 0x7f, 0xff, 0xe7, 0xff, 0x7e}, //6
{0xff, 0xff, 0xe0, 0x70, 0x38, 0x1c, 0x1c, 0x1c}, //7
{0x7e, 0xff, 0xe7, 0x7e, 0x7e, 0xe7, 0xff, 0x7e}, //8
{0x7e, 0xff, 0xe7, 0xff, 0xfe, 0xe0, 0xff, 0x7e} }; //9
	
void Dot_Display(unsigned char num){
	for (char k=0; k<8;k++){
		DOT_ROW=DOT_SEL[k];
		DOT_COL=~DOT_NUM[num][k];
		_delay_ms(dTime);
	}
}
int main(void) {
	CPU_Setup( );
	while (1) {
		for (int k=0;k<Speed;k++){
			Dot_Display(Count);
		}
		if (++Count>9) Count=0;
	}
}