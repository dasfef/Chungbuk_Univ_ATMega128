/*
 * IR_Remote.h
 *
 * Created: 2018-08-13 오후 9:28:13
 *  Author: user
 */ 


#ifndef __IR_Remote_H__
#define __IR_Remote_H__

#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define IR_DDR		DDRD

volatile unsigned char IR_Code[4];

void IR_Init();
unsigned char get_IR_Code (void);
void clear_IR_Code (void);


#endif /* _IRremote_H_ */