#define F_CPU 14745600
#define LCD_CD_PORT PORTB
#define LCD_CD_DDR DDRB
#define LCD_DB_PORT PORTE
#define LCD_DB_DDR DDRE

#include <avr/io.h>
#include <util/delay.h>

void write_Command ( unsigned char command ) {
	LCD_CD_PORT = 0x00; /* E = 0, R/W = 0, RS = 0 */
	LCD_DB_PORT = command; /* Command */
	LCD_CD_PORT |= 0x04; _delay_us(110); /* E = 1 Essential Delay for Simulator */
	LCD_CD_PORT &= ~(0x04); _delay_us(110); /* E = 0 */
}
void write_Data ( unsigned char data ) {
	LCD_CD_PORT = 0x00; /* RS = 0, R/W = 0, E = 0 */
	LCD_CD_PORT |= 0x01; /* RS = 1, DR->DDRAM */
	LCD_DB_PORT = data;
	LCD_CD_PORT |= 0x04; /* E = 1 */
	_delay_us(110); /* Essential Delay for Simulator */
	LCD_CD_PORT &= ~(0x04); /* E = 0 */
	_delay_us(110)
}

void printString ( char *string ) {
	while ( *string != '\0' ) {
		write_Data ( *string );
		string ++;
	}
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

