#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

// ��� led on, off �ݺ� 
// n = �ݺ�Ƚ�� , t = �ݺ� �ֱ� 
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

//display�� �Է��� ��� t�� �ֱ⸦ ������ n���� �ݺ��Ѵ�.
//display : 16���� �Է�(�Է���1�� �����°��� �ǹ� )
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

//�պ� shift 	
//n= �պ� Ƚ�� , v= �̵��۵�(ms)
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
    
		//led ��ü�� 200ms�� �ֱ�� 6�� �ݺ��϶�.
		led_all_onoff(6,200);
    
		//�Է��� ����� �������� ����� 300ms�� �ֱ�� 3�� �ݺ��϶� 
		//��Ʈ 1 
		led_alternating_onoff(0xAA,3,300);
		//��Ʈ2 
		led_alternating_onoff(0xF0,3,300);
		//��Ʈ 3 
		led_alternating_onoff(0xC3,3,300);

    	//led ����->�������� 300ms�� �ֱ�� 3���� �ݺ��Ѵ�.
		led_shift(3,300);
	}
}
