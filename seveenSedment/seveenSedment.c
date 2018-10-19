#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include<util/delay.h>

//정답
#define SEG_PB_MASK 0x3F

unsigned char seg_tb[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
// 굳이 이 B에 대한 값을 넣지 않아도 됨 어짜피 없자너 
unsigned char seg_tb_B[]={0x3F,0x06,0x1B,0x0F,0x26,0x2D,0x3D,0x07,0x3F,0x2F};
unsigned char seg_tb_C[]={0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x01};


void main()
{
	DDRB=0xFF;
	DDRC=0x3F;
	DDRD=0xFF;  // 포트 F 모든 비트를 출력핀으로 

/*
	while(1){
		for (int i = 0 ; i<8;i++)
		{
			PORTD=0x01<<i;
			_delay_ms(500);
		}
	}

	/* 0부터 9까지 출력하기 
	while (1)
	{
		PORTD=0x3F; // --> 0
		_delay_ms(500);
		PORTD=0x06; // --> 1
		_delay_ms(500);
		PORTD=0x5B; // --> 2
		_delay_ms(500);
		PORTD=0x4F; // --> 3
		_delay_ms(500);
		PORTD=0x66; // --> 4
		_delay_ms(500);
		PORTD=0x6D; // --> 5
		_delay_ms(500);
		PORTD=0x7D; // --> 6
		_delay_ms(500);
		PORTD=0x07; // --> 7
		_delay_ms(500);
		PORTD=0x7F; // --> 8
		_delay_ms(500);
		PORTD=0x6F; // --> 9
		_delay_ms(500); // --> delay 빼먹지 말라고 
 	}
	*/

	
	
	
	
	/*
	//내가 만든 비효율 갑 코드 
	while(1){

		for (int i =0 ; i<10;i++)
		{
			PORTD=seg_tb[i];
			PORTB=seg_tb_B[i];
			PORTC=seg_tb_C[i];
			_delay_ms(500);

		}
	}
	*/
	

	/*
	// 교수님의 초효율 코드임
	// 내껀 for 문이 아니면 안되는대 교수님꺼는 어디든 다씀 
	while (1){
		for (int i = 0; i<10;i++)
		{
			PORTD=seg_tb[i]; // index i 에 대응되는 값을 첫 번째 세그먼트로 display

		}
	}
	*/
	
	for (int i = 0 ; i<100 ; i++)
	{
		int dec = i/10;
		int one = i%10;
		PORTD=seg_tb[dec];
		PORTB=seg_tb_B[one];
		PORTC=seg_tb_C[one];
		_delay_ms(500);
	}
	

}	
