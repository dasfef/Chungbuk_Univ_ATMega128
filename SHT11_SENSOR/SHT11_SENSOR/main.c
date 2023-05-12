#include "TextLCD.c"
#include "SHT11.c"

unsigned char ASCII[17] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x20};
//불쾌지수 전용
unsigned char DISP1[17] = {'T', '=', '0','0','.','0','C',' ','H','=','0','0','.','0','%',' '};
unsigned char DISP2[17] = {' ','D','I','n','d','e','x','=',' ','0','0','.','0',' ',' ',' '};
	/*
unsigned char DISP1[17] = {' ', ' ', 'T', 'e', 'm', 'p', '=', '0', '0', '.', '0','C', ' ', ' ', ' '};
unsigned char DISP2[17] = {' ', ' ', 'H', 'u', 'm', 'i', '=', '0', '0', '0', '.','0', '%', ' ', ' '};*/
unsigned int Temp = 0;
unsigned int Humi = 0;
unsigned int dIndex = 0;

// 불쾌지수 계산 메소드 DiscomfortIndex
float DiscomfortIndex(float temp, float humi) {
	return (1.8f * temp) - (0.55 * (1-humi/100.0f) * (1.8f*temp-26)) + 32;
}

void Hex2ASC(char temp, char humi, char dindex){
	unsigned int tmpNo = temp;
	/*
	DISP1[7] = ASCII[tmpNo / 100];
	tmpNo = tmpNo % 100;
	DISP1[8] = ASCII[tmpNo / 10];
	DISP1[10] = ASCII[tmpNo % 10];
	
	tmpNo = humi;
	DISP2[7] = ASCII[tmpNo / 1000];
	tmpNo = tmpNo % 1000;
	DISP2[8] = ASCII[tmpNo / 100];
	tmpNo = tmpNo % 100;
	DISP2[9] = ASCII[tmpNo / 10];
	DISP2[11] = ASCII[tmpNo % 10];
	*/
	
	// 불쾌지수 전용 LCD 위치
	DISP1[2] = ASCII[tmpNo / 100];
	tmpNo = tmpNo % 100;
	DISP1[3] = ASCII[tmpNo / 10];
	DISP1[5] = ASCII[tmpNo % 10];
	
	tmpNo = humi;
	DISP1[10] = ASCII[tmpNo / 100];
	tmpNo = tmpNo % 100;
	DISP1[11] = ASCII[tmpNo / 10];
	DISP1[13] = ASCII[tmpNo % 10];
	
	tmpNo = dindex;
	DISP2[9] = ASCII[tmpNo / 100];
	tmpNo = tmpNo % 100;
	DISP2[10] = ASCII[tmpNo / 10];
	DISP2[12] = ASCII[tmpNo % 10];
}

int main(void) {
	SHT11_Init();
	LCD_Init();
	
	write_Command(0x01); _delay_ms(9);
	
	while(1){
		//Hex2ASC(Temp, Humi);
		Temp = get_SHT11_data(TEMP);
		Humi = get_SHT11_data(HUMI);
		
		Hex2ASC(Temp, Humi, dIndex);
		
		write_Command(0x80); _delay_us(220);
		printString(DISP1);
		write_Command(0xc0); _delay_us(220);
		printString(DISP2);
		
		// 아래부턴 불쾌지수 계산용
		float fTemp = Temp / 10.0f;
		float fHumi = Humi / 10.0f;
		dIndex = DiscomfortIndex(fTemp, fHumi) * 10.0f;
		
		
	}
}