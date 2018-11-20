
#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char TovVal = 0;

void LED_BLINK()
{
	PORTD = 0x00;
	_delay_ms(300);
	PORTD = 0xFF;
}


ISR(TIMER1_OVF_vect)
{
	TCNT1 = 0xFFFF - 0x3D09; //To make 5ms 
	TovVal++;

	if (TovVal == 1)
	{
		LED_BLINK();
		TovVal = 0;
	}
	sei(); 
}


int main()
{

	unsigned char in;
	cli();
	DDRD = 0xFF;
	PORTD = 0xFF;

	TCCR1A = 0x00;

	TCCR1B |= (1 << CS12);
	//1024 prescaler
	TCCR1B |= (1 << CS10);

	TCNT1 = 0xFFFF - 0x3D09;

	TIMSK1 |= 1 << TOIE1;
	TIFR1 |= 1 << TOV1;

	sei();

	while (1)
	{
	}
}


