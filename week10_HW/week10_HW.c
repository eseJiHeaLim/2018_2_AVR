#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include<avr/interrupt.h>

#define INT0_SW  1
#define INT1_SW  2

/*


	1. 숫자가 한바퀴를 돌고나서 계속 여러번 눌러야 다음 바퀴로 돌아옴,,,
	2 .숫자를 누를떄 위에 두 led는 어찌해야하는 친구 ? 켜져있으면 안되겠지?,,,,,,



*/





//글로벌 변수로 바꿈 --> 인터럽트에서는 글로벌 변수 밖에 참조가 안됨 
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


ISR(INT0_vect)	// 외부인터럽트 0번의 ISR
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


ISR(INT1_vect)    // 외부인터럽트 1번의 ISR
{
 cli();
 EIFR |= 0x02; 
 
 	in = INT1_SW;
 sei();

}


int main()
{

	cli();		// 전체 인터럽트 disable
	DDRC = 0xFF;
  	DDRD = 0xF3;
  	DDRB = 0xFF;

	EICRA=0x0F;
   	EIMSK = 0x03;               //EIMSK 1,2번비트SET
	EIFR = 0x03;                //EIFR 1, 2번비트SET
	
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
