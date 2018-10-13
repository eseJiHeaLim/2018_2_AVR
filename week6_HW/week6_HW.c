#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

// 모든 led on, off 반복 
// n = 반복횟수 , t = 반복 주기 
void led_all_onoff(int n, int t)
{
	int i =0;
	for (i=0; i<n;i++)
	{
		PORTD=0x0F;
		PORTB=0xF0;
		_delay_ms(t);
		PORTD=0xF0;
		PORTB=0x0F;
		_delay_ms(t);
	}
}

//display을 입력한 대로 t의 주기를 가지며 n번을 반복한다.
//display : 16진수 입력(입력의1은 켜지는것을 의미 )
void led_alternating_onoff(int display , int n , int t)
{
	
	for (int i=0;i<n;i++)
	{
		PORTD=(display<<4);
		PORTB=(display>>4);
		_delay_ms(t);
		
		PORTD=(~display)<<4;
		PORTB=(~display>>4);
		_delay_ms(t);
	}
}

//왕복 shift 	
//n= 왕복 횟수 , v= 이동송도(ms)
void led_shift(int n, int v)
{
	int cnt=0;
	while(1)
	{
		PORTD=0xFF;
		PORTB=0xFF;
		if (cnt==n)
		{
			return;
		}
	
		for (int i= 0;i<4;i++)
		{
			PORTD= ~ (0x10<<i);
			_delay_ms(v);
		}
	
		PORTD=0xFF;
		for (int i= 0;i<4;i++)
		{
			PORTB= ~ (0x01<<i);
			_delay_ms(v);
		}
		for (int i= 0;i<5;i++)
		{
			PORTB= ~ (0x10>>i);
			_delay_ms(v);
		}
		PORTB=0xFF;
		for (int i= 0;i<4;i++)
		{
			PORTD= ~ (0x80>>i);
			_delay_ms(v);
		}
		cnt++;
	}
}

void main()
{
	DDRD=0xF0;
	DDRB=0x0F;

	while(1)
	{
    
		//led 전체를 200ms의 주기로 6번 반복하라.
		led_all_onoff(6,200);
    
		//입력한 모양대로 시작으로 교대로 300ms의 주기로 3번 반복하라 
		//세트 1 
		led_alternating_onoff(0xAA,3,300);
		//세트2 
		led_alternating_onoff(0xF0,3,300);
		//세트 3 
		led_alternating_onoff(0xC3,3,300);

    	//led 왼쪽->오른쪽을 300ms의 주기로 3번을 반복한다.
		led_shift(3,300);
	}
}
