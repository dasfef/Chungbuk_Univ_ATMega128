/********************************************************************

 파 일 : lcd.h

 소스 설명 :
 1) 입출력 관련 헤더파일 선언
 2) Delay 관련 헤더파일 선언
 3) 인터럽트 관련 헤더파일 선언
 4) 온도와 습도를 나타내는 문자열 변수 선언
 5) 온/습도 센서와 I2C 관련 함수의 프로토타입을 선언
 
********************************************************************/

#ifndef	__SHT11_H__
#define	__SHT11_H__

#define F_CPU		14745600UL	
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum { TEMP, HUMI };

void SHT11_Init (void);
void Connection_reset (void);
void Transmission_start (void);
unsigned short get_SHT11_data (unsigned char type);
unsigned char Write_byte (unsigned char value);
unsigned char Read_byte (unsigned char ack);
unsigned char Measure (unsigned short *p_value, 
						unsigned short *p_checksum,	unsigned char mode);
void calc_SHT11 (unsigned short p_humidity ,unsigned short p_temperature);

#endif	/* __LIB_SENSOR_H__ */
