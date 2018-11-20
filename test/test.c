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
        // PD2, PD3 입력값 확인
      PORTB = in;     // 입력받은 포트 D의 값을 포트 B (led)로 출력
   }
   
}
