#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include<util/delay.h>

//����
#define SEG_PB_MASK 0x3F

unsigned char seg_tb[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
// ���� �� B�� ���� ���� ���� �ʾƵ� �� ��¥�� ���ڳ� 
unsigned char seg_tb_B[]={0x3F,0x06,0x1B,0x0F,0x26,0x2D,0x3D,0x07,0x3F,0x2F};
unsigned char seg_tb_C[]={0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x01,0x01};


void main()
{
	DDRB=0xFF;
	DDRC=0x3F;
	DDRD=0xFF;  // ��Ʈ F ��� ��Ʈ�� ��������� 

/*
	while(1){
		for (int i = 0 ; i<8;i++)
		{
			PORTD=0x01<<i;
			_delay_ms(500);
		}
	}

	/* 0���� 9���� ����ϱ� 
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
		_delay_ms(500); // --> delay ������ ����� 
 	}
	*/

	
	
	
	
	/*
	//���� ���� ��ȿ�� �� �ڵ� 
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
	// �������� ��ȿ�� �ڵ���
	// ���� for ���� �ƴϸ� �ȵǴ´� �����Բ��� ���� �پ� 
	while (1){
		for (int i = 0; i<10;i++)
		{
			PORTD=seg_tb[i]; // index i �� �����Ǵ� ���� ù ��° ���׸�Ʈ�� display

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
