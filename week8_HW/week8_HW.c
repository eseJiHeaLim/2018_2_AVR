#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char seg_1[2][10] = {{0xF0, 0x60, 0xB0, 0xF0, 0x60, 0xD0, 0xD0, 0x70, 0xF0, 0xF0},
							  {0x03, 0x00, 0x05, 0x04, 0x06, 0x06, 0x07, 0x02, 0x07, 0x06}};

int   main()
{
	unsigned char in;

	DDRD = 0xF3;
	DDRB = 0xFF;
	DDRC=0xFF;
	int cnt=0;
	
	
	while(1){ 
	
	
		in = (PIND & 0x0C);	
		  // PD2, PD3 입력값 확인
		if (in== 0x04)
		{
				cnt=cnt+1;
			if (cnt==10)
			{
				cnt=0;
			}
			PORTD=seg_1[0][cnt];
			PORTB=seg_1[1][cnt];
		
			_delay_ms(500);
		//PORTB = in;	  // 입력받은 포트 D의 값을 포트 B (led)로 출력
		}



		else if (in==0x08)
		{
			while(1)
			{
				if (cnt==0)
				{
					PORTD=seg_1[0][0];
					PORTB=seg_1[1][0]|0x30;
					break;
				}
				for (int i= 0;i<2;i++)
				{
					PORTB = (PORTB&~(0x10<<i));

					PORTB|= (0x10<<i)|seg_1[1][cnt];
				
			     	PORTD=seg_1[0][cnt];
					//	PORTB=seg_1[1][cnt];
			
					_delay_ms(300);

				}
				//PORTB=PORTB&seg_1[0][cnt];

				for (int i= 0;i<6;i++)
				{
					PORTC= ~(0x01<<i);
					PORTD=seg_1[0][cnt];
						PORTB=seg_1[1][cnt]|0x30;
					_delay_ms(300);
				
				}
					for (int i= 0;i<2;i++)
				{
				
				
					PORTB |= (0xD0>>i)|seg_1[1][cnt];
					PORTD=seg_1[0][cnt];

					_delay_ms(300);

				}
			
	
				for (int i= 0;i<6;i++)
				{
					PORTC= ~(0x10>>i);
					PORTD=seg_1[0][cnt];
						PORTB=seg_1[1][cnt]|0x30;
					_delay_ms(300);
				
				}

				cnt=cnt-1;
			
			}
	
		}
	

	}
}
