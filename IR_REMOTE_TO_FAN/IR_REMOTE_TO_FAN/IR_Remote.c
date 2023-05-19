
#include "IR_Remote.h"

// 0.000069s, 14.7456MHz, Prescaler 1024
/* NEC Format
  LEADER CODE	: 13.5ms
  DATA CODE
    - LOW BIT	: 1.125ms
    - HIGH BIT	: 2.25ms
*/
#define LEADER_MAX		216			// 69us * 216 = 14.904ms
#define LEADER_MIN		175			// 69us * 175 = 12.075ms
#define LOW_BIT_MAX		19			// 69us * 19 = 1.311ms
#define LOW_BIT_MIN		13			// 69us * 13 = 0.897ms
#define HIGH_BIT_MAX	37			// 69us * 37 = 2.553ms
#define HIGH_BIT_MIN	28			// 69us * 28 = 1.932ms

volatile unsigned char IR_State = 0;
volatile unsigned char IR_TimeCount;	// ��ȣ�� ���̸� Ȯ���ϴ� ī��Ʈ
volatile unsigned char IR_BitCount;		// ������ �� ���Ž�, BIT ���� ī��Ʈ
volatile unsigned char IR_RxBit;			// BIT ���� ������ �� ����

//volatile unsigned char IR_Code[4];	// ���ŵ� ������ �� ����

ISR(TIMER0_OVF_vect) {
	cli();
	IR_State = 0;
	sei();
}

ISR(INT0_vect) {
	cli();

	IR_TimeCount = TCNT0;		// ī���͸� �̿��� ��ȣ ���� �ð� ����
	TCNT0 = 0;					// ī��Ʈ �ʱ�ȭ

	sei();
	
	switch(IR_State) {			// ���� ���� �����ϸ鼭 ��ȣ ������ ���������� ����
		case 0:
			IR_State = 1;		// ���� �ܰ�� ����
			IR_TimeCount = 0;	// ī��Ʈ �ʱ�ȭ
			break;

		case 1:	//leader code
			if((IR_TimeCount>=LEADER_MIN)&&(IR_TimeCount<=LEADER_MAX)) 	{
				IR_State = 2;		// ���� �ܰ�� ����
				IR_TimeCount = 0;	// ī��Ʈ �ʱ�ȭ
				IR_BitCount = 0;
				IR_RxBit = 0;
			} else 	{
				IR_State = 0;
			}
			break;

		case 2:	//Data Receive
			IR_RxBit>>=1;
			if((IR_TimeCount>=LOW_BIT_MIN)&&(IR_TimeCount<=LOW_BIT_MAX)) {
				IR_RxBit &= 0x7F;		// LOW
			} else if((IR_TimeCount>=HIGH_BIT_MIN)&&(IR_TimeCount<=HIGH_BIT_MAX)) {
				IR_RxBit |= 0x80;		// HIGH
			} else	{
				IR_State = 0;
			}
		
			IR_TimeCount = 0;
			IR_BitCount++;
		
			if((IR_BitCount%8) == 0) {		// 8�� BIT�� ���Žø���
				IR_Code[(IR_BitCount/8)-1] = IR_RxBit;
				IR_RxBit = 0;
			}

			if(IR_BitCount==32) {		// 4 BYTE ���Ž�
				if((~IR_Code[2] & 0xFF) == IR_Code[3]) {
					IR_State = 0;
					IR_BitCount = 0;
				} else {
					// Error- �ԷµǴ� ���� ������ ����ġ
					IR_State = 0;
					IR_BitCount = 0;
				}
			}
			break;
		
		default :
			break;
	}
	sei();
}

unsigned char get_IR_Code (void) {
	return IR_Code[2];
}

void clear_IR_Code (void) {
	IR_Code[2] = 0;
}

void Ext_Int0_Init() {
	// External Interrupt 0 Enable : PORTD.0
	EICRA	|=	0x02;	// falling edge
	EICRB	|=	0x00;
	EIMSK	|=	0x01;
	EIFR	|=	0x01;
}

void Timer0_Init() {
	// Timer/Counter0 Control register Clock Select(prescaler 1024)
	// 1/(14745600Hz/1024) = 0.000069s
	TCCR0 = 0x07;	// prescaler 1024

	// TOIE0 = 0x01, (Timer/Counter0 Overflow Interrupt Enable)
	TIMSK = 0x01;
}

void IR_Init()
{
	IR_DDR = 0x00;
	Timer0_Init();
	Ext_Int0_Init();
}

