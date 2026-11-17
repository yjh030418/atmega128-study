#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//=============16비트 타이머(CTC) LED 출력=============
volatile uint8_t count = 0;
volatile uint8_t state = 0;

ISR(TIMER1_COMPA_vect){   //타이머1 비교 일치 인터럽트
	count++;
	if(count==2){ 
		count = 0;
		state = !state;
		
		if(state) PORTC = 0xFF;
		else PORTC = 0x00;
	}
}
int main(){
	
	DDRC = 0xFF;
	PORTC = 0xFF;
	

	TCCR1B |= (1<<WGM12);
	
	TCCR1B |= (1<<CS12); //256분주
	
	//500*2 
	//ocr 값을 500으로.
	//65536 
	//16,000,000 / 256(분주) -> 625000Hz (=0.000016s 주기)
	// 0.5초 = 주기 * 31250 
	// 사이클이 31250 돌면 인터럽트 -> 정확하게 0.5초
	OCR1A = 31249; 
	
	TIMSK |= (1<<OCIE1A); //비교 일치 인터럽트
	
	
	
	sei();
	
	while(1){
		
	}
	
}
