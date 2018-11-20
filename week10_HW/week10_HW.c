#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include<avr/interrupt.h>

#define INT0_SW  1
#define INT1_SW  2

/*


	1. ���ڰ� �ѹ����� ������ ��� ������ ������ ���� ������ ���ƿ�,,,
	2 .���ڸ� ������ ���� �� led�� �����ؾ��ϴ� ģ�� ? ���������� �ȵǰ���?,,,,,,



*/





//�۷ι� ������ �ٲ� --> ���ͷ�Ʈ������ �۷ι� ���� �ۿ� ������ �ȵ� 
unsigned char in;
int count =0;

void led_on_off(void)
{

		PORTB&=0x0F;
		PORTC=0x00;
		_delay_ms(300);
		PORTB|=0xF0;
		PORTC=0xFF;
		_delay_ms(300);
}

void disp_seg(int cnt)
{
	unsigned char seg_1[2][4] = {{0xF0, 0x60, 0xB0, 0xF0},
							  {0x03, 0x00, 0x05, 0x04}};
			PORTD=seg_1[0][cnt];
			PORTB=seg_1[1][cnt];
}


ISR(INT0_vect)	// �ܺ����ͷ�Ʈ 0���� ISR
{
   cli();		// clear Interrupt
   EIFR |= 0x01; 
   count++;
   count=count%4;
   disp_seg(count);
   	
	if (count==0 )
	{
		EICRA=0x03;
	}
	else if (count ==1)
	{
		EICRA=0x07;
	}
	else if (count ==2)
	{
		EICRA=0x0B;
	}
					
	else if (count ==3)
	{
		EICRA=0x0F;
	}	
   
   in = INT0_SW;

    sei();		// set interrupt	
}


ISR(INT1_vect)    // �ܺ����ͷ�Ʈ 1���� ISR
{
 cli();
 EIFR |= 0x02; 
 
 	in = INT1_SW;
 sei();

}


int main()
{

	cli();		// ��ü ���ͷ�Ʈ disable
	DDRC = 0xFF;
  	DDRD = 0xF3;
  	DDRB = 0xFF;

	EICRA=0x0F;
   	EIMSK = 0x03;               //EIMSK 1,2����ƮSET
	EIFR = 0x03;                //EIFR 1, 2����ƮSET
	
	sei();		//global interrupt enable

	while(1)
	{
		if(in == INT1_SW)
		{ 
			in=0;
			for (int i =0 ;i<10;i++)
			{
				if(in == INT0_SW)
				{
					break;
				}
				if(in == INT1_SW)
				{
					break;
				}
				led_on_off();
			}
			in=0;
		}
	}

}
