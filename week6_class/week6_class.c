//cpu의 레지스터들을 모두 딮인을 하고 있음 
#include <avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
//값을 확인하고 준다는 것은 소프트웨어를 통해서 하드웨어로 가는 것임 -> 포트 제어 

//포트제어 led를 키려면 0을 입력해줘야함 

int main()
{
	DDRD=0xFF; // 포트 A의 첫번째 비트를 추력핀으로 
	//PORTD=0xFE ; // 11111110  첫 번째 비트에 logic low -> led on;
	
	//for (int i=0; i<3;i++)
	//{
	//	PORTD=0xAA;
	//	_delay_ms(500);
	//	PORTD=0x55;
	//	_delay_ms(500);
	//}

	while(1)
	{
		for (int j= 0;j<8;j++)
		{
			PORTD= ~ (0x01<<j);
			_delay_ms(40);
		}
	}
}


//과제 있음 ppt 

// 보쇄 관계 == 반전 --> ~  쳐주면 됨 1회 보쇄 
//시프트할때 코드를 하나씩 쓰지맑 그냥 하나씩 밀어서 할것

// 낫게이트가 붙는 이유는 led는 0으로 해야 켜지기 때문이니깐 

//	

