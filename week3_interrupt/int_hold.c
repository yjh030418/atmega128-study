#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//================홀드===============

ISR(INT4_vect){ //인터럽트 서비스 루틴
	_delay_ms(20); //디바운싱

	if(!(PINE & (1 << 4))){ //버튼이 눌렸을 때
		PORTC = 0x00;
		
	}
	else{
		PORTC = 0xFF;
	}
	
}



int main(){
	
	DDRC = 0xFF;
	PORTC = 0xFF; //초기 상태 (끄기)
	
	DDRE = 0x00;
	PORTE = (1 << 4); //내부 풀업 저항 사용
	
	EIMSK |= (1<<INT4); //4번 포트 인터럽트 활성화(**or대입)
	EICRB |= (0<<ISC41 | 0<<ISC41);//LOW 일 때 인터럽트 발생
	
	// (0,0)

	sei();//set enable interrupt
	

	
	
	while(1){
		
	}
	
	return 0 ;
}
