#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int   main()
{
   unsigned char in;

   DDRD = 0xF3;
   DDRB = 0xFF;
   
   
   while(1){ 

   in = (PIND & 0x0C);
        // PD2, PD3 �Է°� Ȯ��
      PORTB = in;     // �Է¹��� ��Ʈ D�� ���� ��Ʈ B (led)�� ���
   }
   
}
