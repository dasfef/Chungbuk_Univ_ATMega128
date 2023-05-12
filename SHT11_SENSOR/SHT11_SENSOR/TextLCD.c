/********************************************************************
 파 일 : TextlCD.c
********************************************************************/

#include "TextLCD.h"

void write_Data ( unsigned char data )
{
	LCD_CD_PORT	=	0x00;		/* RS = 0, R/W = 0, E = 0 */
	LCD_CD_PORT	|=	0x01;		/* RS = 1, DR->DDRAM */
	LCD_DB_PORT	=	data;

	LCD_CD_PORT	|=	0x04;		/* E = 1 */
	_delay_us(110);				/* Essential Delay for Simulator */
	LCD_CD_PORT	&=	~(0x04);	/* E = 0 */
	_delay_us(110);
}

void printString ( char *string )
{
	while ( *string != '\0' )
	{
		write_Data ( *string );
		string ++;
	}
}

void write_Command ( unsigned char command )
{
	LCD_CD_PORT	=	0x00;		/* E = 0, R/W = 0, RS = 0 */
	LCD_DB_PORT	=	command;	/* Command */

	LCD_CD_PORT	|=	0x04;		/* E = 1 */
	_delay_us(110);				/* Essential Delay for Simulator */
	LCD_CD_PORT	&=	~(0x04);	/* E = 0 */
	_delay_us(110);
}

void LCD_Init (void)
{
	LCD_DB_DDR		=	0xFF;
	LCD_DB_PORT		=	0x00;
	LCD_CD_DDR		=	0x07;	// 신호선 3 PIN  출력설정
	LCD_CD_PORT		=	0x00;

	_delay_us(110);
	LCD_CD_PORT	&=	~(0x04);	/* E = 0 */
	_delay_us(110);

	write_Command(0x38);		/* Function set */
	_delay_us(220);

	write_Command(0x0F);		/* Display ON */
	_delay_us(220);

	write_Command(0x02);		/* Cursor At Home */
	_delay_ms(9);

	write_Command(0x01);		/* Clear Display */
	_delay_ms(9);

	write_Command(0x06);		/* Entry mode set */
	_delay_us(220);
}