#include <avr/io.h>
#define FOSC 16000000UL
#define F_CPU 16000000UL
#include <util/delay.h>

//00���� 
// led on -> 0 , led off -> 1
//���׸�Ʈ�� on -> 1 , off -> 0
//����ġ ������ 1 ��


//display�� �Է��� ��� t�� �ֱ⸦ ������ n���� �ݺ��Ѵ�.
//display : 16���� �Է�(�Է���1�� �����°��� �ǹ� )
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


//D��Ʈ�� ���׸�Ʈ ���� ����� ���� ���� 
unsigned char seg_tbl[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7C, 0X27,0X7F, 0X67};


//ù��° ���׸�Ʈ Dd���� �ι��� ���׸�Ʈ B�� C�ϋ� 
#define SEG_PB_MASK   0x3F
unsigned char seg_tbl[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x27,0x7F, 0x67};
unsigned char seg_tbl1[] = {0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,0x01, 0x01};


void seg()
{
                DDRD = 0xFF; //��Ʈ D ��� ��Ʈ�� ���������
	 DDRB = 0x3F; //��Ʈ D ���� 6 ��Ʈ�� ���������
	 DDRC = 0x03; //��Ʈ D ���� 2��Ʈ�� ���������
	while(1){
	       for(int i = 0; i< 10; i++){	
	       	PORTD = seg_tbl[i]; // index i �� �����Ǵ� ���� ù ��° ���׸�Ʈ�� DISPLAY
		PORTB = SEG_PB_MASK &  seg_tbl[i];
		PORTC = seg_tbl1[i];  // index i �� �����Ǵ� ����  �ι�° ���׸�Ʈ�� DISPLAY
	     	_delay_ms(500);
	      }
	}
}

//seg ���� week7

void main()
{
	DDRD=0xF0;
	DDRB=0x0F;
/*
	while(1)
	{
    
		//led ��ü�� 200ms�� �ֱ�� 3�� �ݺ��϶�.
		//led_all_onoff(3,200);
    
	//	�Է��� ����� �������� ����� 300ms�� �ֱ�� 3�� �ݺ��϶� 
		//��Ʈ 1 
		led_alternating_onoff(0xAA,3,300);
		//��Ʈ2 
		led_alternating_onoff(0xF0,3,300);
		//��Ʈ 3 
		led_alternating_onoff(0xC3,3,300);

    	//led ����->�������� 300ms�� �ֱ�� 5���� �ݺ��Ѵ�.
		led_shift(5,300);
	}
*/

//
//
//

//����ġ 23������ �ؼ� ���������� led�� ���� 
//������ �� ����Ǿ����� 
/*
int   main()
{
	unsigned char in;

	DDRD = 0xF3;
	DDRB = 0xFF;
	
	
	while(1){ 
		in = (PIND & 0x0C);	  // PD2, PD3 �Է°� Ȯ��
		PORTB = in;	  // �Է¹��� ��Ʈ D�� ���� ��Ʈ B (led)�� ���
	}
}
*/

}




/*

// ������ ���� ����

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

// ���� �Ԥ��� �������� 
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
		// �̰��� ����ġ�� �д� �κ�
		 in = ((PIND & 0x0C) >> 2 );	// ��Ʈ B �Է�
		disp_seg(in);	
	}
}
*/


