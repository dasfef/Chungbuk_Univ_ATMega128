/********************************************************************

 �� �� : lcd.h

 �ҽ� ���� :
 1) ����� ���� ������� ����
 2) Delay ���� ������� ����
 3) ���ͷ�Ʈ ���� ������� ����
 4) �µ��� ������ ��Ÿ���� ���ڿ� ���� ����
 5) ��/���� ������ I2C ���� �Լ��� ������Ÿ���� ����
 
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
