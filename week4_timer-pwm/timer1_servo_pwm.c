#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//======16비트 타이머를 이용한 서보모터 제어======

#define Pulse0 1150
#define Pulse90 3000 // 1.5ms 만큼 high 유지 - pwm
#define Pulse180 4750

void InitializeTimer1(void){
	TCCR1A |= (1<<WGM11);
	TCCR1B |= (1<<WGM12)| (1<<WGM13);  //  fast pwm with ICR1
	
	TCCR1A |=(1<<COM1A1); //비반전 모드
	
	TCCR1B |= (1<<CS11); // (0,1,0) 8분주 (0.0005ms)
	
	ICR1 = 39999; // 
	//20ms/0.0005ms = 40000  (-1)	
	
	
	
}

int main(){
	DDRB |= (1<<PB5);
	
	InitializeTimer1();
	
	while(1){
		OCR1A = Pulse0;
		_delay_ms(1000);
		
		OCR1A = Pulse90;
		_delay_ms(1000);
		
		OCR1A = Pulse180;
		_delay_ms(1000);
		
	}
	return 0;
}
