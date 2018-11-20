#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include<avr/interrupt.h>

#define INT0_SW  1
#define INT1_SW  2
int i;
//글로벌 변수로 바꿈 --> 인터럽트에서는 글로벌 변수 밖에 참조가 안됨 
unsigned char in;
int count = 0;
int flag=0;

void led_shift(void)
{
				for (int i= 0;i<3;i++)
				{
					PORTB = (PORTB|0x30)&(~(0x10<<i));

					_delay_ms(300);

				}

				for (int i= 0;i<6;i++)
				{
					PORTC= ~(0x01<<i);

					_delay_ms(300);
				
				}
			
			
	
				for (int i= 0;i<6;i++)
				{
					PORTC= ~(0x10>>i);
					_delay_ms(300);
				
				}
						for (int i= 0;i<2;i++)
				{
					PORTB = (PORTB|0x30)&(~(0x20>>i));
					_delay_ms(300);

				}
}

void disp_seg(int cnt)
{
	unsigned char seg_1[2][10] = {{0xF0, 0x60, 0xB0, 0xF0, 0x60, 0xD0, 0xD0, 0x70, 0xF0, 0xF0},
							  {0x03, 0x00, 0x05, 0x04, 0x06, 0x06, 0x07, 0x02, 0x07, 0x06}};
			PORTD=seg_1[0][cnt];
			PORTB=seg_1[1][cnt]| 0x30;
}


ISR(INT0_vect)	// 외부인터럽트 0번의 ISR
{
   cli();		// clear Interrupt
   EIFR |= 0x01; 	// Interrupt Flag set
   count = ++i;
   count=count%10;

   disp_seg(count);	
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
	PORTC = 0xFF;
	PORTB = 0x30;

	EICRA = 0x0F;	// sense control (Rising Edge)
   	EIMSK = 0x03;               //EIMSK 1,2번비트SET
	EIFR = 0x03;                //EIFR 1, 2번비트SET
	
	sei();		//global interrupt enable

	// Refer to the upper box}
	while(1)
		{
			if(in == INT1_SW)// switch 누르면 count up & display
			{ 
				in = 0;
				for(i = count;i > 0;i--)// 현재 count 횟수만큼 shift
				{   
					if(in == INT0_SW)
					{
						break;
					}
					if(in == INT1_SW)
					{
						disp_seg(i);
						break;
					}
					led_shift();
					disp_seg(i-1);
				}
				count = i;
				disp_seg(count);
				in =0;
			
			}
		}	
}
