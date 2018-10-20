#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include<util/delay.h>

// 10 자리 세그먼트를 표현에 사용되는 행렬 
// 0번 행은 PORTD
// 1번 행은 PORTB 
unsigned char seg_1[2][10] = {{0xF0, 0x60, 0xB0, 0xF0, 0x60, 0xD0, 0xD0, 0x70, 0xF0, 0xF0},
							  {0x03, 0x00, 0x05, 0x04, 0x06, 0x06, 0x07, 0x02, 0x07, 0x06}};


// 일의 자리 세그먼트를 표현에 사용되는 행렬 
// 0번 행은 PORTB
// 1번 행은 PORTC

unsigned char seg_2[2][10] = {{0x30, 0x20, 0x30, 0x30, 0x20, 0x10, 0x10, 0x30, 0x30, 0x30},
							  {0x0F, 0x01, 0x16, 0x13, 0x19, 0x1B, 0x1F, 0x09, 0x1F, 0x1B}};


void main()
{
	DDRD=0xF0;
	DDRB=0x3F;
	DDRC=0x3F;
	
	while(1)
	{
		// 0~99까지 증가 
		for(int i =0 ; i<100;i++)
		{
			PORTD=seg_1[0][i/10];
			PORTB=seg_2[0][i%10]|seg_1[1][i/10];
			PORTC=seg_2[1][i%10];
		
			_delay_ms(500);
		}
		//99~0 까지의 감소 
		for(int i =99 ; i>0;i--)
		{
			PORTD=seg_1[0][i/10];
			PORTB=seg_2[0][i%10]|seg_1[1][i/10];
			PORTC=seg_2[1][i%10];
		
			_delay_ms(500);
		}
	}

}
