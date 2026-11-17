#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//=============8비트 타이머 LED 출력=============
volatile uint8_t count = 0;
volatile uint8_t state = 0;

ISR(TIMER0_OVF_vect){   //타이머0 오버플로우 허용
	count++;
	if(count==64){ // 오버플로우 0.016 X 64회 = 1.024초
		count = 0;
		state = !state;
		
		if(state) PORTC = 0xFF;
		else PORTC = 0x00;
	}
}
int main(){
	
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00);
	// tccr0 레지스터 (1, 1, 1) 설정
	// 분주비 1024 , 8비트 타이머 -> 0.016초 마다 오버플로우 발생
	// 16000000 / 1024 = 15625Hz -> 0.000064s 
	// 0.000064 * 256 = 약 16ms

	TIMSK |= (1<<TOIE0); //오버플로우 인터럽트 활성
	

	sei();
	
	while(1){
		
	}
		
}
