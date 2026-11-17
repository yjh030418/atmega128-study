#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//====================토글==================
volatile int state = 0;//볼라타일 선언(읽어오는 중 인터럽트 막기)


ISR(INT4_vect){	//인터럽트 서비스 루틴
	
	_delay_ms(20);//디바운스
	
	if((PINE & (1<<4)) == 0){	//입력 확정
		state = (state + 1) % 2;//버튼 누를 때 상태 변환하기
	}
	
	
}


int main(){
	
	DDRC = 0xFF;
	PORTC = 0xFF; //초기 상태 (끄기)
	
	DDRE = 0x00;
	PORTE = (1 << 4); //내부 풀업 저항 사용
	
	EIMSK |= (1<<INT4); //4번 포트 인터럽트 활성화(**or대입)
	EICRB |= (1<<ISC41);//하강 엣지일 때 인터럽트 발생
	//interrupt sense control 4 -> 1
	// (1,0)
	
	sei();//set enable interrupt
	

	

	while(1){
		
	
				if(state == 0){
				
					PORTC = 0xFF;//끔
					
				}
			
				else {
					
					PORTC = 0x00;//켬
					
				}
		
		
	}
	
	
	return 0 ;
}
