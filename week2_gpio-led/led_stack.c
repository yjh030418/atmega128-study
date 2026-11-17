#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void clear_all() {
	PORTC = 0xFF; // 모든 LED 끄기
	_delay_ms(250);
}

int main(void) {
	DDRC = 0xFF; // PORTC 출력 설정
	clear_all();

	while (1) {
		// 정방향 쌓기 (7번에서 0번으로 낙하)
		uint8_t stacked_forward = 0x00;//초기화
		for (int floor = 0; floor < 8; floor++) {
			for (int i = 7; i >= floor; i--) {
				PORTC = ~((1 << i) | stacked_forward); 
				//비트 하나씩 밀면서 or연산
				//그걸 전체 반전
				_delay_ms(50);
			}
			stacked_forward |= (1 << floor); // 쌓인 불빛 위치 저장
		}
		_delay_ms(500); 
		clear_all();     // 초기화

		// 역방향 쌓기 
		uint8_t stacked_backward = 0x00;
		for (int floor = 7; floor >= 0; floor--) {//반대로
			for (int i = 0; i <= floor; i++) {
				PORTC = ~((1 << i) | stacked_backward); 
				_delay_ms(50);
			}
			stacked_backward |= (1 << floor); //쌓인 불빛 위치 저장
		}
		_delay_ms(500); // 완성 후 대기
		clear_all();     // 초기화
	}
	return 0;
}
