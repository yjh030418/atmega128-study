#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
	PORTC = 0xFF; // 모든 LED를 끈 상태(1)로 먼저 설정
	DDRC = 0xFF;  // PORTC를 출력으로 설정

	while (1) {
		
		for (int i = 0; i < 8; i++) {
			
			PORTC = ~(1 << i);   // i번째 LED만 켜기
			_delay_ms(500);      // 켜짐 유지

			PORTC = 0xFF;        // 다시 모든 LED 끄기 
			_delay_ms(250);       // 잠깐 대기
		}
		
		_delay_ms(250); //잠깐 대기
	}
	return 0;
}
