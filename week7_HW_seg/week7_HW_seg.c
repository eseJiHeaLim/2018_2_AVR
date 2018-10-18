#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include<util/delay.h>

unsigned char seg_1[2][10] = {{0xF0, 0x60, 0xB0, 0xF0, 0x60, 0xD0, 0xD0, 0x70, 0xF0, 0xF0},
							  {0x03, 0x00, 0x05, 0x04, 0x06, 0x60, 0x07, 0x02, 0x07, 0x03}};

unsigned char seg_2[2][10] = {{0x30, 0x20, 0x30, 0x30, 0x20, 0x01, 0x01, 0x03, 0x03, 0x03},
							  {0x0F, 0x01, 0x16, 0x13, 0x19, 0x1B, 0x1F, 0x09, 0x1F, 0x1B}};



void main()
{
	DDRD=0xF0;
	DDRB=0x3F;
	DDRC=0x3F;


}
