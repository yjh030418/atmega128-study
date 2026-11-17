#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t state = 0;
volatile uint8_t stack = 0x00;

ISR(INT4_vect){	//인터럽트 서비스 루틴
	_delay_ms(20);//디바운스

	if(!(PINE&(1<<4))){
		state=1;
		
	}
}



int main(){
	
	DDRC = 0xFF;
	PORTC = 0xFF; //초기 상태 (끄기)
	
	DDRE = 0x00;
	PORTE = (1 << 4); //내부 풀업 저항 사용
	
	EIMSK |= (1<<INT4); //4번 포트 인터럽트 활성화(**or대입)
	EICRB |= (1<<ISC41);//하강 엣지일 때 인터럽트 발생
	//interrupt sense control 4  1 -> 1
	// (1,0)
	
	sei();//set enable interrupt
	

	
	
	while(1){

		uint8_t current = 0x00;
		
		if(stack==0xFF){
			stack=0x00;
			
			_delay_ms(100);
		}
		
		
		if(state == 1){
			state = 0; 

			for(int i=7;i>=0;i--){ //폭포수
				
				
				current = (1 << i); //1000 0000
				
				
				PORTC = ~(current|stack); //0111 1111
				_delay_ms(100);
				current &= ~(1<<i);
				
				
				if (i==0 || (stack & (1<<(i-1)))){ // i=0 순환이 다 돌거나, stack에 닿을 경우
					
					stack |= (1<<(i));  //0000 0001 저장
					break;
				}
			}
			
			
		}
		
		PORTC = ~stack; //현재 스택 츨력
		
		
		_delay_ms(100);
	}
	
	
	return 0 ;
}
