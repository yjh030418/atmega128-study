#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define Forward() {PORTE |= (1<<PE0); PORTE &= ~(1<<PE2);}
#define Backward() {PORTE &= ~(1<<PE0); PORTE |= (1<<PE2);}

#define Speed(s) OCR3B = s


void InitializeTimer3(void){
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32); // 8비트 고속 PWM모드
	//주파수가 높을수록 모터 회전이 부드러워짐
	
	TCCR3A |= (1<<COM3B1); //비반전
	
	TCCR3B |= (1<<CS31) | (1<< CS30); // 64분주 -> 250,000Hz
	// 250,000 / 256 -> 약 976Hz
	
	OCR3B = 0; // (0~255)
	
}

int main(void){
	DDRE |= (1<<PE0) | (1<<PE2) | (1<<PE4);
	//출력 단자 설정 (pwm은 pe4)
	InitializeTimer3();
	
	while(1){
		
		Forward();
		
		Speed(100);
		_delay_ms(1000);

		Speed(180);
		_delay_ms(1000);

		Speed(255);
		_delay_ms(1000);
		
		Speed(0);
		_delay_ms(3000);
	}
	return 0;
}
