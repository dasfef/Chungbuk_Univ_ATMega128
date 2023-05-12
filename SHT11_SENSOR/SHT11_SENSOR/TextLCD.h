/********************************************************************

 파 일 : Textlcd.h

 소스 설명 :
 1) 입출력 관련 헤더파일을 선언
 2) Delay 관련 헤더파일을 선언
 3) PORTB 정의
 4) DDRB 정의
 5) PORTE 정의
 6) DDRE 정의

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