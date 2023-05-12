/********************************************************************

 �� �� : Textlcd.h

 �ҽ� ���� :
 1) ����� ���� ��������� ����
 2) Delay ���� ��������� ����
 3) PORTB ����
 4) DDRB ����
 5) PORTE ����
 6) DDRE ����

********************************************************************/

#ifndef __TEXTLCD_H__
#define __TEXTLCD_H__

#define F_CPU		14745600UL	
#include <avr/io.h>
#include <util/delay.h>

#define LCD_CD_PORT		PORTB
#define LCD_CD_DDR		DDRB
#define LCD_DB_PORT		PORTE
#define LCD_DB_DDR		DDRE

#endif	/* __LCD_H__ */