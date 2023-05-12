#define F_CPU 14745600
#define LCD_CD_PORT PORTB
#define LCD_DB_PORT PORTE
#define LCD_CD_DDR DDRB
#define LCD_DB_DDR DDRE

#include <avr/io.h>
#include <util/delay.h>

unsigned char ASCII[17] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x20};
unsigned char DISP[17] = {'C', 'd', 'S', '=', '0', '0', '0', '0', ' ', 'P', 't', '=', '0', '0', '0', '0'};
unsigned int CdS = 0;
unsigned int PTR = 0;

void Setup_CPU() {
	DDRF = 0xf0;
	PORTF = 0xdf;
}

void Hex2ASC(int tCdS, int tPt){
	int tmpNo=tCdS;
	DISP[4]=ASCII[tmpNo/1000];
	tmpNo %=1000;
	DISP[5]=ASCII[tmpNo/100];
	tmpNo %=100;
	DISP[6]=ASCII[tmpNo/10];
	DISP[7]=ASCII[tmpNo % 10];
	tmpNo=tPt;
	DISP[12]=ASCII[tmpNo/1000];
	tmpNo %=1000;
	DISP[13]=ASCII[tmpNo/100];
	tmpNo %=100;
	DISP[14]=ASCII[tmpNo/10];
	DISP[15]=ASCII[tmpNo % 10];
}

unsigned int ADConv(unsigned char Channel) {
	ADMUX = (Channel & 0x03);
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS1) | (1<<ADPS0);
	_delay_us(100);
	while(!ADCSRA && 0x10);
	return ADC;
}

void write_Command ( unsigned char command ) {
	LCD_CD_PORT = 0x00; /* E = 0, R/W = 0, RS = 0 */
	LCD_DB_PORT = command; /* Command */
	LCD_CD_PORT |= 0x04; _delay_us(110); /* E = 1 Essential Delay for Simulator */
	LCD_CD_PORT &= ~(0x04); _delay_us(110); /* E = 0 */
}

void LCD_Init (void) {
	LCD_DB_DDR=0xFF;
	LCD_DB_PORT=0x00;
	LCD_CD_DDR=0x07; // 신호선 3 PIN 출력설정
	LCD_CD_PORT=0x00;
	_delay_us(110);
	LCD_CD_PORT &= ~(0x04); _delay_us(110); /* E = 0 */
	write_Command(0x38); _delay_us(220); /* Function set */
	write_Command(0x0F); _delay_us(220); /* Display ON */
	write_Command(0x02); _delay_ms(9); /* Cursor At Home */
	write_Command(0x01); _delay_ms(9); /* Clear Display */
	write_Command(0x06); _delay_us(220); /* Entry mode set */
}

void write_Data ( unsigned char data ) {
	LCD_CD_PORT = 0x00; /* RS = 0, R/W = 0, E = 0 */
	LCD_CD_PORT |= 0x01; /* RS = 1, DR->DDRAM */
	LCD_DB_PORT = data;
	LCD_CD_PORT |= 0x04; /* E = 1 */
	_delay_us(110); /* Essential Delay for Simulator */
	LCD_CD_PORT &= ~(0x04); /* E = 0 */
	_delay_us(110);
}

void printString ( char *string ) {
	while ( *string != '\0' ) {
		write_Data ( *string );
		string ++;
	}
}

int main(void) {
	Setup_CPU();
	LCD_Init();
	
	write_Command(0x01); _delay_ms(9);
	write_Command(0x80); _delay_us(220);
	printString(" IoT Smart SW ");
	write_Command(0xc0); _delay_us(220);
	printString(DISP);
	_delay_ms(500);
	
	while(1){
		Hex2ASC(CdS, PTR);
		write_Command(0xc0); _delay_us(220);
		printString(DISP); _delay_ms(500);
		PTR = ADConv(0);
		CdS = ADConv(1);
	}
}