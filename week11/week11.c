#include<avr/io.h>
#define F_CPU 16000000UL
#define FREQ(x)(unsigned int)(16000000/2*8(1+x))
#include<util/delay.h>
#include<avr/interrupt.h>


#define ON  1
#define OFF  0

int on_off=0;


void play(unsigned int y)
{
	unsigned int x;
	DDRB|=0x02;
	TCCR1A|=0x40;
	TCCR1B|=0x1A;
	ICR1=y;


}
void stop(void)
{
	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1=0;
	ICR1=0;
	DDRB=~0x02;
}

ISR(INT0_vect)
{
	cli();
	on_off=ON;
	EIFR|=0x01;
	sei();
}

ISR(INT1_vect)
{
	cli();
	on_off=OFF;
	EIFR|=0x02;
	sei();
}

int main()
{
	cli();
	DDRD=0xF3;
	DDRB=0x0F;
	PORTB=0x00;

	PORTD=0x00;
	EICRA=0x0A;
	EIMSK=0x03;
	EIFR|=0x03;

	sei();
	while(1)
	{
		if (on_off==ON)
		{
			play(2273);
		}
		else
		{
			stop();
		}

	}

}
/* 
// pem제어하여 ㅎ1초마다 까마ㅃㄱ거린ㄴ led제어하기

unsigned char TovVal=0;

void LED_BLINK(void)
{
	PORTD=0x00;
	_delay_ms(300);
	PORTD=0xFF;
}

ISR(TIMER0_COMPA_vect)
{	
	OCR0A=0x4E;
	TovVal++;

	if (TovVal==200)
	{
		LED_BLINK();
		TovVal=0;
	}
	sei();

}


int main (void)
{
	unsigned char in;
	cli();
	DDRD=0xFF;
	PORTD=0x00;

	TCCR0A=0x02;
	TCCR0B|=(1<<CS02);
	TCCR0B|=(1<<CS00);

	OCR0A=0x4E;
		
	TIMSK0|=(1<<OCIE0A);
	TIFR0|=(1<<OCIE0A); //어짜피 알아서 클리어딤 

	sei();

	while(1)
	{

	}
}


*/



