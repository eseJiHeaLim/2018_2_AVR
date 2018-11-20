#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include <util/delay.h>

//00설정 
// led on -> 0 , led off -> 1
//새그면트는 on -> 1 , off -> 0
//스위치 누르면 1 임


//display을 입력한 대로 t의 주기를 가지며 n번을 반복한다.
//display : 16진수 입력(입력의1은 켜지는것을 의미 )
void led_alternating_onoff(int display , int n , int t)
{


		for (int i=0;i<n;i++)
		{
	
			PORTD=display;
			PORTB=display;
			_delay_ms(t);
		
	//	PORTD=(~display)<<4;
	//	PORTB=(~display>>4);
		PORTD=~PORTD;
		PORTB=~PORTB;
	
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


//D포트에 세그먼트 전부 연결시 숫자 증가 
unsigned char seg_tbl[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X27,0X7F, 0X67};


//첫벤째 세그면트 Dd에다 두번재 세그먼트 B랑 C일떄 
#define SEG_PB_MASK   0x3F
unsigned char seg_tbl[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x27,0x7F, 0x67};
unsigned char seg_tbl1[] = {0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,0x01, 0x01};


void seg()
{
                DDRD = 0xFF; //포트 D 모든 비트를 출력핀으로
	 DDRB = 0x3F; //포트 D 하위 6 비트를 출력핀으로
	 DDRC = 0x03; //포트 D 하위 2비트를 출력핀으로
	while(1){
	       for(int i = 0; i< 10; i++){	
	       	PORTD = seg_tbl[i]; // index i 에 대응되는 값을 첫 번째 세그먼트로 DISPLAY
		PORTB = SEG_PB_MASK &  seg_tbl[i];
		PORTC = seg_tbl1[i];  // index i 에 대응되는 값을  두번째 세그먼트로 DISPLAY
	     	_delay_ms(500);
	      }
	}
}

//seg 과제 week7

void main()
{
	DDRD=0xF0;
	DDRB=0x0F;
/*
	while(1)
	{
    
		//led 전체를 200ms의 주기로 3번 반복하라.
		//led_all_onoff(3,200);
    
	//	입력한 모양대로 시작으로 교대로 300ms의 주기로 3번 반복하라 
		//세트 1 
		led_alternating_onoff(0xAA,3,300);
		//세트2 
		led_alternating_onoff(0xF0,3,300);
		//세트 3 
		led_alternating_onoff(0xC3,3,300);

    	//led 왼쪽->오른쪽을 300ms의 주기로 5번을 반복한다.
		led_shift(5,300);
	}
*/

//
//
//

//스위치 23번연결 해서 누를때마다 led가 꺼짐 
//나머지 다 열결되어있음 
/*
int   main()
{
	unsigned char in;

	DDRD = 0xF3;
	DDRB = 0xFF;
	
	
	while(1){ 
		in = (PIND & 0x0C);	  // PD2, PD3 입력값 확인
		PORTB = in;	  // 입력받은 포트 D의 값을 포트 B (led)로 출력
	}
}
*/

}




/*

// 마지막 과제 정답

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#define INT0_SW 1
#define INT1_SW 2

void LED_ALL_ONOFF(void);
void Disp_SEG(unsigned char _cnt);
unsigned char input = 0;
unsigned char seg[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x27,0x7F,0x6F};
unsigned char cnt = 0;

ISR(INT0_vect){
   cli();         // clear interrupt
   EIFR |= 0x01;  // interrupt flag set
   ++cnt;
   cnt = cnt % 4;
   EICRA = (cnt<< 2) | cnt;
   Disp_SEG(cnt);
   input = INT0_SW;
   sei();          // set interrupt
}

ISR(INT1_vect){
   cli();
   EIFR |= 0x02;
   input = INT1_SW;
   sei();
}

void LED_ALL_ONOFF(void){
   for (int i = 0;i<10;i++){
      PORTC = 0;
      PORTB = (PORTB & 0x0F) | 0x00;
      _delay_ms(300);
      PORTC = 0xFF;
      PORTB = (PORTB & 0x0F) | 0x30;
       _delay_ms(300);
      if (input == INT0_SW) {
         break;
      }
      if (input == INT1_SW) {
         break;
      }
   }
}

void Disp_SEG(unsigned char _cnt){
   PORTD = (seg[_cnt]&0xF0);
   PORTB = (PORTB & 0x30) | (seg[_cnt] & 0x0F);
   _delay_ms(700);
}

int main(){

   cli();
   DDRD = 0xF3;
   DDRB = 0xFF;
   DDRC = 0xFF;
   
   PORTC = 0xFF;
   PORTB = 0xF0;

   EICRA = 0x0F;
   EIMSK = 0x03;
   EIFR = 0x03;
   sei();


   while(1){
      Disp_SEG(cnt);
      if(input == INT1_SW){
         input = 0;
         LED_ALL_ONOFF();
         Disp_SEG(cnt);
         input = 0;
      } 
   }
}

*/




/*

// 이진 입ㄺ을 십진으로 
#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "segment.h"

int main()
{
 	unsigned char in;

	DDRD = 0xF3;
	DDRB = 0xFF;
	

	while(1){ 
		// 이곳에 스위치값 읽는 부분
		 in = ((PIND & 0x0C) >> 2 );	// 포트 B 입력
		disp_seg(in);	
	}
}
*/


